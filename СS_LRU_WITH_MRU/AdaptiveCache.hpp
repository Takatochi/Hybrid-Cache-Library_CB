﻿#ifndef ADAPTIVE_CACHE_HPP
#define ADAPTIVE_CACHE_HPP

#include "LRU_Cache.hpp"
#include "MRU_Cache.hpp"
#include <unordered_map>
#include <string>

namespace CacheLibrary {

    /**
     * @class AdaptiveCache
     * @brief Адаптивний кеш, який перемикається між алгоритмами LRU та MRU залежно від дисперсії доступу.
     */
    class AdaptiveCache {
    public:
        /**
         * @brief Конструктор для ініціалізації адаптивного кешу.
         */
        AdaptiveCache();

        /**
         * @brief Доступ до ключа з адаптивним вибором алгоритму кешування.
         * @param key Ключ для доступу.
         */
        void access(int key);

        /**
         * @brief Архівування ключа на основі частоти доступу.
         * @param key Ключ для архівування.
         */
        void archive(int key);

        /**
         * @brief Розрахунок дисперсій доступу для LRU та MRU.
         */
        void calculate_dispersions();

        /**
         * @brief Виведення поточного статусу кешу.
         */
        void display_cache_status() const;

    private:
        LRU_Cache lruCache; ///< Об'єкт кешу LRU.
        MRU_Cache mruCache; ///< Об'єкт кешу MRU.
        float dispersionLRU, dispersionMRU; ///< Дисперсії для LRU та MRU.
        std::unordered_map<int, int> accessFrequency; ///< Частота доступу до кожного ключа.
        std::unordered_map<int, double> insertionTime; ///< Час вставки для кожного ключа.
        const double alpha = 0.5; ///< Коефіцієнт згладжування для розрахунків частоти.
        const std::string archiveFilePath = "archive.txt"; ///< Шлях до файлу архіву.
        std::string lastAlgorithm; ///< Останній використаний алгоритм кешування.

        /**
         * @brief Обчислює SHA-256 контрольну суму для даних.
         * @param data Дані для хешування.
         * @return Контрольна сума у вигляді числа з плаваючою точкою.
         */
        static double calculate_sha256(const std::string& data);

        /**
         * @brief Записує ключ і його контрольну суму у файл архіву.
         * @param key Ключ для запису.
         * @param checksum Контрольна сума для ключа.
         */
        void write_to_archive_file(int key, double checksum) const;
    };

} // namespace CacheLibrary

#endif // ADAPTIVE_CACHE_HPP
