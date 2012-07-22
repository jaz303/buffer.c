cmake_minimum_required (VERSION 2.6)
project (buffer)

# Detect subproject status
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(IS_SUBPROJECT NO)
else()
    set(IS_SUBPROJECT YES)
endif()

include_directories("include")

if (IS_SUBPROJECT)
    set(BUFFER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)
endif()

ADD_LIBRARY(buffer STATIC
    src/buffer.c
    )
