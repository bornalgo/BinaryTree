cmake_minimum_required(VERSION 3.16.3)

project(BinaryTree)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src/binary_tree)

target_include_directories(${PROJECT_NAME} PUBLIC src/binary_tree)

target_link_directories(${PROJECT_NAME} PRIVATE src/binary_tree)

target_link_libraries(${PROJECT_NAME} BinaryTreeLIB)