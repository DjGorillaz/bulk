cmake_minimum_required(VERSION 3.8)

project (bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(app main.cpp)

add_executable(test_bulk test.cpp)

add_library(bulk bulk.cpp)

add_library(exporter exporter.cpp)

set_target_properties(app bulk exporter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(test_bulk PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_bulk bulk ${Boost_LIBRARIES})

target_link_libraries(bulk exporter)

target_link_libraries(app bulk)

install(TARGETS app RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT djg2008@gmail.com)

include(CPack)

enable_testing()

add_test(Test test_bulk)