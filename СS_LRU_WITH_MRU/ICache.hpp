#ifndef ICACHE_HPP
#define ICACHE_HPP

#include <vector>

namespace cache_library {

    /**
 * @class ICache
 * @brief Абстрактний інтерфейс для кешів.
 * @en Abstract interface for caches.
 */
    class ICache {
    public:
        virtual ~ICache() = default;

        /**
         * @brief Вставка ключа у кеш.
         * @en Insert a key into the cache.
         * @param key Ключ для збереження в кеші.
         * @en Key to store in the cache.
         * @param value Значення, яке буде прив'язано до ключа.
         * @en Value to associate with the key.
         */
        virtual void insert(int key, int value) = 0;

        /**
         * @brief Отримання значення за ключем.
         * @en Retrieve a value by key.
         * @param key Ключ, який потрібно отримати.
         * @en Key to retrieve.
         * @return Значення ключа або -1, якщо ключа немає в кеші.
         * @en Value of the key or -1 if the key is not in the cache.
         */
        virtual int get(int key) = 0;

        /**
         * @brief Перевірка, чи є ключ у кеші.
         * @en Check if a key is in the cache.
         * @param key Ключ для перевірки.
         * @en Key to check.
         * @return true, якщо ключ є в кеші, інакше false.
         * @en true if the key is in the cache, otherwise false.
         */
        virtual bool contains(int key) const = 0;

        /**
         * @brief Видалення ключа з кешу.
         * @en Remove a key from the cache.
         * @param key Ключ для видалення.
         * @en Key to remove.
         */
        virtual void remove(int key) = 0;

        /**
         * @brief Виводить поточний статус кешу.
         * @en Display the current status of the cache.
         */
        virtual void display_status() const = 0;

        /**
         * @brief Отримує всі ключі в кеші.
         * @en Retrieve all keys in the cache.
         * @return Вектор ключів.
         * @en Vector of keys.
         */
        virtual std::vector<int> get_keys() const = 0;
    };


} // namespace CacheLibrary

#endif // ICACHE_HPP
