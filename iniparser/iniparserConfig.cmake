# created by Ricardo Lu in 07-15-2021

# - Config file for the INIPARSER package
# It defines the following variables
#  INIPARSER_INCLUDE_DIRS - include directories for INIPARSER
#  INIPARSER_LIBRARIES    - libraries to link against


set(INIPARSER_INCLUDE_DIRS "/home/ts/workSpace/packageConfig/iniparser/inc")
set(INIPARSER_LIBRARIES "iniparser")

include(${CMAKE_CURRENT_LIST_DIR}/iniparserTargets.cmake)
