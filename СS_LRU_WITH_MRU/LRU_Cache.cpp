#include "LRU_Cache.hpp"

namespace CacheLibrary {

    void LRU_Cache::insert(const int key, int value) {
        if (!keyMap.contains(key)) {
            if (cacheKeys.size() >= capacity) {
                int lastKey = cacheKeys.back();
                cacheKeys.pop_back();
                keyMap.erase(lastKey);
            }
        }
        else {
            cacheKeys.erase(keyMap[key]);
        }
        cacheKeys.push_front(key);
        keyMap[key] = cacheKeys.begin();
    }

    int LRU_Cache::get(const int key) {
        if (keyMap.contains(key)) {
            cacheKeys.splice(cacheKeys.begin(), cacheKeys, keyMap[key]);
            return *keyMap[key];
        }
        return -1;
    }

    bool LRU_Cache::contains(const int key) const {
        return keyMap.contains(key);
    }

    void LRU_Cache::display_status() const {
        std::cout << "LRU Cache Status:\n";
        for (const int key : cacheKeys) {
            std::cout << "Key: " << key << " ";
        }
        std::cout << std::endl;
    }

} // namespace CacheLibrary
