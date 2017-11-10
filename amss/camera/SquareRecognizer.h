///////////////////////////////////////////////////////////
//  SquareRecognizer.h
//  Implementation of the Class SquareRecognizer
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(_SQUARE_RECOGNIZER_H_)
#define _SQUARE_RECOGNIZER_H_

#include <opencv2/opencv.hpp>

using namespace cv;
class SquareRecognizer
{

public:
    SquareRecognizer();
    virtual ~SquareRecognizer();
    bool recognizeSquare(Mat& orgImg, Mat& synthImg);

};
#endif // !defined(_SQUARE_RECOGNIZER_H_)
