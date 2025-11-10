cmake_minimum_required(VERSION 3.14)
project(Figures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(HEADER_ONLY ON)  

set(HEADERS
    include/point.h
    include/figure.h
    include/array.h
    include/triangle.h
    include/hexagon.h
    include/octagon.h
)

add_executable(main
    main.cpp
    ${HEADERS}
)

add_executable(tests
    test/tests.cpp
    ${HEADERS}
)

target_include_directories(main PRIVATE include)
target_include_directories(tests PRIVATE include)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)