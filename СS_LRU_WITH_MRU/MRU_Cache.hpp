#ifndef MRU_CACHE_HPP
#define MRU_CACHE_HPP

#include "ICache.hpp"
#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>

namespace cache_library {

    /**
     * @class mru_cache
     * @brief Реалізація кешу з алгоритмом MRU (Most Recently Used).
     * @en Implementation of cache with MRU (Most Recently Used) algorithm.
     */
    class mru_cache final : public i_cache {
    public:
        /**
		 * @brief Конструктор для ініціалізації кешу з заданою місткістю.
		 * @en Constructor to initialize the cache with a given capacity.
		 * @param capacity Місткість кешу.
		 * @en Cache capacity.
		 */
        explicit mru_cache(int capacity = 10);

        void insert(int key, int value) override;
        int get(int key) override;
        [[nodiscard]] bool contains(int key) const override;
        void remove(int key) override;
        void display_status() const override;
        [[nodiscard]] std::vector<int> get_keys() const override;
        [[nodiscard]] std::string get_strategy_name() const override;

    private:
        std::list<int> cache_keys_;
        std::unordered_map<int, std::list<int>::iterator> key_map_;
        std::unordered_map<int, int> value_map_; ///< Відображення ключів на значення.
        int capacity_;
    };

} // namespace CacheLibrary

#endif // MRU_CACHE_HPP
