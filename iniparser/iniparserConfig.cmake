# created by Ricardo Lu in 07-15-2021

# - Config file for the INIPARSER package
# It defines the following variables
#  INIPARSER_INCLUDE_DIRS - include directories for INIPARSER
#  INIPARSER_LIBRARIES    - libraries to link against

set(INIPARSER_INCLUDE_DIRS "/usr/local/iniparser/include")
set(INIPARSER_LIBRARIES "iniparser")

if( NOT TARGET iniparser AND NOT iniparser_BINARY_DIR )
	include(${CMAKE_CURRENT_LIST_DIR}/iniparserTargets.cmake)
endif()