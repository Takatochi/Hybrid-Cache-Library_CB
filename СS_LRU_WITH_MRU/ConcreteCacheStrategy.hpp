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
     * @brief ��������� ������㳿 ������ ����.
     */
    class concrete_cache_strategy : public i_cache_strategy {
    public:
        concrete_cache_strategy(std::shared_ptr<i_cache> lru_cache, std::shared_ptr<i_cache> mru_cache);

        std::shared_ptr<i_cache> select_cache(int key) override;
        void update_strategy(int key) override;

        // �������� ������ ������� �� �����
        std::shared_ptr<i_cache> lruCache() const override;
        std::shared_ptr<i_cache> mruCache() const override;

    private:
        std::shared_ptr<i_cache> lru_cache_;
        std::shared_ptr<i_cache> mru_cache_;

        // Data structures for tracking access frequencies and times
        std::unordered_map<int, double> accessFrequency_;
        std::unordered_map<int, std::chrono::steady_clock::time_point> insertionTime_;

        // Dispersion values
        double dispersionLRU_;
        double dispersionMRU_;

        const double alpha_ = 0.5; ///< ���������� ������������ ��� ���������� �������. / @en Smoothing coefficient for frequency calculations.

        void calculate_dispersions();
    };

} // namespace cache_library

#endif // CONCRETECACHESTRATEGY_HPP
