#include <iostream>
#include <fstream>
#include "Task.h"
#include "ThreadPool.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

void squareFunc(int i, int *target) {
    for (int j = 0; j < 10000; ++j) {

    }
    *target = i * i;
}

void prevFunc(int i, int *target) {
    for (int j = 0; j < 10000; ++j) {

    }
    *target = i - 1;
}

void nextFunc(int i, int *target) {
    for (int j = 0; j < 10000; ++j) {

    }
    *target = i + 1;
}

void writeToFile(int i) {
    ofstream myFile;
    myFile.open("example.txt");
    myFile << i << "\n";
    myFile.close();
}

void changeToBlack(int x1, int x2, int y1, int y2, Mat *image) {
    int xToUpdate = 0;
    int yToUpdate = 0;
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            Vec3b color = image->at<Vec3b>(Point(j, i));
            if (color[0] > 200 && color[1] > 200 && color[2] > 200) {
                xToUpdate = j;
                yToUpdate = i;
                color[0] = 100;
                color[1] = 155;
                color[2] = 255;
                //std:: cout << color;
                image->at<Vec3b>(Point(xToUpdate, yToUpdate)) = color;
            }
        }
    }
    Vec3b color;

}

int main(int argc, char *argv[]) {
    VideoCapture cap("sample.webm");
    // Check if camera opened successfully
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    ThreadPool *threadPool = new ThreadPool(4);
    threadPool->createThreads(4, 2, threadPool);
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int rate = 60;
    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    VideoWriter video("outcpp1.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(frame_width, frame_height));

    auto timeNow = std::chrono::system_clock::now();
    while (1) {

        Mat image;
        // Capture frame-by-frame
        if (!cap.read(image)) {
            break;
        }
        int xStart1 = 0;
        int xEnd1 = image.rows / 2;
        int yStart1 = 0;
        int yEnd1 = image.cols / 2;

        int xStart2 = image.rows / 2;
        int xEnd2 = image.rows;
        int yStart2 = 0;
        int yEnd2 = image.cols / 2;

        int xStart3 = 0;
        int xEnd3 = image.rows / 2;
        int yStart3 = image.cols / 2;
        int yEnd3 = image.cols;

        int xStart4 = image.rows / 2;
        int xEnd4 = image.rows;
        int yStart4 = image.cols / 2;
        int yEnd4 = image.cols;


        threadPool->setThreadPoolWorking();
        Task task1;
        task1.addTask(std::bind(&changeToBlack, xStart1, xEnd1, yStart1, yEnd1, &image));
        threadPool->addTask(task1);
        Task task2;
        task2.addTask(std::bind(&changeToBlack, xStart2, xEnd2, yStart2, yEnd2, &image));
        threadPool->addTask(task2);
        Task task3;
        task3.addTask(std::bind(&changeToBlack, xStart3, xEnd3, yStart3, yEnd3, &image));
        threadPool->addTask(task3);
        Task task4;
        task4.addTask(std::bind(&changeToBlack, xStart4, xEnd4, yStart4, yEnd4, &image));
        threadPool->addTask(task4);
        threadPool->releaseMeWhenFinished();
        video.write(image);
//        Mat image1 = imread(imageName, IMREAD_COLOR); // Read the file
//        timeNow = std::chrono::system_clock::now();
//        changeToBlack(0, image1.rows, 0, image1.cols, &image1);
//        duration = std::chrono::system_clock::now();
//        std::cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(duration - timeNow)).count()
//                  << " nanoseconds " << std::endl;

//        imshow("Display window1", image);                // Show our image inside it.
//        if (waitKey(1) == 27) // Wait for 'esc' key press to exit
//        {
//            break;
//        }
    }
    auto duration = std::chrono::system_clock::now();
    std::cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(duration - timeNow)).count() << " nanoseconds "
              << std::endl;
    cap.release();
    video.release();

    VideoWriter video1("outcpp2.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(frame_width, frame_height));
    VideoCapture cap1("sample.webm");
    // Check if camera opened successfully
    if (!cap1.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    timeNow = std::chrono::system_clock::now();
    while (1) {

        Mat image;
        // Capture frame-by-frame
        if (!cap1.read(image)) {
            break;
        }


        changeToBlack(0, image.rows, 0, image.cols, &image);
        video1.write(image);
//        imshow("Display window1", image);
//        if (waitKey(1) == 27) // Wait for 'esc' key press to exit
//        {
//            break;
//        }
    }
    duration = std::chrono::system_clock::now();
    std::cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(duration - timeNow)).count() << " nanoseconds "
              << std::endl;
    cap1.release();
//    video1.release();

    return 0;
}

