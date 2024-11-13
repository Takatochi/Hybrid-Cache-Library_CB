#include "LRU_Cache.hpp"

namespace cache_library {

    LRU_Cache::LRU_Cache(const int capacity) : capacity_(capacity) {}

    void LRU_Cache::insert(int key, int value) {
        if (!key_map_.contains(key)) {
            if (cache_keys_.size() >= capacity_) {
                int last_key = cache_keys_.back();
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

    int LRU_Cache::get(int key) {
        if (key_map_.contains(key)) {
            cache_keys_.erase(key_map_[key]);
            cache_keys_.push_front(key);
            key_map_[key] = cache_keys_.begin();
            return value_map_[key]; // Повертаємо значення
        }
        return -1; // Або використовуйте інший спосіб обробки відсутнього ключа
    }

    bool LRU_Cache::contains(int key) const {
        return key_map_.contains(key);
    }

    void LRU_Cache::remove(int key) {
        if (key_map_.contains(key)) {
            cache_keys_.erase(key_map_.at(key));
            key_map_.erase(key);
            value_map_.erase(key); // Видаляємо значення
        }
    }

    void LRU_Cache::display_status() const {
        std::cout << "LRU Cache Status:\n";
        for (const int key : cache_keys_) {
            std::cout << "Key: " << key << ", Value: " << value_map_.at(key) << " ";
        }
        std::cout << '\n';
    }

    std::vector<int> LRU_Cache::get_keys() const {
        return { cache_keys_.begin(), cache_keys_.end() };
    }

    std::string LRU_Cache::getStrategyName() const {
        return "LRU";
    }

} // namespace CacheLibrary
