#ifndef ADAPTIVE_CACHE_HPP
#define ADAPTIVE_CACHE_HPP

#include "LRU_Cache.hpp"
#include "MRU_Cache.hpp"
#include <unordered_map>
#include <string>

namespace CacheLibrary {

    /**
     * @class AdaptiveCache
     * @brief ���������� ���, ���� ������������ �� ����������� LRU �� MRU ������� �� ������� �������.
     */
    class AdaptiveCache {
    public:
        /**
         * @brief ����������� ��� ����������� ����������� ����.
         */
        AdaptiveCache();

        /**
         * @brief ������ �� ����� � ���������� ������� ��������� ���������.
         * @param key ���� ��� �������.
         */
        void access(int key);

        /**
         * @brief ����������� ����� �� ����� ������� �������.
         * @param key ���� ��� �����������.
         */
        void archive(int key);

        /**
         * @brief ���������� �������� ������� ��� LRU �� MRU.
         */
        void calculate_dispersions();

        /**
         * @brief ��������� ��������� ������� ����.
         */
        void display_cache_status() const;

    private:
        LRU_Cache lruCache; ///< ��'��� ���� LRU.
        MRU_Cache mruCache; ///< ��'��� ���� MRU.
        float dispersionLRU, dispersionMRU; ///< ������� ��� LRU �� MRU.
        std::unordered_map<int, int> accessFrequency; ///< ������� ������� �� ������� �����.
        std::unordered_map<int, double> insertionTime; ///< ��� ������� ��� ������� �����.
        const double alpha = 0.5; ///< ���������� ������������ ��� ���������� �������.
        const std::string archiveFilePath = "archive.txt"; ///< ���� �� ����� ������.
        std::string lastAlgorithm; ///< ������� ������������ �������� ���������.

        /**
         * @brief �������� SHA-256 ���������� ���� ��� �����.
         * @param data ��� ��� ���������.
         * @return ���������� ���� � ������ ����� � ��������� ������.
         */
        static double calculate_sha256(const std::string& data);

        /**
         * @brief ������ ���� � ���� ���������� ���� � ���� ������.
         * @param key ���� ��� ������.
         * @param checksum ���������� ���� ��� �����.
         */
        void write_to_archive_file(int key, double checksum) const;
    };

} // namespace CacheLibrary

#endif // ADAPTIVE_CACHE_HPP
