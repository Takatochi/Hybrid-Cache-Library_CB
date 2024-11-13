#include "LRU_Cache.hpp"

namespace cache_library {

    lru_cache::lru_cache(const int capacity) : capacity_(capacity) {}

    void lru_cache::insert(const int key, const int value) {
        if (!key_map_.contains(key)) {
            if (cache_keys_.size() >= capacity_) {
	            const int last_key = cache_keys_.back();
                cache_keys_.pop_back();
                key_map_.erase(last_key);
                value_map_.erase(last_key); // Видаляємо значення
            }
        }
        else {
            cache_keys_.erase(key_map_[key]);
        }
        cache_keys_.push_front(key);
        key_map_[key] = cache_keys_.begin();
        value_map_[key] = value; // Зберігаємо значення
    }

    int lru_cache::get(const int key) {
        if (key_map_.contains(key)) {
            cache_keys_.erase(key_map_[key]);
            cache_keys_.push_front(key);
            key_map_[key] = cache_keys_.begin();
            return value_map_[key]; // Повертаємо значення
        }
        return -1; // Або використовуйте інший спосіб обробки відсутнього ключа
    }

    bool lru_cache::contains(const int key) const {
        return key_map_.contains(key);
    }

    void lru_cache::remove(const int key) {
        if (key_map_.contains(key)) {
            cache_keys_.erase(key_map_.at(key));
            key_map_.erase(key);
            value_map_.erase(key); // Видаляємо значення
        }
    }

    void lru_cache::display_status() const {
        std::cout << "LRU Cache Status:\n";
        for (const int key : cache_keys_) {
            std::cout << "Key: " << key << ", Value: " << value_map_.at(key) << " ";
        }
        std::cout << '\n';
    }

    std::vector<int> lru_cache::get_keys() const {
        return { cache_keys_.begin(), cache_keys_.end() };
    }

    std::string lru_cache::get_strategy_name() const {
        return "LRU";
    }

} // namespace CacheLibrary
