# Hybrid LRU-MRU Cache Library

A C++ library implementing a hybrid caching system that dynamically switches between LRU (Least Recently Used) and MRU (Most Recently Used) caching strategies based on access pattern dispersion. This hybrid approach improves cache efficiency by adaptively choosing the best algorithm according to the data access patterns.

## Features

- **Hybrid Cache**: Combines LRU and MRU caching strategies with dynamic switching based on access frequency dispersion to balance between frequently and recently accessed data.
- **LRU Cache**: Evicts the least recently accessed items when the cache is full, focusing on retaining frequently accessed items.
- **MRU Cache**: Evicts the most recently accessed items when the cache is full, prioritizing older data when access patterns indicate it may be reused.
- **Adaptive Switching**: Uses access frequency dispersion to determine the optimal caching algorithm for current patterns, switching dynamically between LRU and MRU based on stability and frequency metrics.
- **Access Dispersion Analysis**: Calculates variance in access frequency to decide when to switch algorithms, favoring MRU for stable, frequent access, and LRU for sporadic access.
- **Archiving**: Archives infrequently accessed data to minimize cache load and optimize memory usage.
- **Checksum Verification**: Uses SHA-256 checksums (via OpenSSL) to verify archived data integrity, protecting against data corruption.

## Requirements

- C++17 or higher
- OpenSSL library (for SHA-256 checksum calculations)
- Visual Studio (for Windows users) or other compatible IDEs

## Installation (Windows)

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/hybrid-cache-library.git
   cd hybrid-cache-library
2. **Open Visual Studio**:
  - Open Visual Studio and select "Open a Local Folder".
  - Navigate to the cloned repository folder and open it.
3. **Open Visual Studio**:
  - Add Existing Items:
     - Go to Project > Add Existing Item.
     - Select and add all .cpp and .hpp files to the project
  - Set C++17 Standard:
     - Right-click on the project in the Solution Explorer.
     - Select "Properties".
     - Navigate to C/C++ > Language.
     - Set C++ Language Standard to C++17.
4. **Build the Library**:
   - Go to Build > Build Solution to compile the library.

## Usage

Include the library in your project and use the "AdaptiveCache" class to manage cached data.

#include "AdaptiveCache.hpp"
using namespace CacheLibrary;
```cpp

#include "AdaptiveCache.hpp"

int main() {
    CacheLibrary::AdaptiveCache cache;
    for (int i = 0; i < 100; ++i) {
        cache.access(2);
        cache.access(10);
    }
    cache.access(100);
    cache.access(278);

    cache.displayCacheStatus();

    return 0;
}
```
## Example of Access Patterns
The library can dynamically handle frequent and sporadic access patterns:
1. **Frequent Access Example**:
    - Access a few keys repeatedly (e.g., cache.access(2); cache.access(10);) to favor LRU.
2. **Sporadic Access Example**:
   - Access different keys (e.g., cache.access(100); cache.access(278);) to induce switching based on dispersion analysis.

## Documentation
Documentation is provided using Doxygen. To generate it, run:
 ```bash
    doxygen Doxyfile
