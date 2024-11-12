#include "AdaptiveCache.hpp"
#include <openssl/sha.h>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace cache_library {

   
    adaptive_cache::adaptive_cache(std::shared_ptr<ICache> lruCachePtr, std::shared_ptr<ICache> mruCachePtr)
        : lru_cache_(std::move(lruCachePtr)), mru_cache_(std::move(mruCachePtr)),
        dispersion_lru_(0), dispersion_mru_(0), last_algorithm_("None") {}
    void adaptive_cache::access(const int key) {
        // Ініціалізуємо або збільшуємо частоту доступу для ключа
        if (!access_frequency_.contains(key)) {
            access_frequency_[key] = 1.0; // Початкова частота доступу
            insertion_time_[key] = std::chrono::steady_clock::now();
        }
        else {
            access_frequency_[key] += 1.0; // Збільшуємо частоту доступу для ключа
        }

        // Розрахунок дисперсій для LRU та MRU
        calculate_dispersions();

        // Вибір алгоритму на основі дисперсії
        if (dispersion_lru_ < dispersion_mru_) {
            lru_cache_->insert(key, key);
            last_algorithm_ = "LRU";
        }
        else {
            mru_cache_->insert(key, key);
            last_algorithm_ = "MRU";
        }

        // Архівування, якщо потрібно
        archive(key);
    }

    void adaptive_cache::insert(const int key, const int value) {
        access_frequency_[key] += 1.0;
        insertion_time_[key] = std::chrono::steady_clock::now();

        calculate_dispersions();
      
        if (dispersion_lru_ < dispersion_mru_) {
            lru_cache_->insert(key, value); // Передаємо посилання на AdaptiveCache
            last_algorithm_ = "LRU";
        }
        else {
            mru_cache_->insert(key, value); // Передаємо посилання на AdaptiveCache
            last_algorithm_ = "MRU";
        }

        // Видаляємо виклик archive(key);
    }

    int adaptive_cache::get(const int key) {
        int value = -1;
        
        if (lru_cache_->contains(key)) {
            value = lru_cache_->get(key);
            last_algorithm_ = "LRU";
        }
        else if (mru_cache_->contains(key)) {
            value = mru_cache_->get(key);
            last_algorithm_ = "MRU";
        }
        else {
            // Спробувати відновити з архіву
            value = restore_from_archive(key);
            if (value != -1) {
                insert(key, value);
            }
        }

        if (value != -1) {
            access_frequency_[key] += 1.0;
            calculate_dispersions();
        }

        return value;
    }

    std::vector<int> adaptive_cache::filter(const std::function<bool(int)>& predicate) const {
        std::vector<int> result;

        // Фільтрація в LRU кеші
        for (const int key : lru_cache_->get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        // Фільтрація в MRU кеші
        for (const int key : mru_cache_->get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        return result;
    }

    std::vector<int> adaptive_cache::sort(std::function<bool(int, int)> comparator) const {
        std::vector<int> all_keys = lru_cache_->get_keys();
        std::vector<int> mru_keys = mru_cache_->get_keys();
        all_keys.insert(all_keys.end(), mru_keys.begin(), mru_keys.end());

        std::sort(all_keys.begin(), all_keys.end(), comparator);

        return all_keys;
    }

    void adaptive_cache::calculate_dispersions() {
        double sum_lru = 0, sum_mru = 0;
        double mean_lru = 0, mean_mru = 0;
        int count_lru = 0, count_mru = 0;

        // Обчислюємо середнє значення для LRU і MRU
        for (const auto& [key, freq] : access_frequency_) {
            if (lru_cache_->contains(key)) {
                mean_lru += freq;
                count_lru++;
            }
            else if (mru_cache_->contains(key)) {
                mean_mru += freq;
                count_mru++;
            }
        }

        if (count_lru > 0) mean_lru /= count_lru;
        if (count_mru > 0) mean_mru /= count_mru;

        // Обчислюємо дисперсію для LRU і MRU
        for (const auto& [key, freq] : access_frequency_) {
            if (lru_cache_->contains(key)) {
                sum_lru += pow(freq - mean_lru, 2);
            }
            else if (mru_cache_->contains(key)) {
                sum_mru += pow(freq - mean_mru, 2);
            }
        }

        if (count_lru > 0) dispersion_lru_ = sum_lru / count_lru;
        if (count_mru > 0) dispersion_mru_ = sum_mru / count_mru;
    }

    void adaptive_cache::archive(const int key) {
        if (should_archive(key)) {
	        const double checksum = calculate_sha256(std::to_string(key));
            write_to_archive_file(key, checksum);
            remove_from_caches(key);
            std::cout << "Archived key: " << key << " with checksum: " << checksum << '\n';
        }
    }

    bool adaptive_cache::should_archive(const int key) const {
        // Логіка визначення архівування на основі частоти доступу та часу перебування в кеші
        const auto now = std::chrono::steady_clock::now();
        const auto insertion_time = insertion_time_.at(key);

        if (const auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - insertion_time).count(); access_frequency_.at(key) < 2 || duration > 300) {
            return true;
        }
        return false;
    }

    double adaptive_cache::calculate_sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

        double checksum = 0;
        for (const unsigned char i : hash)
        {
            checksum += i;
        }
        return checksum;
    }

    void adaptive_cache::write_to_archive_file(const int key, const double checksum) const {
        std::ofstream archive_file(archive_file_path_, std::ios::app);
        if (archive_file.is_open()) {
            archive_file << "Key: " << key << ", Checksum: " << checksum << "\n";
            archive_file.close();
        }
        else {
            std::cerr << "Unable to open archive file!" << '\n';
        }
    }

    void adaptive_cache::remove_from_caches(const int key) const
    {
        if (lru_cache_->contains(key)) {
            lru_cache_->remove(key);
        }
        else if (mru_cache_->contains(key)) {
            mru_cache_->remove(key);
        }
    }

    int adaptive_cache::restore_from_archive(const int key) const
    {
	    if (std::ifstream archive_file(archive_file_path_); archive_file.is_open()) {
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

    bool adaptive_cache::verify_checksum(const int key, const double checksum) {
	    const double calculated_checksum = calculate_sha256(std::to_string(key));
        return calculated_checksum == checksum;
    }

    void adaptive_cache::display_cache_status() const {
        std::cout << "Cache Status:\n";
        lru_cache_->display_status();
        mru_cache_->display_status();
        std::cout << "Last used algorithm: " << last_algorithm_ << "\n";
    }

    void adaptive_cache::on_evict(const int key) const
    {
        if (should_archive(key)) {
	        const double checksum = calculate_sha256(std::to_string(key));
            write_to_archive_file(key, checksum);
            remove_from_caches(key);
            std::cout << "Archived key: " << key << " with checksum: " << checksum << '\n';
        }
    }

} // namespace CacheLibrary
