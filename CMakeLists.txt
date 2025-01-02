cmake_minimum_required(VERSION 3.13)
project(TerminalPaint)


set(CMAKE_CXX_STANDARD 17)


if(WIN32)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(TerminalPaint ${SOURCES})

include_directories("include")

else()
	message(FATAL_ERROR "Terminal Paint only works on Windows")
endif()