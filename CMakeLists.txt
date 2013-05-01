cmake_minimum_required (VERSION 2.6)
project (Zen)
 
# The version number.
set (Zen_VERSION_MAJOR 0)
set (Zen_VERSION_MINOR 1)

include(CTest)

include_directories(.)

find_package( Boost REQUIRED )
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} )

install (DIRECTORY zen DESTINATION include)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})


add_executable (ZenTest EXCLUDE_FROM_ALL test.cpp)
add_test (ZenTest ZenTest)
add_dependencies(check ZenTest)
set_target_properties(ZenTest PROPERTIES COMPILE_FLAGS -DZEN_TEST)
set_tests_properties(ZenTest PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")