#include "MRU_Cache.hpp"

#include "AdaptiveCache.hpp"

namespace cache_library {

    MRU_Cache::MRU_Cache(const int capacity) : capacity_(capacity) {}

    void MRU_Cache::insert(const int key, const int value) {
        if (!key_map_.contains(key)) {
            if (cache_keys_.size() >= capacity_) {
	            const int first_key = cache_keys_.front();
                cache_keys_.pop_front();
                key_map_.erase(first_key);
            }
        }
        else {
            cache_keys_.erase(key_map_[key]);
        }
        cache_keys_.push_back(key);
        key_map_[key] = --cache_keys_.end();
        value_map_[key] = value; // Зберігаємо значення
    }

    int MRU_Cache::get(const int key) {
        if (key_map_.contains(key)) {
            cache_keys_.erase(key_map_[key]);
            cache_keys_.push_back(key);
            key_map_[key] = --cache_keys_.end();
            return value_map_[key]; // Повертаємо значення
        }
        return -1; // Або використовуйте інший спосіб обробки відсутнього ключа
    }

    bool MRU_Cache::contains(const int key) const {
        return key_map_.contains(key);
    }

    void MRU_Cache::remove(const int key) {
        if (key_map_.contains(key)) {
            cache_keys_.erase(key_map_.at(key));
            key_map_.erase(key);
            value_map_.erase(key); // Видаляємо значення
        }
    }

    void MRU_Cache::display_status() const {
        std::cout << "MRU Cache Status:\n";
        for (const int key : cache_keys_) {
            std::cout << "Key: " << key << ", Value: " << value_map_.at(key) << " ";
        }
        std::cout << '\n';
    }

    std::vector<int> MRU_Cache::get_keys() const {
        return { cache_keys_.begin(), cache_keys_.end() };
    }

    std::string MRU_Cache::getStrategyName() const {
        return "MRU";
    }


} // namespace CacheLibrary
