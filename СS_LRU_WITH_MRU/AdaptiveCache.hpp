#ifndef ADAPTIVE_CACHE_HPP
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
     * @en Adaptive cache that switches between LRU and MRU algorithms depending on access dispersion.
     */
    class adaptive_cache {
    public:
        /**
         * @brief Конструктор для ініціалізації адаптивного кешу.
         * @en Constructor for initializing adaptive cache.
         * @param lruCache Указівник на LRU кеш.
         * @en Pointer to the LRU cache.
         * @param mruCache Указівник на MRU кеш.
         * @en Pointer to the MRU cache.
         */
        adaptive_cache(std::shared_ptr<ICache> lruCache, std::shared_ptr<ICache> mruCache);
    

        /**
         * @brief Доступ до ключа з адаптивним вибором алгоритму кешування.
         * @en Access a key with adaptive caching algorithm selection.
         * @param key Ключ для доступу.
         * @en Key to access.
         */
        void access(int key);

        /**
         * @brief Вставка нового ключа в кеш з адаптивним вибором алгоритму кешування.
         * @en Insert a new key with adaptive caching algorithm selection.
         * @param key Ключ для вставки.
         * @en Key to insert.
         * @param value Значення, пов'язане з ключем.
         * @en Value associated with the key.
         */
        void insert(int key, int value);

        /**
         * @brief Отримання значення за ключем.
         * @en Retrieve value by key.
         * @param key Ключ для пошуку.
         * @en Key to look up.
         * @return Значення, пов'язане з ключем, або -1, якщо ключ не знайдено.
         * @en Value associated with the key or -1 if key is not found.
         */
        int get(int key);

        /**
         * @brief Фільтрація ключів за заданим критерієм.
         * @en Filter keys by specified criterion.
         * @param predicate Функція предикат для фільтрації.
         * @en Predicate function for filtering.
         * @return Вектор ключів, що задовольняють критерію.
         * @en Vector of keys that satisfy the criterion.
         */
        std::vector<int> filter(const std::function<bool(int)>& predicate) const;

        /**
         * @brief Сортування ключів за заданим компаратором.
         * @en Sort keys by specified comparator.
         * @param comparator Функція компаратор для сортування.
         * @en Comparator function for sorting.
         * @return Відсортований вектор ключів.
         * @en Sorted vector of keys.
         */
        std::vector<int> sort(std::function<bool(int, int)> comparator) const;

        /**
         * @brief Виведення поточного статусу кешу.
         * @en Display the current status of the cache.
         */
        void display_cache_status() const;

        /**
         * @brief Метод, який викликається при видаленні ключа з кешу.
         * @en Method called when a key is evicted from the cache.
         * @param key Ключ, який був видалений.
         * @en Key that was evicted.
         */
        void on_evict(int key) const;

    private:
    private:
       std::shared_ptr<ICache> lru_cache_; ///< Указівник на LRU кеш. / @en Pointer to LRU cache.
        std::shared_ptr<ICache> mru_cache_; ///< Указівник на MRU кеш. / @en Pointer to MRU cache.
        
        float dispersion_lru_, dispersion_mru_; ///< Дисперсії для LRU та MRU. / @en Dispersions for LRU and MRU.
        std::unordered_map<int, int> access_frequency_; ///< Частота доступу до кожного ключа. / @en Access frequency for each key.
        std::unordered_map<int, std::chrono::steady_clock::time_point> insertion_time_; ///< Час вставки для кожного ключа. / @en Insertion time for each key.
        const double alpha_ = 0.5; ///< Коефіцієнт згладжування для розрахунків частоти. / @en Smoothing coefficient for frequency calculations.
        const std::string archive_file_path_ = "archive.txt"; ///< Шлях до файлу архіву. / @en Path to archive file.
        std::string last_algorithm_; ///< Останній використаний алгоритм кешування. / @en Last used caching algorithm.

        /**
           * @brief Розрахунок дисперсій доступу для LRU та MRU.
           * @en Calculate access dispersions for LRU and MRU.
           */
        void calculate_dispersions();

        /**
         * @brief Архівування ключа на основі частоти доступу.
         * @en Archive a key based on access frequency.
         * @param key Ключ для архівування.
         * @en Key to archive.
         */
        void archive(int key);

        /**
          * @brief Перевірка, чи потрібно архівувати ключ.
          * @en Check if a key needs to be archived.
          * @param key Ключ для перевірки.
          * @en Key to check.
          * @return true, якщо потрібно архівувати, інакше false.
          * @en true if archiving is required, otherwise false.
          */
        bool should_archive(int key) const;

        /**
       * @brief Обчислює SHA-256 контрольну суму для даних.
       * @en Computes SHA-256 checksum for data.
       * @param data Дані для хешування.
       * @en Data to hash.
       * @return Контрольна сума у вигляді числа з плаваючою точкою.
       * @en Checksum as a floating-point number.
       */
        static double calculate_sha256(const std::string& data);

        /**
       * @brief Записує ключ і його контрольну суму у файл архіву.
       * @en Write key and its checksum to archive file.
       * @param key Ключ для запису.
       * @en Key to record.
       * @param checksum Контрольна сума для ключа.
       * @en Checksum for the key.
       */
        void write_to_archive_file(int key, double checksum) const;

        /**
        * @brief Видаляє ключ з кешів LRU та MRU.
        * @en Remove a key from LRU and MRU caches.
        * @param key Ключ для видалення.
        * @en Key to remove.
        */
        void remove_from_caches(int key) const;

        /**
         * @brief Відновлює ключ з архіву.
         * @en Restore a key from the archive.
         * @param key Ключ для відновлення.
         * @en Key to restore.
         * @return Значення ключа або -1, якщо не знайдено.
         * @en Value of the key or -1 if not found.
         */
        int restore_from_archive(int key) const;

        /**
        * @brief Перевіряє контрольну суму для ключа.
        * @en Verify the checksum for a key.
        * @param key Ключ для перевірки.
        * @en Key to verify.
        * @param checksum Контрольна сума для перевірки.
        * @en Checksum to validate.
        * @return true, якщо контрольна сума вірна, інакше false.
        * @en true if checksum is correct, otherwise false.
        */
        static bool verify_checksum(int key, double checksum);

        
    };

} // namespace CacheLibrary

#endif // ADAPTIVE_CACHE_HPP
