#ifndef ICACHE_HPP
#define ICACHE_HPP

#include <vector>

namespace cache_library {

    /**
     * @class ICache
     * @brief ����������� ��������� ��� �����.
     */
    class ICache {
    public:
        virtual ~ICache() = default;

        /**
         * @brief ������� ����� � ���.
         * @param key ���� ��� ���������� � ����.
         * @param value ��������, ��� ���� ����'����� �� �����.
         */
        virtual void insert(int key, int value) = 0;

        /**
         * @brief ��������� �������� �� ������.
         * @param key ����, ���� ������� ��������.
         * @return �������� ����� ��� -1, ���� ����� ���� � ����.
         */
        virtual int get(int key) = 0;

        /**
         * @brief ��������, �� � ���� � ����.
         * @param key ���� ��� ��������.
         * @return true, ���� ���� � � ����, ������ false.
         */
        virtual bool contains(int key) const = 0;

        /**
         * @brief ��������� ����� � ����.
         * @param key ���� ��� ���������.
         */
        virtual void remove(int key) = 0;

        /**
         * @brief �������� �������� ������ ����.
         */
        virtual void display_status() const = 0;

        /**
         * @brief ������ �� ����� � ����.
         * @return ������ ������.
         */
        virtual std::vector<int> get_keys() const = 0;
    };

} // namespace CacheLibrary

#endif // ICACHE_HPP
