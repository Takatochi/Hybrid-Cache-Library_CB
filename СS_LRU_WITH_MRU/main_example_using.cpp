#include "AdaptiveCache.hpp"
#include "LRU_Cache.hpp"
#include "MRU_Cache.hpp"
#include "ConcreteCacheStrategy.hpp"

int main() {
    using namespace cache_library;
    // Initialize caches and strategy
    auto lruCache = std::make_shared<LRU_Cache>(5);
    auto mruCache = std::make_shared<MRU_Cache>(5);

    // TODO Add abstraction 
    //auto strategy = std::make_shared<ConcreteCacheStrategy>(lruCache, mruCache);
    //AdaptiveCache cache(strategy);

   // При створенні adaptive_cache
    auto strategy = std::make_shared<concrete_cache_strategy>(lruCache, mruCache);
    adaptive_cache cache(strategy);


 

    // Insert data
    cache.insert(1, 100);
    cache.insert(2, 200);
    cache.insert(3, 300);

    // Access data
    int value = cache.get(2);
    std::cout << "Value for key 2: " << value << '\n';

    // Filter data
    auto filtered_keys = cache.filter([](int key) { return key > 1; });
    std::cout << "Filtered keys: ";
    for (int key : filtered_keys) {
        std::cout << key << " ";
    }
    std::cout << '\n';

    // Sort data
    auto sorted_keys = cache.sort([](int a, int b) { return a < b; });
    std::cout << "Sorted keys: ";
    for (int key : sorted_keys) {
        std::cout << key << " ";
    }
    std::cout << '\n';

    // Display cache status
    cache.display_cache_status();

    return 0;
}
