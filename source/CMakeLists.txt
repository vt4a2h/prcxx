find_package(fmt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)

set(HEADER_LIST
    "${prcxx_SOURCE_DIR}/include/prcxx/EvaluationChain.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/ActiveEvaluationChain.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/BaseObservable.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/Error.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/SourceLocation.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/DecoratableBase.hpp"
)

add_library(prcxx
    EvaluationChain.cpp
    ActiveEvaluationChain.cpp
    BaseObservable.cpp
    Error.cpp
    ${HEADER_LIST}
)

target_include_directories(prcxx PUBLIC ../include)

target_link_libraries(prcxx PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(prcxx PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)

target_compile_features(prcxx PUBLIC cxx_std_20)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)