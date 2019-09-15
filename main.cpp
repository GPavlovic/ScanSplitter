#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    String imageName ("test.jpg"); // by default
    if( argc > 1)
    {
        imageName = argv[1];
    }
    Mat image;
    image = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // Create a mask for the image
    // TODO: This is probably not going to work for more complicated images, needs work
    Mat mask;
    inRange(image, Scalar(100, 0, 0), Scalar(255, 255, 255), mask);
    // Contours and their hierarchies
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(mask.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
    // Contoured image is a clone of original
    Mat contouredImage = image.clone();
    // Draw contours
    drawContours(contouredImage, contours, 1, Scalar(255, 0 , 0), 2); // Draw the second contour 
    imshow("countoured Image", contouredImage); // Show the contoured image

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}