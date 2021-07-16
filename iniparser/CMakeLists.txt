# created by Ricardo Lu in 07-15-2021

cmake_minimum_required(VERSION 3.10)

PROJECT(iniparser)
set(INIPARSER_MAJOR_VERSION 0)
set(INIPARSER_MINOR_VERSION 1)
set(INIPARSER_PATCH_VERSION 0)
set(INIPARSER_VERSION 
    ${INIPARSER_MAJOR_VERSION}.${INIPARSER_MINOR_VERSION}.${INIPARSER_PATCH_VERSION})

set(INIPARSER_HEADER_DIR ${PROJECT_SOURCE_DIR}/inc)
set(INIPARSER_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_INSTALL_PREFIX /usr/local/iniparser)

add_library(${PROJECT_NAME}
    SHARED
    ${INIPARSER_SOURCE_DIR}/dictionary.c
    ${INIPARSER_SOURCE_DIR}/iniparser.c
    ${INIPARSER_SOURCE_DIR}/ini_conf.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inc
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES PUBLIC_HEADER "${INIPARSER_HEADER_DIR}/ini_conf.h"
)

install(TARGETS ${PROJECT_NAME}
    EXPORT iniparserpackage
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

configure_file(iniparserConfig.cmake.in
  "${PROJECT_SOURCE_DIR}/iniparserConfig.cmake" @ONLY)

configure_file(iniparserConfigVersion.cmake.in
  "${PROJECT_SOURCE_DIR}/iniparserConfigVersion.cmake" @ONLY)

install(FILES 
    "${PROJECT_SOURCE_DIR}/iniparserConfig.cmake"
    "${PROJECT_SOURCE_DIR}/iniparserConfigVersion.cmake"
    DESTINATION lib/cmake
)

install(EXPORT iniparserpackage
        FILE iniparserTargets.cmake
        DESTINATION lib/cmake/
)