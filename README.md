401 Vision
===================
[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE.md)

**NOTE:** This code will **_only_** run on a Linux based operating system. [Ubuntu](https://www.ubuntu.com/download) is free, easy to install, and great for beginners.

This is FRC Team 401 Copperhead Robotics' 2017 Vision Code, the files in this repository are the three most important files used in vision processing for STEAMWORKS. We used a Playstation Eye webcam as our main camera and the traditional green LED ring. The following files are included:

 - [Main.cpp:](#main) The main vision processing file that calculates yaw, pitch, and distance
 - [flCalculator.cpp:](#flCalc) Finds the Focal Length of your camera, import for being used in Main.cpp
 - [hsvFinder.cpp:](#hsvFind) Finds the HSV values of a pixel while looking through your camera

----------


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
<a name="main"></a>
[Main.cpp](src/main.cpp)
-------------------
The main vision file used in FRC Team 401's Vision code.

Setup: Lines 18-80

These lines set up the basic variables and configuration for the code which can be configured for each team's needs.
 
Set custom values on the following lines:

Debug: 15

```cpp
 //Enable to see debug windows and print statements
 bool debug = true;
 ```

Current Camera: 26
```cpp
// Type $(ls /dev/video*) into a terminal to find out what number should be inside cap()
cv::VideoCapture cap(1);
```

HSV ranges: 42 - 44
```cpp
    // Place the lower bound in [0] and the upper in [1]
    int H[2] = {58, 62};
    int S[2] = {253, 255};
    int V[2] = {120, 185};
```
    
Focal Length: 52
```cpp
// You can find this value by running flCalculator
double focalLength = 524.9;
```
    
Image Width, Height, and Camera FOV: 55 - 57
```cpp
// Our camera has a view of 640x480 pixels and a FOV of 75 degrees
int imageWidth = 640,
    imageHeight = 480;
double cameraFOV = 75.0, 
```
    
Contour Filtering: 69 - 79
```cpp
// Parameters can be found using GRIP
    double minArea = 57,
           minPerimeter = 50,
           minWidth = 25,
           maxWidth = 1000,
           minHeight = 4,
           maxHeight = 1000,
           solidity[] = {62, 100},
           maxVertices = 1000000,
           minVertices = 4,
           minRatio = 1.0,
           maxRatio = 6.0;
```
           
>For GRIP use the following pipe for the data on lines 69-79
>-- Camera > HSV Filter > Find Contours > Filter Contours

----------
<a name="flCalc"></a>
[flCalculator.cpp](src/flCalculator.cpp)
-------------------
All of the variables are almost identical to Main.cpp, however when you run the command you should know the distance from the camera to the center between the two rings of the retro reflective tape.

To run the command, use the following syntax
```shell
./bin/flCalculator 401
```

Replace 401 with the distance away the camera is in inches. It will then print out the Focal Length for your camera. Try to have the center of the goal be lined up on the center of the entire frame (the white dot) for the best results.

**NOTE:** Each camera has a different Focal Length and the code is not perfect, for the best results, preform multiple tests and average your Focal Lengths together.

----------
<a name="hsvFind"></a>
[hsvFinder.cpp](src/hsvFinder.cpp)
-------------------
The only variable you might have to change is the camera number, which I explained above in the **[Main.cpp](#main)** section. 

Just click on the pixel you want and it will return the HSV value of that spot, you can then create the range yourself. In my experience you want H and S to be extremely tight, and V is more dependent on your camera settings. These are the ranges that I have for this year:

- H +- 2
- S +- 3
- V +- 153

I set camera settings using a program called **[qv4l2](https://www.google.com/search?sourceid=chrome-psyapi2&ion=1&espv=2&ie=UTF-8&q=how%20to%20install%20qv4l2&oq=how%20to%20install%20qv4l2&aqs=chrome..69i57.5651j0j7)**. The settings we are using this year are the following:

  - Brightness: 0
  - Contrast: 0
  - Saturation: 255
  - Hue: 0
  - Gain: 15
  - Exposure: 20
  - Manual Exposure: On
  - Auto WB: Off
  - Auto Gain: Off
	
----------

For any questions about our vision code you can reach us [here](http://team401.org/contact), good luck to all of the teams out there this year!
