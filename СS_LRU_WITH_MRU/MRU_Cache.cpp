#include "MRU_Cache.hpp"

namespace CacheLibrary {

    void MRU_Cache::insert(const int key, int value) {
        if (!keyMap.contains(key)) {
            if (cacheKeys.size() >= capacity) {
	            const int first_key = cacheKeys.front();
                cacheKeys.pop_front();
                keyMap.erase(first_key);
                std::cout << "MRU: Delete the most recent key: " << first_key << '\n';
            }
        }
        else {
            cacheKeys.erase(keyMap[key]);
        }
        cacheKeys.push_back(key);
        keyMap[key] = --cacheKeys.end();
        std::cout << "MRU: Adding a key: " << key << " to the MRU cache." << '\n';
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
        std::cout << '\n';
    }

} // namespace CacheLibrary
