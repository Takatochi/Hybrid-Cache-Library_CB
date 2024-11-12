#include "AdaptiveCache.hpp"
#include <iostream>
#include <algorithm>
#include <utility>
#include "ConcreteCacheStrategy.hpp"
int i = 1;
namespace cache_library {

    adaptive_cache::adaptive_cache(std::shared_ptr<ICacheStrategy> strategy)
        : cacheStrategy(std::move(strategy)) {}

    adaptive_cache::adaptive_cache(std::shared_ptr<ICache> lru_cache_ptr, std::shared_ptr<ICache> mru_cache_ptr) {
        // Створюємо стратегію за замовчуванням
        cacheStrategy = std::make_shared<concrete_cache_strategy>(lru_cache_ptr, mru_cache_ptr);
    }

    void adaptive_cache::insert(int key, int value) {
        // Вибираємо відповідний кеш
        auto cache = cacheStrategy->select_cache(key);

        // Вставляємо в обраний кеш
        cache->insert(key, value);

        // Оновлюємо стратегію з ключем
        cacheStrategy->update_strategy(key);
    }



    int adaptive_cache::get(int key) {
        int value = -1;

        auto lruCache = cacheStrategy->lruCache();
        auto mruCache = cacheStrategy->mruCache();

        if (lruCache->contains(key)) {
            value = lruCache->get(key);
            
        }
        else if (mruCache->contains(key)) {
            value = mruCache->get(key);
            
        }
        else {
            // Спробувати відновити з архіву, якщо реалізовано
        }

        if (value != -1) {
            // Оновлюємо стратегію з ключем
            cacheStrategy->update_strategy(key);
        }

        return value;
    }

    std::vector<int> adaptive_cache::filter(const std::function<bool(int)>& predicate) const {
        std::vector<int> result;

        auto lruCache = cacheStrategy->lruCache();
        auto mruCache = cacheStrategy->mruCache();

        // Фільтрація в LRU кеші
        for (const int key : lruCache->get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        // Фільтрація в MRU кеші
        for (const int key : mruCache->get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        return result;
    }

    std::vector<int> adaptive_cache::sort(std::function<bool(int, int)> comparator) const {
        auto lruCache = cacheStrategy->lruCache();
        auto mruCache = cacheStrategy->mruCache();

        std::vector<int> all_keys = lruCache->get_keys();
        std::vector<int> mru_keys = mruCache->get_keys();
        all_keys.insert(all_keys.end(), mru_keys.begin(), mru_keys.end());

        std::ranges::sort(all_keys, std::move(comparator));

        return all_keys;
    }

    void adaptive_cache::display_cache_status() const {
        std::cout << "Cache Status:\n";
        cacheStrategy->lruCache()->display_status();
        cacheStrategy->mruCache()->display_status();
    }

} // namespace cache_library
