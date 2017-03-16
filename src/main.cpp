/*
 * Author: Liam Lawrence
 * Date: 2.25.17
 *
 * FRC Team 401 Vision Code rewrite for the 2017 game STEAMWORKS
 */

//#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

// Boolean used for showing image streams and printing data
bool debug = true;

int main() {
    // Debug image processing
    cv::Mat goodCont,
            drawing;

    // Image processing
    cv::Mat latestFrame,
            hsvFrame,
            rangeFrame;
    cv::VideoCapture cap(0);

    // Shapes and centers
    cv::Rect rect,
             rect2;
    cv::Point topLeft,
              bottomRight,
              center,
              topCenter,
              bottomCenter;

    // Contour lists
    std::vector<std::vector<cv::Point>> contours,
                                        goodContours;

    // HSV ranges
    int H[2] = {58, 62},
        S[2] = {253, 255},
        V[2] = {120, 185};

    // Data to send to RIO
    double yaw,
           pitch,
           distance;

    // Used to calculate distance
    double focalLength = 524.9;

    // Used in yaw and pitch calculations
    int imageWidth = 640,
        imageHeight = 480;
    double cameraFOV = 75.0,                  // In degrees
           horizontalDPP = cameraFOV/640.0,   // Degrees Per Pixel
           verticalDPP = cameraFOV/480.0;

    // Contour Filtering variables
    std::vector<cv::Point> hull;
    cv::Rect bb;
    double area,
           solid,
           ratio;

    // Contour filtering parameters
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

    // Main loop
    for(;;) {
        // Clears out our old contour list
        contours.clear();

        // Reads in the latest frame, converts it to HSV, and then filters out the colors we don't want
        cap.read(latestFrame);
        cv::cvtColor(latestFrame, hsvFrame, CV_BGR2HSV);
        cv::inRange(hsvFrame, cv::Scalar(H[0], S[0], V[0]), cv::Scalar(H[1], S[1], V[1]), rangeFrame);

        // Finds contours for our image stream
        findContours(rangeFrame, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        // Filters the contours
        goodContours.clear();
        for (std::vector<cv::Point> currentContour: contours) {
            bb = boundingRect(currentContour);
            if (bb.width < minWidth || bb.width > maxWidth) continue;
            if (bb.height < minHeight || bb.height > maxHeight) continue;
            area = cv::contourArea(currentContour);
            if (area < minArea) continue;
            if (arcLength(currentContour, true) < minPerimeter) continue;
            cv::convexHull(cv::Mat(currentContour, true), hull);
            solid = 100 * area / cv::contourArea(hull);
            if (solid < solidity[0] || solid > solidity[1]) continue;
            if (currentContour.size() < minVertices || currentContour.size() > maxVertices) continue;
            ratio = (double) bb.width / (double) bb.height;
            if (ratio < minRatio || ratio > maxRatio) continue;
            goodContours.push_back(currentContour);
        }

        // If there is a goal, do processing on it
        if(goodContours.size() >= 2) {
            // Finds the two rectangles the goal has on it
            rect = boundingRect(goodContours[1]);
            rect2 = boundingRect(goodContours[0]);

            // Finds the top left point of the higher rectangle
            topLeft.x = rect.x;
            topLeft.y = rect.y;

            // Finds the bottom right point of the lower rectangle
            bottomRight.x = rect2.x + rect2.width;
            bottomRight.y = rect2.y + rect2.height;

            // Finds the center points
            center.x = (topLeft.x + bottomRight.x) / 2;
            center.y = (topLeft.y + bottomRight.y) / 2;
            topCenter.x = (rect.x + (rect.x + rect.width)) / 2;
            topCenter.y = (topLeft.y);
            bottomCenter.x = (rect2.x + (rect2.x + rect2.width)) / 2;
            bottomCenter.y = (bottomRight.y);

            // Calculates Yaw and Pitch in degrees
            yaw = ((center.x - ((imageWidth / 2) - 0.5)) * horizontalDPP);
            pitch = ((center.y - ((imageHeight / 2) - 0.5)) * verticalDPP);

            // Calculate the diagonal distance from the camera to the center of the retro reflective tape
            distance = 10 * focalLength / (bottomCenter.y - topCenter.y);
        }

        // Debug drawings and image streams
        if(debug) {
            // Refreshes the Mats
            drawing = cv::Mat::zeros(latestFrame.size(), CV_8UC3);
            goodCont = cv::Mat::zeros( latestFrame.size(), CV_8UC3 );

            // Draws the contours and filtered contours onto their respective Mats
            for(int i = 0; i < contours.size(); i++) {
                drawContours(drawing, contours, i, cv::Scalar(100, 100, 100));
            }
            for(int i = 0; i < goodContours.size(); i++) {
                drawContours(goodCont, goodContours, i, cv::Scalar(100,100,100));
            }

            // Draws the centers of the goal on the filtered contours
            circle(goodCont, bottomCenter, 1, cv::Scalar(255,0,255), 2);
            circle(goodCont, topCenter, 1, cv::Scalar(0,255,255), 2);
            circle(goodCont, center, 1, cv::Scalar(0,100,255), 2);

            // Draws the top left and bottom right of the goal on the filtered contours
            circle(goodCont, topLeft, 1, cv::Scalar(255,255,0), 2);
            circle(goodCont, bottomRight, 1, cv::Scalar(255,100,0), 2);

            // Draws a dot in the center of the image
            circle(goodCont, cv::Point(imageWidth/2 - 0.5, imageHeight/2 - 0.5), 1, cv::Scalar(255,255,255), 2);

            // Displays image streams on the screen
            imshow("Contours ", drawing);
            imshow("Filtered Contours", goodCont);
            imshow("Latest Frame", latestFrame);
            std::cout << "==========\nYAW: " << yaw << "\nPITCH: " << pitch << "\nDISTANCE: " << distance << "==========\n";
        }

        // Adds a little bit of delay
        // Hit ESC to kill the program
        if(cv::waitKey(1) == 27)
            break;
    }
}
