# Adaptive Hybrid Cache Library

An adaptive hybrid caching library in C++ that combines LRU (Least Recently Used) and MRU (Most Recently Used) caching algorithms with an archiving mechanism. The library dynamically switches between LRU and MRU based on access patterns and variance (dispersion) of data access, optimizing cache performance and memory usage.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Architecture](#architecture)
4. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installation](#installation)
5. [Usage](#usage)
   - [Initialization](#initialization)
   - [Inserting Data](#inserting-data)
   - [Accessing Data](#accessing-data)
   - [Filtering and Sorting](#filtering-and-sorting)
   - [Displaying Cache Status](#displaying-cache-status)
6. [API Reference](#api-reference)
   - [AdaptiveCache Class](#adaptivecache-class)
   - [ICache Interface](#icache-interface)
7. [Examples](#examples)
8. [Design Patterns](#design-patterns)
9. [Contributing](#contributing)
10. [License](#license)

---

## Introduction

The Adaptive Cache Library provides an efficient caching mechanism that adapts to different access patterns by switching between LRU and MRU caching algorithms. This adaptability ensures that the most appropriate caching strategy is used, improving system performance. The library also includes an archiving system that moves rarely accessed data to an archive, freeing up cache space and maintaining data integrity through checksums.

---

## Features
- **Adaptive Caching**: Dynamically switches between LRU and MRU algorithms based on data access patterns.
- **Archiving Mechanism**: Archives infrequently accessed data to optimize memory usage.
- **Checksum Verification**: Ensures data integrity using SHA-256 checksums.
- **Polymorphic Design**: Uses interfaces and dependency injection for flexibility and extensibility.
- **Filtering and Sorting**: Supports data filtering and sorting operations.
- **Easy Integration**: Simple API that can be integrated into existing C++ projects.

---

## Architecture

The library consists of several key components:
- **AdaptiveCache**: The main class that manages caching, archiving, and algorithm selection.
- **ICache Interface**: An abstract interface that defines the cache operations.
- **LRU_Cache and MRU_Cache**: Concrete implementations of the ICache interface using LRU and MRU algorithms.
- **ICacheStrategy Interface**: Defines the strategy for selecting the appropriate cache.
- **ConcreteCacheStrategy**: Implements the strategy for cache selection based on access patterns.
- **Archiving System**: Handles the archiving of data with checksum verification.

The adaptive mechanism analyzes data access patterns and calculates dispersion to decide whether to use LRU or MRU caching. The archiving system stores rarely accessed data, ensuring efficient cache utilization.

##How It Works
1. The library tracks the frequency of access for each key.
2. Calculates the variance (dispersion) of access frequencies for both LRU and MRU caches.
3. Based on the dispersion values, it dynamically selects the most suitable caching algorithm (LRU or MRU) for inserting data.
4. Data that is infrequently accessed or has been in the cache beyond a certain threshold is archived to free up space.
5. When archiving and restoring data, SHA-256 checksums are used to verify data integrity.
   
---

## Getting Started

### Prerequisites
- **C++17 or higher** (for features like `std::shared_ptr`)
- **OpenSSL library** (for SHA-256 checksum calculation)
- **C++ compiler** (e.g., GCC, Clang, MSVC)

### Installation

Clone the repository:

```bash
git clone https://github.com/Takatochi/Hybrid-Cache-Library_CB.git
```
Include the library in your project:
- Copy the CacheLibrary folder into your project directory and include the necessary header files.
  
Link against OpenSSL:
- Ensure your build system links against the OpenSSL library for checksum functionality.
  
---

## Usage

### Initialization

To use the Adaptive Hybrid Cache Library, create instances of the cache implementations and the adaptive cache.

````
#include "AdaptiveCache.hpp"
#include "LRU_Cache.hpp"
#include "MRU_Cache.hpp"

using namespace CacheLibrary;

int main() {
    // Create cache instances
    std::shared_ptr<ICache> lruCache = std::make_shared<LRU_Cache>(10);
    std::shared_ptr<ICache> mruCache = std::make_shared<MRU_Cache>(10);

    // TODO Add abstraction 
    //auto strategy = std::make_shared<ConcreteCacheStrategy>(lruCache, mruCache);
    //AdaptiveCache cache(strategy);

    AdaptiveCache cache(lruCache,mruCache);

    // Initialize the adaptive cache with the strategy
    AdaptiveCache cache(strategy);

    // Use the cache...
}
````
### Inserting Data
Insert data into the cache using the insert method:
````
cache.insert(key, value);
````
- key: An integer key for the data.
- value: The value associated with the key (can be any data type; adapt the code accordingly).

### Accessing Data
Retrieve data from the cache using the get method:
````
int value = cache.get(key);
if (value != -1) {
    // Data found
} else {
    // Data not found
}
````
### Filtering and Sorting
1. Filtering:
````
auto filtered_keys = cache.filter([](int key) {
    return key > 5; // Example condition
});
````
2. Sorting:
````
auto sorted_keys = cache.sort([](int a, int b) {
    return a < b; // Sort in ascending order
});
````
### Displaying Cache Status
Display the current status of the cache:
````
cache.display_cache_status();
````
---

## API Reference

### AdaptiveCache Class
The AdaptiveCache class manages data caching, archiving, and algorithm selection.

**Methods**
- TODO AdaptiveCache(std::shared_ptr<ICacheStrategy> strategy): Constructor that initializes the adaptive cache with a caching strategy.
- void insert(int key, int value): Inserts a key-value pair into the cache.
- int get(int key): Retrieves the value associated with a key.
- std::vector<int> filter(std::function<bool(int)> predicate): Filters keys based on a predicate.
- std::vector<int> sort(std::function<bool(int, int)> comparator): Sorts keys based on a comparator.
- void display_cache_status(): Displays the status of the caches.
  
### ICache Interface
The ICache interface defines the basic operations for cache implementations.

**Methods**
- void insert(int key, int value): Inserts a key-value pair into the cache.
- int get(int key): Retrieves the value associated with a key.
- bool contains(int key) const: Checks if a key exists in the cache.
- void remove(int key): Removes a key from the cache.
- void display_status() const: Displays the status of the cache.
- std::vector<int> get_keys() const: Retrieves all keys in the cache.

---

## Examples

### Basic Usage
````
#include "AdaptiveCache.hpp"
#include "LRU_Cache.hpp"
#include "MRU_Cache.hpp"

using namespace CacheLibrary;

int main() {
    // Initialize caches and strategy
    auto lruCache = std::make_shared<LRU_Cache>(5);
    auto mruCache = std::make_shared<MRU_Cache>(5);

    // TODO Add abstraction 
    //auto strategy = std::make_shared<ConcreteCacheStrategy>(lruCache, mruCache);
    //AdaptiveCache cache(strategy);

    AdaptiveCache cache(lruCache,mruCache);


    // Insert data
    cache.insert(1, 100);
    cache.insert(2, 200);
    cache.insert(3, 300);

    // Access data
    int value = cache.get(2);
    std::cout << "Value for key 2: " << value << '\n';

    // Filter data
    auto filtered_keys = cache.filter([](int key) { return key > 1; });
    std::cout << "Filtered keys: ";
    for (int key : filtered_keys) {
        std::cout << key << " ";
    }
    std::cout << '\n';

    // Sort data
    auto sorted_keys = cache.sort([](int a, int b) { return a < b; });
    std::cout << "Sorted keys: ";
    for (int key : sorted_keys) {
        std::cout << key << " ";
    }
    std::cout << '\n';

    // Display cache status
    cache.display_cache_status();

    return 0;
}
````

## Contributing
Contributions are welcome! Please follow these steps:
1. Fork the repository.
2. Create a new branch: git checkout -b feature/your-feature.
3. Commit your changes: git commit -m 'Add some feature'.
4. Push to the branch: git push origin feature/your-feature.
5. Open a pull request.
   
## License
This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
