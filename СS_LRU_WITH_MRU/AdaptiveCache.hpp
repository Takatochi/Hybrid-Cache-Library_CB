﻿#ifndef ADAPTIVE_CACHE_HPP
#define ADAPTIVE_CACHE_HPP

#include "ICache.hpp"
#include "LRU_Cache.hpp"
#include "MRU_Cache.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <chrono>

namespace cache_library {

    /**
     * @class adaptive_cache
     * @brief Адаптивний кеш, який перемикається між алгоритмами LRU та MRU залежно від дисперсії доступу.
     */
    class adaptive_cache {
    public:
        /**
         * @brief Конструктор для ініціалізації адаптивного кешу.
         * @param lruCache Указівник на LRU кеш.
         * @param mruCache Указівник на MRU кеш.
         */
        adaptive_cache(std::shared_ptr<ICache> lruCache, std::shared_ptr<ICache> mruCache);
    

        /**
         * @brief Доступ до ключа з адаптивним вибором алгоритму кешування.
         * @param key Ключ для доступу.
         */
        void access(int key);

        /**
         * @brief Вставка нового ключа в кеш з адаптивним вибором алгоритму кешування.
         * @param key Ключ для вставки.
         * @param value Значення, пов'язане з ключем.
         */
        void insert(int key, int value);

        /**
         * @brief Отримання значення за ключем.
         * @param key Ключ для пошуку.
         * @return Значення, пов'язане з ключем, або -1, якщо ключ не знайдено.
         */
        int get(int key);

        /**
         * @brief Фільтрація ключів за заданим критерієм.
         * @param predicate Функція предикат для фільтрації.
         * @return Вектор ключів, що задовольняють критерію.
         */
        std::vector<int> filter(const std::function<bool(int)>& predicate) const;

        /**
         * @brief Сортування ключів за заданим компаратором.
         * @param comparator Функція компаратор для сортування.
         * @return Відсортований вектор ключів.
         */
        std::vector<int> sort(std::function<bool(int, int)> comparator) const;

        /**
         * @brief Виведення поточного статусу кешу.
         */
        void display_cache_status() const;

        /**
        * @brief Метод, який викликається при видаленні ключа з кешу.
        * @param key Ключ, який був видалений.
        */
        void on_evict(int key) const;

    private:
    private:
        std::shared_ptr<ICache> lru_cache_; ///< Указівник на LRU кеш.
        std::shared_ptr<ICache> mru_cache_; ///< Указівник на MRU кеш.
        /*LRU_Cache lru_cache_; ///< Об'єкт кешу LRU.
        MRU_Cache mru_cache_; ///< Об'єкт кешу MRU.*/
        float dispersion_lru_, dispersion_mru_; ///< Дисперсії для LRU та MRU.
        std::unordered_map<int, int> access_frequency_; ///< Частота доступу до кожного ключа.
        std::unordered_map<int, std::chrono::steady_clock::time_point> insertion_time_; ///< Час вставки для кожного ключа.
        const double alpha_ = 0.5; ///< Коефіцієнт згладжування для розрахунків частоти.
        const std::string archive_file_path_ = "archive.txt"; ///< Шлях до файлу архіву.
        std::string last_algorithm_; ///< Останній використаний алгоритм кешування.

        /**
         * @brief Розрахунок дисперсій доступу для LRU та MRU.
         */
        void calculate_dispersions();

        /**
         * @brief Архівування ключа на основі частоти доступу.
         * @param key Ключ для архівування.
         */
        void archive(int key);

        /**
         * @brief Перевірка, чи потрібно архівувати ключ.
         * @param key Ключ для перевірки.
         * @return true, якщо потрібно архівувати, інакше false.
         */
        bool should_archive(int key) const;

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

        /**
         * @brief Видаляє ключ з кешів LRU та MRU.
         * @param key Ключ для видалення.
         */
        void remove_from_caches(int key) const;

        /**
         * @brief Відновлює ключ з архіву.
         * @param key Ключ для відновлення.
         * @return Значення ключа або -1, якщо не знайдено.
         */
        int restore_from_archive(int key) const;

        /**
         * @brief Перевіряє контрольну суму для ключа.
         * @param key Ключ для перевірки.
         * @param checksum Контрольна сума для перевірки.
         * @return true, якщо контрольна сума вірна, інакше false.
         */
        static bool verify_checksum(int key, double checksum);

        
    };

} // namespace CacheLibrary

#endif // ADAPTIVE_CACHE_HPP
