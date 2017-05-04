cmake_minimum_required(VERSION 2.8.3)
project(t)


find_package(catkin REQUIRED COMPONENTS
roscpp
)
catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(server src/server2.cpp)
target_link_libraries(server ${catkin_LIBRARIES}) 
add_dependencies(server t_generate_messages_cpp) 
