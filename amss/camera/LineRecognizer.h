///////////////////////////////////////////////////////////
//  LineRecognizer.h
//  Implementation of the Class LineRecognizer
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_99423EA0_8F71_479e_BC46_399A5087FDC7__INCLUDED_)
#define EA_99423EA0_8F71_479e_BC46_399A5087FDC7__INCLUDED_

#include <opencv2/opencv.hpp>
using namespace cv;
class LineRecognizer
{

public:
	LineRecognizer();
	virtual ~LineRecognizer();
    float calculateLineOffset(Mat& orgImg, Mat& synthImg, bool &crossDetect);
};
#endif // !defined(EA_99423EA0_8F71_479e_BC46_399A5087FDC7__INCLUDED_)
