cmake_minimum_required(VERSION 3.10)

project(boost_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(Boost 
			 REQUIRED
			 COMPONENTS
			 filesystem)

set(SUBDIRS vendor/Catch2 spirit fusion)

foreach(DIR ${SUBDIRS})
	add_subdirectory(${DIR})
endforeach()

