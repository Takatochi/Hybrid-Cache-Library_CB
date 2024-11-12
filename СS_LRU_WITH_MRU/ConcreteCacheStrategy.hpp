#ifndef CONCRETECACHESTRATEGY_HPP
#define CONCRETECACHESTRATEGY_HPP

#include <chrono>
#include "ICacheStrategy.hpp"
#include "ICache.hpp"
#include <memory>
#include <unordered_map>

namespace cache_library {

    /**
     * @class concrete_cache_strategy
     * @brief Реалізація стратегії вибору кешу.
     */
    class concrete_cache_strategy : public ICacheStrategy {
    public:
        concrete_cache_strategy(std::shared_ptr<ICache> lru_cache, std::shared_ptr<ICache> mru_cache);

        std::shared_ptr<ICache> select_cache(int key) override;
        void update_strategy(int key) override;

        // Реалізуємо методи доступу до кешів
        std::shared_ptr<ICache> lruCache() const override;
        std::shared_ptr<ICache> mruCache() const override;

    private:
        std::shared_ptr<ICache> lru_cache_;
        std::shared_ptr<ICache> mru_cache_;

        // Data structures for tracking access frequencies and times
        std::unordered_map<int, double> accessFrequency_;
        std::unordered_map<int, std::chrono::steady_clock::time_point> insertionTime_;

        // Dispersion values
        double dispersionLRU_;
        double dispersionMRU_;

        const double alpha_ = 0.5; ///< Коефіцієнт згладжування для розрахунків частоти. / @en Smoothing coefficient for frequency calculations.

        void calculate_dispersions();
    };

} // namespace cache_library

#endif // CONCRETECACHESTRATEGY_HPP
