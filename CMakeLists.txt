cmake_minimum_required (VERSION 2.6)
project (buffer)

include_directories("include")

ADD_LIBRARY(buffer STATIC
    src/buffer.c
    )