cmake_minimum_required(VERSION 2.6)
project(eratosthenes)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(eratosthenes main.cpp eratlib.cpp eratlib.h)

set(BOOST_LIBS program_options)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)

target_link_libraries(eratosthenes ${Boost_LIBRARIES})

install(TARGETS eratosthenes RUNTIME DESTINATION bin)
