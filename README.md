python libraries:
pandas
scikit-learn
opencv
json
signal




C++ libraries:
opencv
Here is how to install opencv c++ for linux:
# Install minimal prerequisites (Ubuntu 18.04 as reference)
1->sudo apt update && sudo apt install -y cmake g++ wget unzip
 
# Download and unpack sources
2->wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
3->wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
4->unzip opencv.zip
5->unzip opencv_contrib.zip
 
# Create build directory and switch into it
6->mkdir -p build && cd build
 
# Configure
7->cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x
 
# Build
8->cmake --build .
# Install
9-> sudo make install




C++ Qt:
(we suggest to use qt official downloader https://www.qt.io/download-open-source otherwise you have to install banch of libraries.)
qmake6 (It is probably a better idea to have the IDE download all libraries then run it with makefile without IDE)
qt multimedia lib
qt6.7.1
Here is how to install qmake6 with multimedia lab, which is used in the Makefile:
1->sudo apt update
2->sudo apt install qt6-base-dev
3->sudo apt install libqt6multimedia6 libqt6multimedia6-plugins libqt6multimedia6-dev




In Order to establish connection with Mongodb:
boost
mongocxx
You can install these libraries with these commands in order:
1->sudo apt-get install libboost-all-dev
2->curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.10.1/mongo-cxx-driver-r3.10.1.tar.gz
3->tar -xzf mongo-cxx-driver-r3.10.1.tar.gz
3->cd mongo-cxx-driver-r3.10.1/build
4->cmake ..                                            \
    -DCMAKE_BUILD_TYPE=Release                      \
    -DBSONCXX_POLY_USE_BOOST=1                      \
    -DMONGOCXX_OVERRIDE_DEFAULT_INSTALL_PREFIX=OFF
5->cmake --build .
6->sudo cmake --build . --target install
These steps should build mongocxx driver in the default location, which code will have access to. 





Makefile, will compile detectShapes code, which uses opencv, then compiles onxx_pose (cpp code for exercises), and then compiles qt project, with qmake6 PAES.pro.
You can just use "$make run" to compile and run the project, should work if you have all required libraries.
