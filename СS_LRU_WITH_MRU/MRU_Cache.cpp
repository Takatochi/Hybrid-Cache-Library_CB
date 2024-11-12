#include "MRU_Cache.hpp"

namespace CacheLibrary {

    void MRU_Cache::insert(const int key, int value) {
        if (!key_map_.contains(key)) {
            if (cache_keys_.size() >= capacity_) {
	            const int first_key = cache_keys_.front();
                cache_keys_.pop_front();
                key_map_.erase(first_key);
                std::cout << "MRU: Delete the most recent key: " << first_key << '\n';
            }
        }
        else {
            cache_keys_.erase(key_map_[key]);
        }
        cache_keys_.push_back(key);
        key_map_[key] = --cache_keys_.end();
        std::cout << "MRU: Adding a key: " << key << " to the MRU cache." << '\n';
    }

    int MRU_Cache::get(const int key) {
        if (key_map_.contains(key)) {
            cache_keys_.splice(cache_keys_.end(), cache_keys_, key_map_[key]);
            return *key_map_[key];
        }
        return -1;
    }

    bool MRU_Cache::contains(const int key) const {
        return key_map_.contains(key);
    }

    void MRU_Cache::display_status() const {
        std::cout << "MRU Cache Status:\n";
        for (const int key : cache_keys_) {
            std::cout << "Key: " << key << " ";
        }
        std::cout << '\n';
    }

} // namespace CacheLibrary
