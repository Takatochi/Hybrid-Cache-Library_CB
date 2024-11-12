#include "LRU_Cache.hpp"

namespace CacheLibrary {

    void LRU_Cache::insert(const int key, int value) {
        if (!key_map_.contains(key)) {
            if (cache_keys_.size() >= capacity_) {
	            const int last_key = cache_keys_.back();
                cache_keys_.pop_back();
                key_map_.erase(last_key);
            }
        }
        else {
            cache_keys_.erase(key_map_[key]);
        }
        cache_keys_.push_front(key);
        key_map_[key] = cache_keys_.begin();
    }

    int LRU_Cache::get(const int key) {
        if (key_map_.contains(key)) {
            cache_keys_.splice(cache_keys_.begin(), cache_keys_, key_map_[key]);
            return *key_map_[key];
        }
        return -1;
    }

    bool LRU_Cache::contains(const int key) const {
        return key_map_.contains(key);
    }

    void LRU_Cache::display_status() const {
        std::cout << "LRU Cache Status:\n";
        for (const int key : cache_keys_) {
            std::cout << "Key: " << key << " ";
        }
        std::cout << '\n';
    }

} // namespace CacheLibrary
