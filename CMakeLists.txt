cmake_minimum_required(VERSION 3.20)

project(system)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(CoreLogic
        src/System.cpp
)
target_include_directories(CoreLogic PUBLIC include)

add_executable(system src/main.cpp)
target_link_libraries(system PRIVATE CoreLogic)

enable_testing()
include(GoogleTest)

add_executable(tests
        tests/testSystem.cpp
)
target_link_libraries(tests PRIVATE GTest::gtest_main CoreLogic)
gtest_discover_tests(tests)