#include "AdaptiveCache.hpp"
#include <iostream>
#include <algorithm>
#include <utility>
#include "ConcreteCacheStrategy.hpp"
#include <cmath>
#include <openssl/sha.h>
#include <fstream>
int i = 1;
namespace cache_library {

    adaptive_cache::adaptive_cache(std::shared_ptr<ICacheStrategy> strategy)
        : cacheStrategy(std::move(strategy)) {}

    adaptive_cache::adaptive_cache(const std::shared_ptr<ICache>& lru_cache_ptr, const std::shared_ptr<ICache>&
                                   mru_cache_ptr) {
        // Створюємо стратегію за замовчуванням
        cacheStrategy = std::make_shared<concrete_cache_strategy>(lru_cache_ptr, mru_cache_ptr);
    }

    void adaptive_cache::insert(const int key, const int value) const
    {
        // Вибираємо відповідний кеш
        const auto cache = cacheStrategy->select_cache(key);

        // Вставляємо в обраний кеш
        cache->insert(key, value);

        // Оновлюємо стратегію з ключем
        cacheStrategy->update_strategy(key);
    }



    int adaptive_cache::get(const int key) const
    {
        int value = -1;

        const auto lru_cache = cacheStrategy->lruCache();
        const auto mru_cache = cacheStrategy->mruCache();

        if (lru_cache->contains(key)) {
            value = lru_cache->get(key);
            
        }
        else if (mru_cache->contains(key)) {
            value = mru_cache->get(key);
            
        }
        else {
            // Спробувати відновити з архіву, якщо реалізовано
        }

        if (value != -1) {
            // Оновлюємо стратегію з ключем
            cacheStrategy->update_strategy(key);
        }

        return value;
    }

    std::vector<int> adaptive_cache::filter(const std::function<bool(int)>& predicate) const {
        std::vector<int> result;

        const auto lru_cache = cacheStrategy->lruCache();
        const auto mru_cache = cacheStrategy->mruCache();

        // Фільтрація в LRU кеші
        for (const int key : lru_cache->get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        // Фільтрація в MRU кеші
        for (const int key : mru_cache->get_keys()) {
            if (predicate(key)) {
                result.push_back(key);
            }
        }

        return result;
    }

    std::vector<int> adaptive_cache::sort(std::function<bool(int, int)> comparator) const {
	    const auto lru_cache = cacheStrategy->lruCache();
	    const auto mru_cache = cacheStrategy->mruCache();

        std::vector<int> all_keys = lru_cache->get_keys();
        std::vector<int> mru_keys = mru_cache->get_keys();
        all_keys.insert(all_keys.end(), mru_keys.begin(), mru_keys.end());

        std::ranges::sort(all_keys, std::move(comparator));

        return all_keys;
    }
    double adaptive_cache::calculate_sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
        std::string hashStr(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);

        double checksum = 0;
        for (unsigned char ch : hash) {
            checksum += static_cast<double>(ch);
        }
        return checksum;
    }

    void adaptive_cache::write_to_archive_file(int key, double checksum) const
    {
        std::ofstream archiveFile(archiveFilePath_, std::ios::app);
        if (archiveFile.is_open()) {
            archiveFile << "Key: " << key << ", Checksum: " << checksum << "\n";
            archiveFile.close();
        }
        else {
            std::cerr << "Unable to open archive file!" << std::endl;
        }
    }
    void adaptive_cache::display_cache_status() const {
        std::cout << "Cache Status:\n";
        cacheStrategy->lruCache()->display_status();
        cacheStrategy->mruCache()->display_status();
    }

} // namespace cache_library
