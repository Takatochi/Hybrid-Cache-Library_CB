#include "MRU_Cache.hpp"

namespace CacheLibrary {

    void MRU_Cache::insert(const int key, int value) {
        if (!keyMap.contains(key)) {
            if (cacheKeys.size() >= capacity) {
	            const int firstKey = cacheKeys.front();
                cacheKeys.pop_front();
                keyMap.erase(firstKey);
                std::cout << "MRU: Delete the most recent key: " << firstKey << std::endl;
            }
        }
        else {
            cacheKeys.erase(keyMap[key]);
        }
        cacheKeys.push_back(key);
        keyMap[key] = --cacheKeys.end();
        std::cout << "MRU: Adding a key: " << key << " to the MRU cache." << std::endl;
    }

    int MRU_Cache::get(const int key) {
        if (keyMap.contains(key)) {
            cacheKeys.splice(cacheKeys.end(), cacheKeys, keyMap[key]);
            return *keyMap[key];
        }
        return -1;
    }

    bool MRU_Cache::contains(const int key) const {
        return keyMap.contains(key);
    }

    void MRU_Cache::display_status() const {
        std::cout << "MRU Cache Status:\n";
        for (const int key : cacheKeys) {
            std::cout << "Key: " << key << " ";
        }
        std::cout << std::endl;
    }

} // namespace CacheLibrary
