#!/bin/sh

# 判断 CMakeLists.txt 文件是否存在，存在则删除
if [ -f "CMakeLists.txt" ];then
    rm -f CMakeLists.txt
fi

# 判断 build 目录是否存在，存在则删除
if [ -d "build" ];then
    rm -rf build
fi

# 判断运行脚本参数是否合法
if [ $# -ne 1 ]; then
    echo "\nRun build.sh like this:\n   \033[32m sh build.sh day_time_tcp_cli \033[0m"
    exit
fi

# 判断对应的xxx.txt文件是否存在
cmake_file_name=$1".txt"
if [ ! -f $cmake_file_name ];then
    echo "\033[31m$cmake_file_name file not exist\033[0m"
    exit
fi

# 文件复制为CMakeLists.txt，CMake才能识别开始编译
cp $cmake_file_name CMakeLists.txt

# 新建build目录用于存放编译生成的各类文件
mkdir build 
cd build
cmake .. 
make

cd ..
rm -rf build
rm -f CMakeLists.txt

# 判断可执行文件是否存在
# -x 判断对象是否存在，并且可执行
if [ -x $1 ];then
    echo "\nBuild success. Run:"
    echo "\033[32m  ./$1\033[0m"
fi
