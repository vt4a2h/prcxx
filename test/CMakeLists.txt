find_package(Catch2 CONFIG REQUIRED)

add_executable(tests test.cpp)

target_compile_features(tests PRIVATE cxx_std_20)

target_link_libraries(tests PRIVATE prcxx Catch2::Catch2)

include(Catch)
catch_discover_tests(tests)
