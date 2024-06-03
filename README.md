python libraries:
pandas
scikit-learn
opencv
json
signal


C++ libraries:
opencv

C++ Qt:
(we suggest to use qt official downloader https://www.qt.io/download-open-source otherwise you have to install banch of libraries.)
qmake6 (It is probably a better idea to have the IDE download all libraries then run it with makefile without IDE)
qt multimedia lib
qt6.7.1


In Order to establish connection with Mongodb:
boost
mongocxx

Makefile, will compile detectShapes code, which uses opencv, then compiles onxx_pose (cpp code for exercises), and then compiles qt project, with qmake6 PAES.pro.
use $make run to compile and run the project, should work if you have all required libraries.
