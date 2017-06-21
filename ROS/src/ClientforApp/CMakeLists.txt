cmake_minimum_required(VERSION 2.8.3)
project(ClientforApp)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

include_directories(
 src/headers ${catkin_INCLUDE_DIRS}
	
)


add_library(client_l src/headers/client_l.cpp)


add_executable(clientapp src/ClientApp.cpp)
target_link_libraries(clientapp client_l ${catkin_LIBRARIES}) 
