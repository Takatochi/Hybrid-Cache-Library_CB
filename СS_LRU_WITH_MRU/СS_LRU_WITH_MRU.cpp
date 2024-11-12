﻿#include "AdaptiveCache.hpp"

int main() {
    cache_library::AdaptiveCache cache;



    for (int i = 0; i < 100; ++i) {
        cache.access(2);
        cache.access(10);
    }
    cache.access(100);
    cache.access(278);

    // Вставка даних
    cache.insert(1, 100);
    cache.insert(2, 200);
    cache.insert(3, 300);
    // Доступ до даних
    int value = cache.get(2);
    std::cout << "Value for key 2: " << value << '\n';

    // Фільтрація даних (наприклад, вибрати ключі більше 1)
    auto filtered_keys = cache.filter([](int key) { return key > 1; });
    std::cout << "Filtered keys: ";
    for (int key : filtered_keys) {
        std::cout << key << " ";
    }
    std::cout << '\n';

    // Сортування даних (за зростанням ключів)
    auto sorted_keys = cache.sort([](int a, int b) { return a < b; });
    std::cout << "Sorted keys: ";
    for (int key : sorted_keys) {
        std::cout << key << " ";
    }
    std::cout << '\n';

    // Відображення статусу кешу
    cache.display_cache_status();

    return 0;
}
