#include "AdaptiveCache.hpp"



int main() {
    CacheLibrary::AdaptiveCache cache;

    // Створюємо постійний доступ для певних ключів, щоб побачити роботу LRU і MRU
    for (int i = 0; i < 100; ++i) {
        cache.access(2);
        cache.access(10);
    }

    // Додаємо доступ до нових ключів для перевірки роботи адаптивного кешування
    cache.access(100);
    cache.access(278);

    // Перевіряємо статус кешу після доступів
    cache.display_cache_status();

    return 0;
}
