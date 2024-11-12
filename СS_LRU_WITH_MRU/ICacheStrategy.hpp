#ifndef ICACHESTRATEGY_HPP
#define ICACHESTRATEGY_HPP

#include <string>
//TODO 
/**
 * @class ICacheStrategy
 * @brief Абстрактний інтерфейс для кеш-стратегій.
 * @en Abstract interface for cache strategies.
 */
class ICacheStrategy {
public:
    virtual ~ICacheStrategy() = default;

    /**
     * @brief Вибір ключа для видалення відповідно до стратегії.
     * @en Select a key for eviction based on the strategy.
     * @return Ключ для видалення або -1, якщо немає ключів для видалення.
     * @en Key to evict or -1 if no keys are available for eviction.
     */
    virtual int select_key_for_eviction() const = 0;

    /**
     * @brief Оновлює стратегію при доступі до ключа.
     * @en Update the strategy when a key is accessed.
     * @param key Ключ, який був доступний.
     * @en Key that was accessed.
     */
    virtual void on_access(int key) = 0;

    /**
     * @brief Оновлює стратегію при вставці нового ключа.
     * @en Update the strategy when a new key is inserted.
     * @param key Ключ для вставки.
     * @en Key to insert.
     */
    virtual void on_insert(int key) = 0;

    /**
     * @brief Видаляє ключ зі стратегії кешування.
     * @en Remove a key from the caching strategy.
     * @param key Ключ для видалення.
     * @en Key to remove.
     */
    virtual void on_remove(int key) = 0;
};


#endif // ICACHESTRATEGY_HPP
