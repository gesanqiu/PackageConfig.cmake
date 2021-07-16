# created by Ricardo Lu in 07-15-2021

cmake_minimum_required(VERSION 3.10)

PROJECT(ini-test)

set(iniparser_DIR "/usr/local/iniparser/lib/cmake")
find_package(iniparser 0.1.0)
message(STATUS "INIPARSER_INCLUDE_DIRS: ${INIPARSER_INCLUDE_DIRS}")
message(STATUS "INIPARSER_LIBRARIES:    ${INIPARSER_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${INIPARSER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${INIPARSER_LIBRARIES})