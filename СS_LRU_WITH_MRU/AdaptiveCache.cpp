#include "AdaptiveCache.hpp"
#include <openssl/sha.h>
#include <fstream>
#include <cmath>
#include <iostream>

namespace CacheLibrary {

// Реалізація методів класу AdaptiveCache
AdaptiveCache::AdaptiveCache() : dispersionLRU(0), dispersionMRU(0), lastAlgorithm("None") {}

void AdaptiveCache::access(int key) {
    // Ініціалізуємо або збільшуємо частоту доступу для ключа
    if (!accessFrequency.contains(key)) {
        accessFrequency[key] = 1.0; // Початкова частота доступу
    }
    else {
        accessFrequency[key] += 1.0; // Збільшуємо частоту доступу для ключа
    }

    // Додаємо відлагоджувальне повідомлення для перевірки частоти доступу
    std::cout << "Access Frequency for key " << key << ": " << accessFrequency[key] << '\n';

    // Розрахунок дисперсій для LRU та MRU
    calculate_dispersions();

    // Вибір алгоритму на основі дисперсії
    if (dispersionLRU < dispersionMRU) {
        // Використовуємо LRU
        lruCache.insert(key, key);
        lastAlgorithm = "LRU";
        std::cout << "Key: " << key << " inserted using LRU algorithm." << '\n';
    }
    else if (dispersionMRU <= dispersionLRU) {
        // Використовуємо MRU
        mruCache.insert(key, key);
        lastAlgorithm = "MRU";
        std::cout << "Key: " << key << " inserted using MRU algorithm." << '\n';
    }

    // Архівування, якщо потрібно
    archive(key);
}


void AdaptiveCache::calculate_dispersions() {
    double sum_lru = 0, sum_mru = 0;
    double mean_lru = 0, mean_mru = 0;
    int count_lru = 0, count_mru = 0;

    // Обчислюємо середнє значення для LRU і MRU
    for (const auto& [fst, snd] : accessFrequency) {
        if (lruCache.contains(fst)) {
            mean_lru += snd;
            count_lru++;
        }
        else if (mruCache.contains(fst)) {
            mean_mru += snd;
            count_mru++;
        }
    }

    if (count_lru > 0) mean_lru /= count_lru;
    if (count_mru > 0) mean_mru /= count_mru;

    // Вивід середніх значень для перевірки
    std::cout << "Mean LRU: " << mean_lru << ", Mean MRU: " << mean_mru << '\n';

    // Обчислюємо дисперсію для LRU і MRU
    for (const auto& entry : accessFrequency) {
        if (lruCache.contains(entry.first)) {
            sum_lru += pow(entry.second - mean_lru, 2);
        }
        else if (mruCache.contains(entry.first)) {
            sum_mru += pow(entry.second - mean_mru, 2);
        }
    }

    if (count_lru > 0) dispersionLRU = sum_lru / count_lru;
    if (count_mru > 0) dispersionMRU = sum_mru / count_mru;

    // Виведення для перевірки обчислення дисперсій
    std::cout << "Dispersion LRU: " << dispersionLRU << ", Dispersion MRU: " << dispersionMRU << '\n';
}



void AdaptiveCache::archive(const int key) {
    if (accessFrequency[key] < 1) {
        double checksum = calculate_sha256(std::to_string(key));
        write_to_archive_file(key, checksum);
        std::cout << "Archived key: " << key << " with checksum: " << checksum << '\n';
    }
}

double AdaptiveCache::calculate_sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    std::string hashStr(hash, hash + SHA256_DIGEST_LENGTH);

    double checksum = 0;
    for (const char ch : hashStr) {
        checksum += static_cast<unsigned char>(ch);
    }
    return checksum;
}

void AdaptiveCache::write_to_archive_file(const int key, const double checksum) const
{
	if (std::ofstream archive_file(archiveFilePath, std::ios::app); archive_file.is_open()) {
        archive_file << "Key: " << key << ", Checksum: " << checksum << "\n";
        archive_file.close();
    }
    else {
        std::cerr << "Unable to open archive file!" << '\n';
    }
}

void AdaptiveCache::display_cache_status() const {
    std::cout << "Cache Status:\n";

    for (const auto& [fst, snd] : accessFrequency) {
        if (lruCache.contains(fst)) {
            lruCache.display_status();
        }
        else
        {
            mruCache.display_status(); // Виводимо статус MRU кешу
        }
    }


    std::cout << "Last used algorithm: " << lastAlgorithm << "\n";
}

} // namespace CacheLibrary
