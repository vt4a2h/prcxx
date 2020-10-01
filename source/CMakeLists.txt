set(HEADER_LIST
    "${prcxx_SOURCE_DIR}/include/prcxx/EvaluationChain.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/ActiveEvaluationChain.hpp"
    "${prcxx_SOURCE_DIR}/include/prcxx/BaseObserver.hpp"
)

add_library(prcxx
    EvaluationChain.cpp
    ActiveEvaluationChain.cpp
    BaseObserver.cpp
    ${HEADER_LIST}
)

target_include_directories(prcxx PUBLIC ../include)

target_compile_features(prcxx PUBLIC cxx_std_20)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)