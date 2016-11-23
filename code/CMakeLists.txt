cmake_minimum_required(VERSION 3.0)

# Add strict warning checking for C++
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_subdirectory(rapidcheck)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(quickcheck
	quickcheck.cc
)
set_property(TARGET quickcheck PROPERTY CXX_STANDARD 14)
target_link_libraries(quickcheck rapidcheck)
