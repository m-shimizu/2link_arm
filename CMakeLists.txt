cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(2link_arm_plugin SHARED 2link_arm_plugin.cc)
target_link_libraries(2link_arm_plugin ${GAZEBO_LIBRARIES})

add_library(pack_push SHARED pack_push.cc)
target_link_libraries(pack_push ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})

