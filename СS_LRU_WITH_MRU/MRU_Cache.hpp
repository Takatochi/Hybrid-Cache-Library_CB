#ifndef MRU_CACHE_HPP
#define MRU_CACHE_HPP

#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>

namespace cache_library {

    class AdaptiveCache; // Попереднє оголошення
    /**
     * @class MRU_Cache
     * @brief Реалізація кешу з алгоритмом MRU (Most Recently Used).
     */
    class MRU_Cache {
    public:
        /**
         * @brief Вставка ключа у кеш з видаленням найновішого при переповненні.
         * @param key Ключ для збереження в кеші.
         * @param value Значення, яке буде прив'язано до ключа.
         */
        void insert(int key, int value, AdaptiveCache* parent_cache);

        /**
         * @brief Отримання значення за ключем з оновленням його у кеші.
         * @param key Ключ, який потрібно отримати.
         * @return Значення ключа або -1, якщо ключа немає в кеші.
         */
        int get(int key);

        /**
         * @brief Перевірка, чи є ключ у кеші.
         * @param key Ключ для перевірки.
         * @return true, якщо ключ є в кеші, інакше false.
         */
        [[nodiscard]] bool contains(int key) const;

        /**
         * @brief Видалення ключа з кешу.
         * @param key Ключ для видалення.
         */
        void remove(int key);

        /**
         * @brief Виводить поточний статус кешу.
         */
        void display_status() const;

        /**
         * @brief Отримує всі ключі в кеші.
         * @return Вектор ключів.
         */
        std::vector<int> get_keys() const;

    private:
        std::list<int> cache_keys_; ///< Список ключів у кеші.
        std::unordered_map<int, std::list<int>::iterator> key_map_; ///< Відображення ключів на їхні позиції в списку.
        int capacity_ = 10; ///< Максимальна кількість елементів у кеші.
    };

} // namespace CacheLibrary

#endif // MRU_CACHE_HPP
