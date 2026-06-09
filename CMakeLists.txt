cmake_minimum_required(VERSION 3.20)

project(system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
        src/SystemUI.cpp
        src/LanguageManager.cpp
)
target_include_directories(CoreLogic PUBLIC include)

add_executable(system src/main.cpp)
target_link_libraries(system PRIVATE CoreLogic)

add_custom_command(TARGET system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:system>/data
)

enable_testing()
include(GoogleTest)

add_executable(tests
        tests/tests_utils.cpp
)

target_link_libraries(tests PRIVATE GTest::gtest_main CoreLogic)
target_link_libraries(CoreLogic PRIVATE GTest::gtest)
gtest_discover_tests(tests)