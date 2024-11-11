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
    std::cout << "Access Frequency for key " << key << ": " << accessFrequency[key] << std::endl;

    // Розрахунок дисперсій для LRU та MRU
    calculate_dispersions();

    // Вибір алгоритму на основі дисперсії
    if (dispersionLRU < dispersionMRU) {
        // Використовуємо LRU
        lruCache.insert(key, key);
        lastAlgorithm = "LRU";
        std::cout << "Key: " << key << " inserted using LRU algorithm." << std::endl;
    }
    else if (dispersionMRU <= dispersionLRU) {
        // Використовуємо MRU
        mruCache.insert(key, key);
        lastAlgorithm = "MRU";
        std::cout << "Key: " << key << " inserted using MRU algorithm." << std::endl;
    }

    // Архівування, якщо потрібно
    archive(key);
}


void AdaptiveCache::calculate_dispersions() {
    double sumLRU = 0, sumMRU = 0;
    double meanLRU = 0, meanMRU = 0;
    int countLRU = 0, countMRU = 0;

    // Обчислюємо середнє значення для LRU і MRU
    for (const auto& entry : accessFrequency) {
        if (lruCache.contains(entry.first)) {
            meanLRU += entry.second;
            countLRU++;
        }
        else if (mruCache.contains(entry.first)) {
            meanMRU += entry.second;
            countMRU++;
        }
    }

    if (countLRU > 0) meanLRU /= countLRU;
    if (countMRU > 0) meanMRU /= countMRU;

    // Вивід середніх значень для перевірки
    std::cout << "Mean LRU: " << meanLRU << ", Mean MRU: " << meanMRU << std::endl;

    // Обчислюємо дисперсію для LRU і MRU
    for (const auto& entry : accessFrequency) {
        if (lruCache.contains(entry.first)) {
            sumLRU += pow(entry.second - meanLRU, 2);
        }
        else if (mruCache.contains(entry.first)) {
            sumMRU += pow(entry.second - meanMRU, 2);
        }
    }

    if (countLRU > 0) dispersionLRU = sumLRU / countLRU;
    if (countMRU > 0) dispersionMRU = sumMRU / countMRU;

    // Виведення для перевірки обчислення дисперсій
    std::cout << "Dispersion LRU: " << dispersionLRU << ", Dispersion MRU: " << dispersionMRU << std::endl;
}



void AdaptiveCache::archive(const int key) {
    if (accessFrequency[key] < 1) {
        double checksum = calculate_sha256(std::to_string(key));
        write_to_archive_file(key, checksum);
        std::cout << "Archived key: " << key << " with checksum: " << checksum << std::endl;
    }
}

double AdaptiveCache::calculate_sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    std::string hashStr(hash, hash + SHA256_DIGEST_LENGTH);

    double checksum = 0;
    for (char ch : hashStr) {
        checksum += static_cast<unsigned char>(ch);
    }
    return checksum;
}

void AdaptiveCache::write_to_archive_file(const int key, const double checksum) const
{
    std::ofstream archiveFile(archiveFilePath, std::ios::app);
    if (archiveFile.is_open()) {
        archiveFile << "Key: " << key << ", Checksum: " << checksum << "\n";
        archiveFile.close();
    }
    else {
        std::cerr << "Unable to open archive file!" << std::endl;
    }
}

void AdaptiveCache::display_cache_status() const {
    std::cout << "Cache Status:\n";

    for (const auto& entry : accessFrequency) {
        if (lruCache.contains(entry.first)) {
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
