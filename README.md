# cpp-bitmaps

Measure three types of bitmaps in C++: `std::bitset`, `std::vector<bool>`, and `boost::dynamic_bitset`.
- `std::bitset` is a fixed-size array of bits, the size of which is determined at compile time.
- `std::vector<bool>` is a dynamic array of bits, the size of which is determined at runtime. It is a specialization of `std::vector` that is optimized for space efficiency (see https://eel.is/c++draft/vector.bool). It will create a proxy object for `operator[]` which causes performance overhead.
- `boost::dynamic_bitset` is a dynamic array of bits, the size of which is determined at runtime. It is a part of the Boost library. It also has a proxy object for `operator[]`.

## Build

Dependends on `boost` library.

```bash
bash build.sh
```

## Run

```bash
./bitset_comparison 
```

## Results

On Perlmutter, AMD EPYC 7713 64-Core Processor:
```
std::vector<bool> set time: 23273 µs
std::vector<bool> read time: 0 µs
std::bitset set time: 0 µs
std::bitset read time: 0 µs
boost::dynamic_bitset set time: 23784 µs
boost::dynamic_bitset read time: 0 µs
```



