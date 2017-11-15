///////////////////////////////////////////////////////////
//  SignRecognizer.cpp
//  Implementation of the Class SignRecognizer
//  Created on:      31-10-2017 PM 7:55:17
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include <iostream>

#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>    // std::max

#include "SignRecognizer.h"

#if  defined(_WIN32) || defined(_WIN64)
#define IMAGE_DIR "signs\\"
#else
#define IMAGE_DIR "signs/"
#endif

SignRecognizer::SignRecognizer() {
    readRefImages();
}

SignRecognizer::~SignRecognizer() {

}

int SignRecognizer::readRefImages() {

    mSymbols[0].img = imread(IMAGE_DIR"arrowL.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[0].img.data)
        return -1;
    threshold(mSymbols[0].img, mSymbols[0].img, 100, 255, 0);
    mSymbols[0].name = "Left 90";

    mSymbols[1].img = imread(IMAGE_DIR"arrowR.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[1].img.data)
        return -1;
    threshold(mSymbols[1].img, mSymbols[1].img, 100, 255, 0);
    mSymbols[1].name = "Right 90";

    mSymbols[2].img = imread(IMAGE_DIR"arrowT.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[2].img.data)
        return -1;
    threshold(mSymbols[2].img, mSymbols[2].img, 100, 255, 0);
    mSymbols[2].name = "Turn Around";

    mSymbols[3].img = imread(IMAGE_DIR"arrowS.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[3].img.data)
        return -1;
    threshold(mSymbols[3].img, mSymbols[3].img, 100, 255, 0);
    mSymbols[3].name = "Straight";

    mSymbols[4].img = imread(IMAGE_DIR"arrowPush.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[4].img.data)
        return -1;
    threshold(mSymbols[4].img, mSymbols[4].img, 100, 255, 0);
    mSymbols[4].name = "Push Can";

    mSymbols[5].img = imread(IMAGE_DIR"arrowStop.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[5].img.data)
        return -1;
    threshold(mSymbols[5].img, mSymbols[5].img, 100, 255, 0);
    mSymbols[5].name = "Stop";

    mSymbols[6].img = imread(IMAGE_DIR"arrowB.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[6].img.data)
        return -1;
    threshold(mSymbols[6].img, mSymbols[6].img, 100, 255, 0);
    mSymbols[6].name = "Ball";

    mSymbols[7].img = imread(IMAGE_DIR"arrowL45.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[7].img.data)
        return -1;
    threshold(mSymbols[7].img, mSymbols[7].img, 100, 255, 0);
    mSymbols[7].name = "Left 45";

    mSymbols[8].img = imread(IMAGE_DIR"arrowR45.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[8].img.data)
        return -1;
    threshold(mSymbols[8].img, mSymbols[8].img, 100, 255, 0);
    mSymbols[8].name = "Right 45";

    mSymbols[9].img = imread(IMAGE_DIR"arrowGo.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (!mSymbols[9].img.data)
        return -1;
    threshold(mSymbols[9].img, mSymbols[9].img, 100, 255, 0);
    mSymbols[9].name = "Go";

    return 0;
}

double SignRecognizer::median(cv::Mat channel) {
    double m = (channel.rows*channel.cols) / 2;
    int    bin = 0;
    double med = -1.0;

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    cv::Mat hist;
    cv::calcHist(&channel, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    for (int i = 0; i < histSize && med < 0.0; ++i)
    {
        bin += cvRound(hist.at< float >(i));
        if (bin > m && med < 0.0)
            med = i;
    }

    return med;
}

void SignRecognizer::sortCorners(std::vector<cv::Point2f>& corners, cv::Point2f center) {
    std::vector<cv::Point2f> top, bot;

    for (unsigned int i = 0; i < corners.size(); i++)
    {
        if (corners[i].y < center.y)
            top.push_back(corners[i]);
        else
            bot.push_back(corners[i]);
    }

    cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
    cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
    cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
    cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];

    corners.clear();
    corners.push_back(tl);
    corners.push_back(tr);
    corners.push_back(br);
    corners.push_back(bl);
}

SignType SignRecognizer::recognizeSign(Mat& orgImage, Mat& synthImage) {
    Mat new_image;
    Mat greyImg;
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    SignType resultSign = SignType::SignNone;
    cvtColor(orgImage, greyImg, CV_RGB2GRAY);

    //threshold(greyImg, greyImg, 100, 255, 0);



    GaussianBlur(greyImg, greyImg, Size(5, 5), 2, 2);


    double med;
    double sigma = 0.33;
    int lower, upper;

    /// Detect edges using canny
    med = median(greyImg);
    lower = int(max(0, (int)((1.0 - sigma) * med)));
    upper = int(min(255, (int)((1.0 + sigma) * med)));
    Canny(greyImg, canny_output, lower, upper);


    #if 0
            if (!IsPi3) imshow("B", canny_output);
    #endif
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE,
        CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<Point> approxRect;

    for (size_t i = 0; i < contours.size(); i++) {

        approxPolyDP(contours[i], approxRect,
            arcLength(Mat(contours[i]), true) * 0.01, true);

        if (approxRect.size() == 4) {
            double area = contourArea(contours[i]);


            if (area > 400)

            {
                std::vector<cv::Point2f> corners;

                vector<Point>::iterator vertex;
                vertex = approxRect.begin();
                //vertex++;
                circle(synthImage, *vertex, 2, Scalar(0, 0, 255), -1, 8, 0);
                corners.push_back(*vertex);
                vertex++;
                circle(synthImage, *vertex, 2, Scalar(0, 0, 255), -1, 8, 0);
                corners.push_back(*vertex);
                vertex++;
                circle(synthImage, *vertex, 2, Scalar(0, 0, 255), -1, 8, 0);
                corners.push_back(*vertex);
                vertex++;
                circle(synthImage, *vertex, 2, Scalar(0, 0, 255), -1, 8, 0);
                corners.push_back(*vertex);

                Moments mu;
                mu = moments(contours[i], false);
                Point2f center((float)(mu.m10 / mu.m00), (float)(mu.m01 / mu.m00));

                sortCorners(corners, center);

                // Define the destination image
                Mat correctedImg = ::Mat::zeros(195, 271, CV_8UC3);

                // Corners of the destination image
                std::vector<cv::Point2f> quad_pts;
                quad_pts.push_back(Point2f(0, 0));
                quad_pts.push_back(Point2f((float)correctedImg.cols, 0.0f));
                quad_pts.push_back(Point2f((float)correctedImg.cols, (float)correctedImg.rows));
                quad_pts.push_back(Point2f(0.0f, (float)correctedImg.rows));

                // Get transformation matrix
                Mat transmtx = getPerspectiveTransform(corners, quad_pts);

                // Apply perspective transformation
                warpPerspective(orgImage, correctedImg, transmtx,
                    correctedImg.size());

                Mat correctedImgBin;

                cvtColor(correctedImg, correctedImgBin, CV_RGB2GRAY);

                //equalizeHist(correctedImgBin, correctedImgBin);

                correctedImgBin.copyTo(new_image);

                threshold(correctedImgBin, correctedImgBin, 140, 255, 0);

                //if (!IsPi3) imshow("B", correctedImgBin);


                double minVal, maxVal, medVal;


                minMaxLoc(new_image, &minVal, &maxVal);

                medVal = (maxVal - minVal) / 2;

                threshold(new_image, new_image, medVal, 255, 0);

                //if (!IsPi3) imshow("C", new_image);

                Mat diffImg;

                int match, minDiff, diff;
                minDiff = 12000;
                match = -1;

                for (int i = 0; i < NUM_SIGNS; i++) {

                    bitwise_xor(new_image, mSymbols[i].img, diffImg,
                        noArray());

                    diff = countNonZero(diffImg);
                    if (diff < minDiff) {
                        minDiff = diff;
                        match = i;
                    }

                    if (i == 0) {

                        //if (!IsPi3)   imshow("B",diffImg);


                    }
                }

                //if (!IsPi3) imshow("B", correctedImg);


                if (match != -1) {
                    putText(synthImage, mSymbols[match].name, Point(320, 30), 1,
                        2, Scalar(0, 255, 0), 2);
                    printf("Match %s\n", mSymbols[match].name.c_str());
                    resultSign = (SignType)match;

                }
                else printf("No Match\n");


            }

        }
    }
    return resultSign;
}

