# 设置最低cmake
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(Main C)

# 添加头文件的搜索路径
include_directories(include)

# 添加库文件
add_library(keyboard SHARED src/keyboard.c)  # SHARED：用于创建共享库（动态链接库）

# 设置库文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加可执行文件
add_executable(main main.c)

# 链接库到可执行文件
target_link_libraries(main PRIVATE keyboard)  # 私有
