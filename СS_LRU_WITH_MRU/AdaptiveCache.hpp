#ifndef ADAPTIVE_CACHE_HPP
#define ADAPTIVE_CACHE_HPP

#include "ICache.hpp"
#include "ICacheStrategy.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <chrono>
#include <memory>

namespace cache_library {

    /**
     * @class adaptive_cache
     * @brief Адаптивний кеш, який перемикається між алгоритмами LRU та MRU залежно від дисперсії доступу.
     */
    class adaptive_cache  {
    public:
        /**
         * @brief Конструктор з передачею стратегії кешування.
         * @param strategy Указівник на стратегію вибору кешу.
         */
        explicit adaptive_cache(std::shared_ptr<ICacheStrategy> strategy);

        /**
         * @brief Конструктор з передачею кешів LRU та MRU.
         * @param lru_cache Указівник на LRU кеш.
         * @param mru_cache Указівник на MRU кеш.
         */
        adaptive_cache(std::shared_ptr<ICache> lru_cache, std::shared_ptr<ICache> mru_cache);

        void insert(int key, int value);
        int get(int key);
        std::vector<int> filter(const std::function<bool(int)>& predicate) const;
        std::vector<int> sort(std::function<bool(int, int)> comparator) const;
        void display_cache_status() const;

    private:
        std::shared_ptr<ICacheStrategy> cacheStrategy; ///< Указівник на стратегію кешування.

        // Інші приватні члени, якщо необхідно
    };

} // namespace cache_library

#endif // ADAPTIVE_CACHE_HPP
