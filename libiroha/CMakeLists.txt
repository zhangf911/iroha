cmake_minimum_required(VERSION 3.3)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

PROJECT(libiroha C CXX)


add_subdirectory(object)
