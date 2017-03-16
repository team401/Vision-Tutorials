/*
 * Author: Liam Lawrence
 * Date: 2.20.17
 *
 * Finds HSV Values of the selected pixel
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat frame,
        hsvFrame;

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
    if(event == cv::EVENT_LBUTTONDOWN) {

        // Converts the BGR stream to HSV
        cvtColor(frame, hsvFrame, CV_BGR2HSV);

        // Grabs the HSV color values out of the spot we clicked on
        cv::Vec3b hsv = hsvFrame.at<cv::Vec3b>(y, x);
        int hue = hsv.val[0];
        int saturation = hsv.val[1];
        int value = hsv.val[2];

        std::cout << "H: " << hue << "\nS: " << saturation << "\nV: " << value << "\n------\n";
    }
}


int main() {
    // Connects to our camera
    cv::VideoCapture cap(1);

    // Initial print to keep things pretty
    std::cout << "------\n";

    // Creates Window
    cv::namedWindow("HSV Grabber", CV_WINDOW_AUTOSIZE);

    for(;;) {
        // Grabs frame and converts its to HSV
        cap.read(frame);

        // If we click, grab the color values
        cv::setMouseCallback("HSV Grabber", CallBackFunc, NULL);

        // Shows frame on window
        imshow("HSV Grabber", frame);

        // Hit ESC to quit
        if(cv::waitKey(1) == 27)
            break;
    }
}
