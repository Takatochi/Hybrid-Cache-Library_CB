#ifndef MRU_CACHE_HPP
#define MRU_CACHE_HPP

#include "ICache.hpp"
#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>

namespace cache_library {

    /**
     * @class MRU_Cache
     * @brief Реалізація кешу з алгоритмом MRU (Most Recently Used).
     * @en Implementation of cache with MRU (Most Recently Used) algorithm.
     */
    class MRU_Cache : public ICache {
    public:
        /**
		 * @brief Конструктор для ініціалізації кешу з заданою місткістю.
		 * @en Constructor to initialize the cache with a given capacity.
		 * @param capacity Місткість кешу.
		 * @en Cache capacity.
		 */
        MRU_Cache(int capacity = 10);

        void insert(int key, int value) override;
        int get(int key) override;
        bool contains(int key) const override;
        void remove(int key) override;
        void display_status() const override;
        std::vector<int> get_keys() const override;

    private:
        std::list<int> cache_keys_;
        std::unordered_map<int, std::list<int>::iterator> key_map_;
        int capacity_;
    };

} // namespace CacheLibrary

#endif // MRU_CACHE_HPP
