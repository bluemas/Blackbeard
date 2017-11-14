///////////////////////////////////////////////////////////
//  SignRecognizer.h
//  Implementation of the Class SignRecognizer
//  Created on:      31-10-2017 PM 7:55:17
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_70044A3D_0794_4325_802A_75007D298813__INCLUDED_)
#define EA_70044A3D_0794_4325_802A_75007D298813__INCLUDED_
#include <string>

#include <opencv2/opencv.hpp>
#include "../common/Constants.h"


#define NUM_SIGNS 10

using namespace cv;
using namespace std;

class SignRecognizer
{

public:
	SignRecognizer();
	virtual ~SignRecognizer();
    SignType recognizeSign(Mat& orgImage, Mat& synthImage);

private:

    class Symbol{
public:
        Mat img;
        string name;
    };

    Symbol mSymbols[NUM_SIGNS];
    int readRefImages();
    void sortCorners(std::vector<cv::Point2f>& corners, cv::Point2f center);
    double median(cv::Mat channel);

};
#endif // !defined(EA_70044A3D_0794_4325_802A_75007D298813__INCLUDED_)
