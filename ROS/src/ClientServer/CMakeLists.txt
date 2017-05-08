cmake_minimum_required(VERSION 2.8.3)
project(ClientServer)


find_package(catkin REQUIRED COMPONENTS
roscpp
std_msgs 
)
catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(server src/server_node.cpp)
target_link_libraries(server ${catkin_LIBRARIES}) 
add_dependencies(server ClientServer_generate_messages_cpp) 

add_executable(client src/client_node.cpp)
target_link_libraries(client ${catkin_LIBRARIES}) 
add_dependencies(client ClientServer_generate_messages_cpp) 
