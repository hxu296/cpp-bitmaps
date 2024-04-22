#include <iostream>
#include <chrono>
#include <vector>
#include <bitset>
#include <boost/dynamic_bitset.hpp>

const size_t SIZE = 10000000;  // Size of the bitsets
const size_t READ_ITERATIONS = 10000;  // Number of read iterations

// Function to measure the execution time of a callable
template <typename Func>
void measureTime(const std::string& name, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << " time: " << duration.count() << " µs\n";
}

int main() {
    // Test std::vector<bool>
    std::vector<bool> vec(SIZE);
    measureTime("std::vector<bool> set", [&]() {
        for (size_t i = 0; i < SIZE; ++i) {
            vec[i] = (i % 2 == 0);
        }
    });
    measureTime("std::vector<bool> read", [&]() {
        size_t sum = 0;
        for (size_t j = 0; j < READ_ITERATIONS; ++j) {
            for (size_t i = 0; i < SIZE; ++i) {
                if (vec[i]) {
                    ++sum;
                }
            }
        }
    });

    // Test std::bitset
    std::bitset<SIZE> bitset;
    measureTime("std::bitset set", [&]() {
        for (size_t i = 0; i < SIZE; ++i) {
            bitset[i] = (i % 2 == 0);
        }
    });
    measureTime("std::bitset read", [&]() {
        size_t sum = 0;
        for (size_t j = 0; j < READ_ITERATIONS; ++j) {
            for (size_t i = 0; i < SIZE; ++i) {
                if (bitset[i]) {
                    ++sum;
                }
            }
        }
    });

    // Test boost::dynamic_bitset
    boost::dynamic_bitset<> dynBitset(SIZE);
    measureTime("boost::dynamic_bitset set", [&]() {
        for (size_t i = 0; i < SIZE; ++i) {
            dynBitset[i] = (i % 2 == 0);
        }
    });
    measureTime("boost::dynamic_bitset read", [&]() {
        size_t sum = 0;
        for (size_t j = 0; j < READ_ITERATIONS; ++j) {
            for (size_t i = 0; i < SIZE; ++i) {
                if (dynBitset[i]) {
                    ++sum;
                }
            }
        }
    });

    return 0;
}