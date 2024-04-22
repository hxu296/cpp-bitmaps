# cpp-bitmaps

This program measure three types of bitmaps in C++: `std::bitset`, `std::vector<bool>`, and `boost::dynamic_bitset`.
- `std::bitset` is a fixed-size array of bits, the size of which is determined at compile time.
- `std::vector<bool>` is a dynamic array of bits, the size of which is determined at runtime. It is a specialization of `std::vector` that is optimized for space efficiency (see https://eel.is/c++draft/vector.bool). It will create a proxy object for `operator[]` which causes performance overhead.
- `boost::dynamic_bitset` is a dynamic array of bits, the size of which is determined at runtime. It is a part of the Boost library. It also has a proxy object for `operator[]`.

The program measures the time to set 10000000 and read 10 * 10000000 bits in each of the bitmaps. The setting of bits is done serially with pesudo-random values calculated by `(i ^ (i >> 1)) & 1` where `i` is the index of the bit. The reading of bits is done in a random order.

## Conclusion
The conclusion is that `boost::dynamic_bitset` is the fastest for both setting and reading bits. `std::bitset` is almost as fast as `boost::dynamic_bitset` for both setting and reading bits. `std::vector<bool>` is the slowest for both setting and reading bits. Refer to run statistics below for more details.

## Build

Dependends on `boost` library.

```bash
bash build.sh
```

## Run

```bash
./bitset_comparison 
```

## Run Satistics

On Perlmutter, AMD EPYC 7713 64-Core Processor:
```
std::vector<bool> set time: 19 ms
std::vector<bool> read time: 819 ms
std::bitset set time: 16 ms
std::bitset read time: 626 ms
boost::dynamic_bitset set time: 14 ms
boost::dynamic_bitset read time: 625 ms
```



