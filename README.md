![Release with tests](https://github.com/vt4a2h/prcxx/workflows/Release%20with%20tests/badge.svg)

# prcxx
Yet another C++ property library.

This is mostly "just for fun" project. But you can write lazily-evaluated properties that support some sort of dependency tracking. For example:
```cpp
property<std::string> p0("p0");
property<std::string> p1("p1");

int counter = 0;
property<std::string> p(wrap_invokable([&] {
    ++counter;

    auto p0_val = *p0;
    if (p0_val == "p0")
        return p0_val;

    return *p1;
}));

assert(counter == 0);

assert(*p == "p0");
assert(counter == 1);

p1.set("~p1");

assert(*p == "p0");
assert(counter == 1);

p0.set("~p0");

assert(*p == "~p1");
assert(counter == 2);

p0.set("p0");

assert(*p == "p0");
assert(counter == 3);
```

You can find more examples [here](https://github.com/vt4a2h/prcxx/tree/master/test).

# Build instructions
```sh
# Install package manager
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
./vcpkg/install catch2 fmt range-v3

# Build library
git clone git@github.com:vt4a2h/prcxx.git
cmake -B prcxx/build -S prcxx -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake -G "Ninja"
cmake --build prcxx/build

# Run tests (optional)
cd prxcc/build
ctest
```
