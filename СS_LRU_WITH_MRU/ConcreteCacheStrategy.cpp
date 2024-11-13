#include "ConcreteCacheStrategy.hpp"
#include <cmath>
#include <iostream>

namespace cache_library {

    concrete_cache_strategy::concrete_cache_strategy(std::shared_ptr<i_cache> lru_cache, std::shared_ptr<i_cache> mru_cache)
        : lru_cache_(std::move(lru_cache)), mru_cache_(std::move(mru_cache)), dispersionLRU_(0.0), dispersionMRU_(0.0){}

    std::shared_ptr<i_cache> concrete_cache_strategy::select_cache(int key) {
        // Вибираємо кеш на основі дисперсії

        if (dispersionLRU_ < dispersionMRU_) {
            return lru_cache_;
            
        }
        else {
            return mru_cache_;
        }
    }

    void concrete_cache_strategy::update_strategy(int key) {
        
	    constexpr double start = 1.0;
        // Update access frequency
	    const auto now = std::chrono::steady_clock::now();

        if (!accessFrequency_.contains(key)) {
            // Ініціалізуємо частоту доступу
            accessFrequency_[key] = start;
            insertionTime_[key] = now;
        }
        else {
            // Оновлюємо частоту доступу з експоненціальним згладжуванням
            accessFrequency_[key] = alpha_ * start + (1.0 - alpha_) * accessFrequency_[key];
        }

     /*   std::cout << accessFrequency_[key];*/
        // Recalculate dispersions
        calculate_dispersions();
    }

    void concrete_cache_strategy::calculate_dispersions() {
        double sum_lru = 0.0, sum_mru = 0.0;
        double mean_lru = 0.0, mean_mru = 0.0;
        int count_lru = 0, count_mru = 0;
        // Перевіряємо, скільки ключів в LRU кеші
       

        // Calculate mean access frequency for LRU and MRU caches
        for (const auto& [key, freq] : accessFrequency_) {
            if (lru_cache_->contains(key)) {
                mean_lru += freq;
                count_lru++;
            }
            else if (mru_cache_->contains(key)) {
                mean_mru += freq;
                count_mru++;
            }
        }

        // Оновлюємо члени класу
        if (count_lru > 0) dispersionLRU_ = sum_lru / count_lru;
        else dispersionLRU_ = 0.0;

        if (count_mru > 0) dispersionMRU_ = sum_mru / count_mru;
        else dispersionMRU_ = 0.0;

        // Calculate dispersion for LRU and MRU caches
        for (const auto& [key, freq] : accessFrequency_) {
            if (lru_cache_->contains(key)) {
                sum_lru += std::pow(freq - mean_lru, 2);
            }
            else if (mru_cache_->contains(key)) {
                sum_mru += std::pow(freq - mean_mru, 2);
            }
        }
     /*   std::cout << dispersionLRU_ << " and " << dispersionMRU_ << " ";*/
        if (count_lru > 0) dispersionLRU_ = sum_lru / count_lru;
        if (count_mru > 0) dispersionMRU_ = sum_mru / count_mru;

    }

    // Реалізація методів доступу до кешів
    std::shared_ptr<i_cache> concrete_cache_strategy::lruCache() const {
        return lru_cache_;
    }

    std::shared_ptr<i_cache> concrete_cache_strategy::mruCache() const {
        return mru_cache_;
    }

} // namespace cache_library
