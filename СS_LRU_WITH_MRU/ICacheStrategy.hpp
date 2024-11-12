#ifndef ICACHESTRATEGY_HPP
#define ICACHESTRATEGY_HPP

#include <string>

/**
 * @class ICacheStrategy
 * @brief Абстрактний інтерфейс для кеш-стратегій.
 */
class ICacheStrategy {
public:
    virtual ~ICacheStrategy() = default;

    /**
     * @brief Вставка ключа у кеш.
     * @param key Ключ для вставки.
     * @param value Значення, яке буде збережено (не використовується в цьому прикладі).
     */
    virtual void insert(int key, int value) = 0;

    /**
     * @brief Отримання значення за ключем.
     * @param key Ключ, який потрібно отримати.
     * @return Значення ключа або -1, якщо ключа немає в кеші.
     */
    virtual int get(int key) = 0;

    /**
     * @brief Перевірка, чи є ключ у кеші.
     * @param key Ключ для перевірки.
     * @return true, якщо ключ є в кеші, інакше false.
     */
    virtual bool contains(int key) const = 0;

    /**
     * @brief Виведення поточного статусу кешу.
     */
    virtual void displayStatus() const = 0;

    /**
     * @brief Отримання назви стратегії кешування.
     * @return Назва стратегії.
     */
    virtual std::string getStrategyName() const = 0;
};

#endif // ICACHESTRATEGY_HPP
