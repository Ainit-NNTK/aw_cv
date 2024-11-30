cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER "/mnt/sdd1/cv/toolchains/toolchain-sunxi-musl-gcc-830/toolchain/bin/arm-openwrt-linux-muslgnueabi-gcc")
set(CMAKE_CXX_COMPILER "/mnt/sdd1/cv/toolchains/toolchain-sunxi-musl-gcc-830/toolchain/bin/arm-openwrt-linux-muslgnueabi-g++")

set(CMAKE_C_FLAGS "-march=armv7-a -mfloat-abi=hard -mfpu=neon")
set(CMAKE_CXX_FLAGS "-march=armv7-a -mfloat-abi=hard -mfpu=neon")


project(aw_cam)

set(OpenCV_DIR "/mnt/sdd1/cv/opencv-mobile/install/aw/opencv-mobile-4.10.0-tinyvision/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)



# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 链接所需的库
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
