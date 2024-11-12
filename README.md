# Adaptive Cache Library

An adaptive caching library in C++ that dynamically switches between LRU (Least Recently Used) and MRU (Most Recently Used) caching algorithms based on access patterns. It includes an archiving mechanism to store infrequently accessed data, ensuring efficient memory usage and optimal performance.

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

---

## Getting Started

### Prerequisites
- **C++17 or higher** (for features like `std::shared_ptr`)
- **OpenSSL library** (for SHA-256 checksum calculation)
- **C++ compiler** (e.g., GCC, Clang, MSVC)

### Installation

Clone the repository:

```bash
git clone https://github.com/yourusername/adaptive-cache-library.git
```
nclude the library in your project:

- Copy the CacheLibrary folder into your project directory and include the necessary header files.
Link against OpenSSL:
- Ensure your build system links against the OpenSSL library for checksum functionality.
- 
