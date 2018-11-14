cmake_minimum_required(VERSION 3.12)
project(SoftProcessor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(SoftProcessor main.cpp SimpleStack/stack_utils.cpp SimpleStack/stack_utils.h SimpleStack/stack_tests.cpp SimpleStack/stack_tests.h SimpleStack/data_types.h Common/err_codes.h Assembler/assembler.cpp Assembler/assembler.h Common/commands.h Processor/processor.cpp Processor/processor.h Common/registers.h Common/jumps.h Assembler/labels.cpp Assembler/labels.h)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -g3")