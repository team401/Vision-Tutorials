FRC Team 401 Vision Tutorial
===================


This is FRC Team 401 Copperhead Robotics 2017 Vision Code, the files in this repository are the three most important files used in vision processing for STEAM works. We used a Playstation Eye Webcam as our main camera and used one of the classic green LED rings to help us target the goal. The following files are included:

 - Main.cpp: The main vision processing file that calculates Yaw, Pitch, and Distance
 - flCalculator.cpp: Finds the Focal Length of your camera, import for being used in Main.cpp
 - hsvFinder.cpp: Finds the HSV values of a pixel while looking through your camera

----------


Running one of the Programs
-------------

Open up a unix terminal and navigate to the folder
Creates a directory called build
>mkdir build

Goes inside of build

>cd build

Sets up CMake so it can easily compile code on the fly

>cmake ..

Creates the files in a new folder called bin

>make

Goes back up a directory

>cd ..

Runs the selected file

>./bin/FILENAME

----------

Main.cpp
-------------------
The main vision file used in FRC Team 401's Vision code.

Setup: Lines 18-80
These lines set up the basic variables and configuration for the code which can be configured for each team's needs.
>**Note:** You should make sure that line 26 has the correct camera source, you can check this by running **ls /dev/video*** in a terminal.
 
 Set custom values on the following lines
 
 - Debug mode on line 15
 - HSV values on lines 42-44
 - Focal Length on line 52
 - Image Width and Height on lines 55-56
 - Camera FOV on line 57
 - Contour Filtering parameters on lines 69-79

Debug Mode --- Displays the debug windows and prints data out
Focal Length --- You can find this value by running flCalculator
Image Width / Height --- Most cameras are 640x480, change if you want
Contour Filtering parameters can be found using GRIP
>For GRIP use the following pipe for the data on lines 69-79
>-- HSV Filter > Find Contours > Filter Contours

----------

flCalculator.cpp
-------------------
All of the variables are almost identical to Main.cpp, however when you run the command you should know the distance from the camera to the center of the two rings of the vision tape.

To run the command, use the following syntax
>./bin/flCalculator 401

Where you replace 401 with how the distance away the camera is. It will print a Focal Length based on your distance away.

**NOTE:** Each camera has a different Focal Length and the code is not perfect, for the best result preform multiple test and average your Focal Lengths together.

----------

hsvFinder.cpp
-------------------
The only variable you might have to change is the camera number, which I explained above in the **Main.cpp** section. 

Just click on the pixel you want and it will return the HSV value of that spot, you can then create the range yourself. In my experience you want H and S to be extremely tight, and V is more dependent on your camera settings. These are the ranges that I have for this year:

- H +- 2
- S +- 3
- V +- 153

I set camera settings using a program called **qv4l2**. The settings we are using this year are the following:

  - Brightness: 0
  - Contrast: 0
  - Saturation: 255
  - Hue: 0
  -  Gain: 15
  - Exposure: 20
  - Manual Exposure: On
  - Auto WB: Off
  - Auto Gain: Off
	
