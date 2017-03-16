401 Vision
===================
[![GPLV3 licensed](https://img.shields.io/aur/license/yaourt.svg)](./LICENSE.md)

**NOTE:** This code will **_only_** run on a Linux based operating system. [Ubuntu](https://www.ubuntu.com/download) is free, easy to install, and great for beginners. You will also need to install OpenCV, the installation guides for the most common distros of Linux can be found [here](#install).

This is FRC Team 401 Copperhead Robotics' Vision Code for 2017, the files in this repository are the three most important files used in vision processing for STEAMWORKS. We used a Playstation Eye webcam as our main camera and the traditional green LED ring. The following files are included:

 - [Main.cpp:](#main) The main vision processing file that calculates yaw, pitch, and distance
 - [flCalculator.cpp:](#flCalc) Finds the focal length of your camera, import for being used in Main.cpp
 - [hsvFinder.cpp:](#hsvFind) Finds the HSV values of a pixel while looking through your camera

----------
<a name="install"></a>
OpenCV Installation
-------------
[Ubuntu Guide](http://rodrigoberriel.com/2014/10/installing-opencv-3-0-0-on-ubuntu-14-04/)

[Debian Guide](https://indranilsinharoy.com/2012/11/01/installing-opencv-on-linux/)

[Fedora Guide](http://docs.opencv.org/3.1.0/dd/dd5/tutorial_py_setup_in_fedora.html#gsc.tab=0)

Arch Guide - $(yaourt -S opencv)

<a name="runProgram"></a>
Running one of the Programs
-------------

Open up a terminal and navigate to the folder and run the following commands:

Create a directory called build
```shell
mkdir build
```
Go inside of build
```shell
cd build
```
Set up CMake so it can easily compile code on the fly
```shell
cmake ..
```
Compile the code to create runnable files
```shell
make
```
Go back up a directory
```shell
cd ..
```
Run the selected file
```shell
./bin/FILENAME
```	
----------

For any questions about our vision code you can reach us [here](http://team401.org/contact), good luck to all of the teams out there this year!
