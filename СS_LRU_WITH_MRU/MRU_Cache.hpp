#ifndef MRU_CACHE_HPP
#define MRU_CACHE_HPP

#include <list>
#include <unordered_map>
#include <iostream>

namespace CacheLibrary {

    /**
     * @class MRU_Cache
     * @brief ��������� ���� � ���������� MRU (Most Recently Used).
     */
    class MRU_Cache {
    public:
        /**
         * @brief ������� ����� � ��� � ���������� ���������� ��� �����������.
         * @param key ���� ��� ���������� � ����.
         * @param value ��������, ��� ���� ����'����� �� ����� (�� ��������������� ���).
         */
        void insert(int key, int value);

        /**
         * @brief ��������� �������� �� ������ � ���������� ���� � ����.
         * @param key ����, ���� ������� ��������.
         * @return �������� ����� ��� -1, ���� ����� ���� � ����.
         */
        int get(int key);

        /**
         * @brief ��������, �� � ���� � ����.
         * @param key ���� ��� ��������.
         * @return true, ���� ���� � � ����, ������ false.
         */
        [[nodiscard]] bool contains(int key) const;

        /**
         * @brief �������� �������� ������ ����.
         */
        void display_status() const;

    private:
        std::list<int> cacheKeys; ///< ������ ������ � ����.
        std::unordered_map<int, std::list<int>::iterator> keyMap; ///< ³���������� ������ �� ��� ������� � ������.
        int capacity = 10; ///< ����������� ������� �������� � ����.
    };

} // namespace CacheLibrary

#endif // MRU_CACHE_HPP
