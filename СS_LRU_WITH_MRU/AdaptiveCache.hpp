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
         * @param lru_cache_ptr Указівник на LRU кеш.
         * @param mru_cache_ptr Указівник на MRU кеш.
         */
        adaptive_cache(const std::shared_ptr<ICache>& lru_cache_ptr, const std::shared_ptr<ICache>& mru_cache_ptr);

        void insert(int key, int value) const;
        int get(int key) const;
        std::vector<int> filter(const std::function<bool(int)>& predicate) const;
        std::vector<int> sort(std::function<bool(int, int)> comparator) const;
        void display_cache_status() const;

    private:
        std::shared_ptr<ICacheStrategy> cacheStrategy; ///< Указівник на стратегію кешування.
        const std::string archiveFilePath_ = "archive.txt"; ///< Шлях до файлу архіву.
        std::string last_algorithm_; ///< Останній використаний алгоритм кешування.
        static double calculate_sha256(const std::string& data);
        void write_to_archive_file(int key, double checksum) const;
        // Інші приватні члени, якщо необхідно
    };

} // namespace cache_library

#endif // ADAPTIVE_CACHE_HPP
