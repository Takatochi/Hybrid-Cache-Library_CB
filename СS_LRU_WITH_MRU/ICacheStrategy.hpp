#ifndef ICACHESTRATEGY_HPP
#define ICACHESTRATEGY_HPP

#include "ICache.hpp"
#include <memory>

namespace cache_library {

    /**
     * @class ICacheStrategy
     * @brief Інтерфейс для стратегій вибору кешу.
     */
    class ICacheStrategy {
    public:
        virtual ~ICacheStrategy() = default;

        /**
         * @brief Вибирає відповідний кеш для даного ключа.
         * @param key Ключ для вставки.
         * @return Указівник на обраний кеш.
         */
        virtual std::shared_ptr<ICache> select_cache(int key) = 0;

        /**
         * @brief Оновлює стратегію на основі доступу до ключа.
         * @param key Ключ для оновлення.
         */
        virtual void update_strategy(int key) = 0;

        /**
         * @brief Отримує указівник на LRU кеш.
         * @return Указівник на LRU кеш.
         */
        virtual std::shared_ptr<ICache> lruCache() const = 0;

        /**
         * @brief Отримує указівник на MRU кеш.
         * @return Указівник на MRU кеш.
         */
        virtual std::shared_ptr<ICache> mruCache() const = 0;

    };

} // namespace cache_library

#endif // ICACHESTRATEGY_HPP
