#include "AdaptiveCache.hpp"
#include <openssl/sha.h>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace cache_library {

    AdaptiveCache::AdaptiveCache() : dispersionLRU(0), dispersionMRU(0), lastAlgorithm("None") {}

    void AdaptiveCache::access(const int key) {
        // Ініціалізуємо або збільшуємо частоту доступу для ключа
        if (!accessFrequency.contains(key)) {
            accessFrequency[key] = 1.0; // Початкова частота доступу
            insertionTime[key] = std::chrono::steady_clock::now();
        }
        else {
            accessFrequency[key] += 1.0; // Збільшуємо частоту доступу для ключа
        }

        // Розрахунок дисперсій для LRU та MRU
        calculate_dispersions();

        // Вибір алгоритму на основі дисперсії
        if (dispersionLRU < dispersionMRU) {
            lruCache.insert(key, key,this);
            lastAlgorithm = "LRU";
        }
        else {
            mruCache.insert(key, key,this);
            lastAlgorithm = "MRU";
        }

        // Архівування, якщо потрібно
        archive(key);
    }

    void AdaptiveCache::insert(int key, int value) {
        accessFrequency[key] = 1.0;
        insertionTime[key] = std::chrono::steady_clock::now();

        calculate_dispersions();

        if (dispersionLRU < dispersionMRU) {
            lruCache.insert(key, value, this); // Передаємо посилання на AdaptiveCache
            lastAlgorithm = "LRU";
        }
        else {
            mruCache.insert(key, value, this); // Передаємо посилання на AdaptiveCache
            lastAlgorithm = "MRU";
        }

        // Видаляємо виклик archive(key);
    }

    int AdaptiveCache::get(int key) {
        int value = -1;

        if (lruCache.contains(key)) {
            value = lruCache.get(key);
            lastAlgorithm = "LRU";
        }
        else if (mruCache.contains(key)) {
            value = mruCache.get(key);
            lastAlgorithm = "MRU";
        }
        else {
            // Спробувати відновити з архіву
            value = restore_from_archive(key);
            if (value != -1) {
                insert(key, value);
            }
        }

        if (value != -1) {
            accessFrequency[key] += 1.0;
            calculate_dispersions();
        }

        return value;
    }

    std::vector<int> AdaptiveCache::filter(std::function<bool(int)> predicate) const {
        std::vector<int> result;

        // Фільтрація в LRU кеші
        for (const int key : lruCache.get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        // Фільтрація в MRU кеші
        for (const int key : mruCache.get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        return result;
    }

    std::vector<int> AdaptiveCache::sort(std::function<bool(int, int)> comparator) const {
        std::vector<int> all_keys = lruCache.get_keys();
        std::vector<int> mru_keys = mruCache.get_keys();
        all_keys.insert(all_keys.end(), mru_keys.begin(), mru_keys.end());

        std::sort(all_keys.begin(), all_keys.end(), comparator);

        return all_keys;
    }

    void AdaptiveCache::calculate_dispersions() {
        double sum_lru = 0, sum_mru = 0;
        double mean_lru = 0, mean_mru = 0;
        int count_lru = 0, count_mru = 0;

        // Обчислюємо середнє значення для LRU і MRU
        for (const auto& [key, freq] : accessFrequency) {
            if (lruCache.contains(key)) {
                mean_lru += freq;
                count_lru++;
            }
            else if (mruCache.contains(key)) {
                mean_mru += freq;
                count_mru++;
            }
        }

        if (count_lru > 0) mean_lru /= count_lru;
        if (count_mru > 0) mean_mru /= count_mru;

        // Обчислюємо дисперсію для LRU і MRU
        for (const auto& [key, freq] : accessFrequency) {
            if (lruCache.contains(key)) {
                sum_lru += pow(freq - mean_lru, 2);
            }
            else if (mruCache.contains(key)) {
                sum_mru += pow(freq - mean_mru, 2);
            }
        }

        if (count_lru > 0) dispersionLRU = sum_lru / count_lru;
        if (count_mru > 0) dispersionMRU = sum_mru / count_mru;
    }

    void AdaptiveCache::archive(const int key) {
        if (should_archive(key)) {
	        const double checksum = calculate_sha256(std::to_string(key));
            write_to_archive_file(key, checksum);
            remove_from_caches(key);
            std::cout << "Archived key: " << key << " with checksum: " << checksum << '\n';
        }
    }

    bool AdaptiveCache::should_archive(int key) const {
        // Логіка визначення архівування на основі частоти доступу та часу перебування в кеші
        const auto now = std::chrono::steady_clock::now();
        const auto insertion_time = insertionTime.at(key);

        if (const auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - insertion_time).count(); accessFrequency.at(key) < 2 || duration > 300) {
            return true;
        }
        return false;
    }

    double AdaptiveCache::calculate_sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

        double checksum = 0;
        for (const unsigned char i : hash)
        {
            checksum += i;
        }
        return checksum;
    }

    void AdaptiveCache::write_to_archive_file(const int key, const double checksum) const {
        std::ofstream archive_file(archiveFilePath, std::ios::app);
        if (archive_file.is_open()) {
            archive_file << "Key: " << key << ", Checksum: " << checksum << "\n";
            archive_file.close();
        }
        else {
            std::cerr << "Unable to open archive file!" << '\n';
        }
    }

    void AdaptiveCache::remove_from_caches(const int key) {
        if (lruCache.contains(key)) {
            lruCache.remove(key);
        }
        else if (mruCache.contains(key)) {
            mruCache.remove(key);
        }
    }

    int AdaptiveCache::restore_from_archive(const int key) {
	    if (std::ifstream archive_file(archiveFilePath); archive_file.is_open()) {
            std::string line;
            while (std::getline(archive_file, line)) {
                // Парсинг лінії для отримання ключа та контрольної суми
                const size_t key_pos = line.find("Key: ");
                if (const size_t checksum_pos = line.find(", Checksum: "); key_pos != std::string::npos && checksum_pos != std::string::npos) {
	                const int archived_key = std::stoi(line.substr(key_pos + 5, checksum_pos - (key_pos + 5)));
	                if (const double archived_checksum = std::stod(line.substr(checksum_pos + 12)); archived_key == key && verify_checksum(key, archived_checksum)) {
                        archive_file.close();
                        return key; // Повертаємо ключ як значення
                    }
                }
            }
            archive_file.close();
        }
        return -1;
    }

    bool AdaptiveCache::verify_checksum(const int key, const double checksum) {
	    const double calculated_checksum = calculate_sha256(std::to_string(key));
        return calculated_checksum == checksum;
    }

    void AdaptiveCache::display_cache_status() const {
        std::cout << "Cache Status:\n";
        lruCache.display_status();
        mruCache.display_status();
        std::cout << "Last used algorithm: " << lastAlgorithm << "\n";
    }

    void AdaptiveCache::on_evict(const int key) {
        if (should_archive(key)) {
	        const double checksum = calculate_sha256(std::to_string(key));
            write_to_archive_file(key, checksum);
            remove_from_caches(key);
            std::cout << "Archived key: " << key << " with checksum: " << checksum << '\n';
        }
    }

} // namespace CacheLibrary
