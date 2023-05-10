# Binary Tree
## _Sample C++ code inspired by [LeetCode](https://leetcode.com/)_

[![BinaryTree_Sample](res/img/binary_tree_example_path.svg)](../../../TextAnimator)

BinaryTree is a library inspired by [Maximum Width of Binary Tree](https://leetcode.com/problems/maximum-width-of-binary-tree/) and
[Print Binary Tree](https://leetcode.com/problems/print-binary-tree) questions.

## Features

- Creates schematic of a binary tree
- Evaluates the maximum width of a binary tree
- Converts a vector to a binary tree
- CMake is used to build the library
- [Batch script](buildWindows.bat) can be executed to create the make file and build the program in Windows
- [Bash script](buildLinux.sh) can be executed to create the make file and build the program in Linux
- more to come ...

## Prerequisites

- g++ or any C++ compiler
- cmake
- make


## Build

### Windows

Execute the following command
```bat
.\buildWindows.bat
```
The following additional options can be provided
```
-source [SOURCE]      : source directory
-build [BUILD]        : build directory excluding operating system
-generator [GENERATOR]: generator for cmake
-compiler [COMPILER]  : compiler for cmake
-make [MAKE]          : make executable
-vcvarsall            : path to vcvarsall.bat to set the environment variables for visual studio
*                     : any cmake arguments
-- *                  : any make arguments
```

### Linux

Execute the following command
```sh
./buildLinux.sh
```
The following additional options can be provided
```
-source [SOURCE]      : source directory
-build [BUILD]        : build directory excluding operating system
-generator [GENERATOR]: generator for cmake
-compiler [COMPILER]  : compiler for cmake
-make [MAKE]          : make executable
*                     : any cmake arguments
-- *                  : any make arguments
```
