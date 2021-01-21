cmake_minimum_required(VERSION 3.17)

project(
    prcxx
    VERSION 0.1
    DESCRIPTION "Yet another C++ property library"
    LANGUAGES CXX
)
  
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CXX_STANDARD 20)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    
    include(CTest)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(source)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
