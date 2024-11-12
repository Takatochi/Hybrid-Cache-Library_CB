#ifndef ICACHE_HPP
#define ICACHE_HPP

#include <vector>

namespace cache_library {

    /**
     * @class ICache
     * @brief Абстрактний інтерфейс для кешів.
     */
    class ICache {
    public:
        virtual ~ICache() = default;

        /**
         * @brief Вставка ключа у кеш.
         * @param key Ключ для збереження в кеші.
         * @param value Значення, яке буде прив'язано до ключа.
         */
        virtual void insert(int key, int value) = 0;

        /**
         * @brief Отримання значення за ключем.
         * @param key Ключ, який потрібно отримати.
         * @return Значення ключа або -1, якщо ключа немає в кеші.
         */
        virtual int get(int key) = 0;

        /**
         * @brief Перевірка, чи є ключ у кеші.
         * @param key Ключ для перевірки.
         * @return true, якщо ключ є в кеші, інакше false.
         */
        virtual bool contains(int key) const = 0;

        /**
         * @brief Видалення ключа з кешу.
         * @param key Ключ для видалення.
         */
        virtual void remove(int key) = 0;

        /**
         * @brief Виводить поточний статус кешу.
         */
        virtual void display_status() const = 0;

        /**
         * @brief Отримує всі ключі в кеші.
         * @return Вектор ключів.
         */
        virtual std::vector<int> get_keys() const = 0;
    };

} // namespace CacheLibrary

#endif // ICACHE_HPP
