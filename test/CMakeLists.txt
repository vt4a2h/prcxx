find_package(Catch2 CONFIG REQUIRED)

set(HEADER_LIST
    "${prcxx_SOURCE_DIR}/test/StringMaker.hpp"
)

add_executable(tests
    main.cpp
    PropertyConstructionTest.cpp
    PropertyComparisonTest.cpp
    PropertyResolvingTest.cpp
    CycleDetectionTest.cpp
    ExpectedConstructionTest.cpp
    ExpectedComparisonTest.cpp
        ValueObservableTest.cpp
        InvokableObservableTest.cpp
    ErrorWithSourceLocationTest.cpp
    PropertyCastTest.cpp
    PropertyGetterTest.cpp
    PropertySetterTest.cpp
    ${HEADER_LIST}
)

target_compile_features(tests PRIVATE cxx_std_20)

target_link_libraries(tests PRIVATE prcxx Catch2::Catch2)

include(Catch)
catch_discover_tests(tests)
