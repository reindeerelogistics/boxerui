#!/bin/bash
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip

# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
unzip opencv.zip

# Download opencv_contrib extra modules
git clone https://github.com/opencv/opencv_contrib.git

# Create build directory
mkdir -p opencv-build && cd opencv-build

# Add opencv_contrib extra modules
cmake ../opencv-master/ -DOPENCV_EXTRA_MODULES_PATH=/home/username/opencv_contrib/modules ../opencv-master/

# Configure
# cmake ../opencv-master/ -DBUILD_TESTS=OFF -DBUILD_opencv_python2=OFF -DBUILD_opencv_python3=OFF -DWITH_OPENEXR=OFF -DWITH_1394=OFF -DWITH_EIGEN=OFF -DWITH_OPENGL=ON -DBUILD_SHARED_LIBS=OFF -DWITH_FFMPEG=OFF .
# cmake ../opencv-master/ -DBUILD_LIST=calib3d,core,features2d,flann,highgui,imgcodecs,imgproc,videoio .
# Simple build w/out CUDA
	# cmake ../opencv-master/ -DBUILD_LIST=calib3d,core,highgui,imgcodecs,imgproc,videoio,video -DBUILD_TESTS=OFF -DBUILD_opencv_python2=OFF -DBUILD_opencv_python3=OFF -DWITH_OPENEXR=OFF -DWITH_1394=OFF -DWITH_EIGEN=OFF -DWITH_OPENGL=ON -DBUILD_SHARED_LIBS=OFF -DWITH_FFMPEG=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DBUILD_opencv_python_tests=OFF -DBUILD_JAVA=OFF .
cmake ../opencv-master/ -DBUILD_LIST=calib3d,core,features2d,flann,highgui,imgcodecs,imgproc,videoio -DBUILD_TESTS=OFF -DBUILD_opencv_python2=OFF -DBUILD_opencv_python3=OFF -DWITH_OPENEXR=OFF -DWITH_1394=OFF -DWITH_EIGEN=OFF -DWITH_OPENGL=ON -DBUILD_SHARED_LIBS=OFF -DWITH_FFMPEG=OFF -DWITH_CUDA=ON .

# print all options
cmake -L
# print all options with help message
cmake -LH
# print all options including advanced
cmake -LA

# Build
make -j4

cmake --install . --prefix "../opencv-build/install"

# sudo apt-get install libglfw3-dev
git clone https://github.com/glfw/glfw.git

mkdir build
# mkdir ../../build
# Configure the project. Create the CMakeCache files required for building the project
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc-9 -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++-9 -H. -B../../build

# Build the application
cmake --build BoxerUI/boxer_build --config Debug --target BoxerUI_app -j 4

chmod +x BoxerUI_app

./BoxerUI_app