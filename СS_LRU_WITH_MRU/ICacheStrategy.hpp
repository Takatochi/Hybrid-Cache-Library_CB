#ifndef ICACHESTRATEGY_HPP
#define ICACHESTRATEGY_HPP

#include "ICache.hpp"
#include <memory>
#include <string>

namespace cache_library {

    /**
     * @class i_cache_strategy
     * @brief Інтерфейс для стратегій вибору кешу.
     */
    class i_cache_strategy {
    public:
        virtual ~i_cache_strategy() = default;

        /**
         * @brief Вибирає відповідний кеш для даного ключа.
         * @param key Ключ для вставки.
         * @return Указівник на обраний кеш.
         */
        virtual std::shared_ptr<i_cache> select_cache(int key) = 0;

        /**
         * @brief Оновлює стратегію на основі доступу до ключа.
         * @param key Ключ для оновлення.
         */
        virtual void update_strategy(int key) = 0;

        /**
         * @brief Отримує указівник на LRU кеш.
         * @return Указівник на LRU кеш.
         */
        virtual std::shared_ptr<i_cache> lruCache() const = 0;

        /**
         * @brief Отримує указівник на MRU кеш.
         * @return Указівник на MRU кеш.
         */
        virtual std::shared_ptr<i_cache> mruCache() const = 0;


    };

} // namespace cache_library

#endif // ICACHESTRATEGY_HPP
