﻿#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <list>
#include <unordered_map>
#include <iostream>

namespace CacheLibrary {

    /**
     * @class LRU_Cache
     * @brief Реалізація кешу з алгоритмом LRU (Least Recently Used).
     */
    class LRU_Cache {
    public:
        /**
         * @brief Вставка ключа у кеш з видаленням найстарішого при переповненні.
         * @param key Ключ для збереження в кеші.
         * @param value Значення, яке буде прив'язано до ключа (не використовується тут).
         */
        void insert(int key, int value);

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
         * @brief Виводить поточний статус кешу.
         */
        void display_status() const;

    private:
        std::list<int> cacheKeys; ///< Список ключів у кеші.
        std::unordered_map<int, std::list<int>::iterator> keyMap; ///< Відображення ключів на їхні позиції в списку.
        int capacity = 10; ///< Максимальна кількість елементів у кеші.
    };

} // namespace CacheLibrary

#endif // LRU_CACHE_HPP
