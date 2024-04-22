#include <iostream>
#include <chrono>
#include <vector>
#include <bitset>
#include <random>
#include <boost/dynamic_bitset.hpp>

const size_t SIZE = 10000000;  // Size of the bitsets
const size_t READ_ITERATIONS = SIZE * 10;  // Number of read iterations

// Function to measure the execution time of a callable
template <typename Func>
void measureTime(const std::string& name, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << name << " time: " << duration.count() << " ms\n";
}

// Function to generate pseudo-random bits using XOR
inline bool generateRandomBit(size_t i) {
    return (i ^ (i >> 1)) & 1;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> index_dist(0, SIZE - 1);

    // Generate random indices
    std::vector<size_t> indices;
    indices.reserve(READ_ITERATIONS);
    for (size_t j = 0; j < READ_ITERATIONS; ++j) {
        indices.push_back(index_dist(gen));
    }

    // Test std::vector<bool>
    std::vector<bool> vec(SIZE);
    measureTime("std::vector<bool> set", [&]() {
        for (size_t i = 0; i < SIZE; ++i) {
            vec[i] = generateRandomBit(i);
        }
    });
    measureTime("std::vector<bool> read", [&]() {
        volatile size_t sum = 0;
        for (size_t index : indices) {
            if (vec[index]) {
                ++sum;
            }
        }
    });

    // Test std::bitset
    std::bitset<SIZE> bitset;
    measureTime("std::bitset set", [&]() {
        for (size_t i = 0; i < SIZE; ++i) {
            bitset[i] = generateRandomBit(i);
        }
    });
    measureTime("std::bitset read", [&]() {
        volatile size_t sum = 0;
        for (size_t index : indices) {
            if (bitset[index]) {
                ++sum;
            }
        }
    });

    // Test boost::dynamic_bitset
    boost::dynamic_bitset<> dynBitset(SIZE);
    measureTime("boost::dynamic_bitset set", [&]() {
        for (size_t i = 0; i < SIZE; ++i) {
            dynBitset[i] = generateRandomBit(i);
        }
    });
    measureTime("boost::dynamic_bitset read", [&]() {
        volatile size_t sum = 0;
        for (size_t index : indices) {
            if (dynBitset[index]) {
                ++sum;
            }
        }
    });

    return 0;
}