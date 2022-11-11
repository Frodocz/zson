cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(zson)

SET(ZSON_HEADER_PATH ${PROJECT_SOURCE_DIR}/include)
SET(ZSON_SRC_PATH ${PROJECT_SOURCE_DIR}/src)
SET(ZSON_TEST_PATH ${PROJECT_SOURCE_DIR}/test)

set(LIB_HEADER
    ${ZSON_HEADER_PATH}/parser.h
    ${ZSON_HEADER_PATH}/scanner.h
    ${ZSON_HEADER_PATH}/json_element.h
    )

set(LIB_SRC
    ${ZSON_SRC_PATH}/parser.cpp
    ${ZSON_SRC_PATH}/scanner.cpp
    )

add_library(zson SHARED ${LIB_HEADER} ${LIB_SRC})

set(TEST_SRC
    ${ZSON_TEST_PATH}/test.cpp
    )

add_executable(zsontest ${TEST_SRC})
target_link_libraries(zsontest zson)