#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include "ICache.hpp"
#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>

namespace cache_library {

    /**
     * @class LRU_Cache
     * @brief Реалізація кешу з алгоритмом LRU (Least Recently Used).
     * @en Cache implementation with LRU (Least Recently Used) algorithm 
     */
    class LRU_Cache : public ICache {
    public:
        /**
         * @brief Конструктор для ініціалізації кешу з заданою місткістю.
         * @en Constructor to initialize the cache with a given capacity.
         * @param capacity Місткість кешу.
         * @en Cache capacity.
         */
        LRU_Cache(int capacity = 10);

        void insert(int key, int value) override;
        int get(int key) override;
        bool contains(int key) const override;
        void remove(int key) override;
        void display_status() const override;
        std::vector<int> get_keys() const override;
        std::string getStrategyName() const override;
    private:
        std::list<int> cache_keys_;
        std::unordered_map<int, std::list<int>::iterator> key_map_;
        std::unordered_map<int, int> value_map_; ///< Відображення ключів на значення.
        int capacity_;
    };

} // namespace CacheLibrary

#endif // LRU_CACHE_HPP
