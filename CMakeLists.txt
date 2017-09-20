

# Project construction ...

# source files ...

cmake_minimum_required(VERSION 3.7)
project(main)
find_path(CPPREST_INCLUDE cpprest/json.h)
message(${CPPREST_INCLUDE})
find_library(CPPREST_LIB NAMES cpprest_2_9d cpprest_2_9 cpprestd cpprest)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_package(OpenSSL 1.0.0 REQUIRED)

add_executable(main ./source/main.cpp
./source/microsvc_controller.cpp
./source/network_utils.cpp
./source/basic_controller.cpp)



set(MICROSERVICE source)

include_directories(${CPPREST_INCLUDE})
include_directories(${MICROSERVICE})
target_link_libraries(main
  ${CPPREST_LIB}
  Boost::boost
  Boost::random
  Boost::system
  Boost::thread
  Boost::filesystem
  Boost::chrono
  Boost::atomic
  Boost::date_time
  Boost::regex
  OpenSSL::SSL
)