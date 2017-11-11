///////////////////////////////////////////////////////////
//  SignRecognizer.h
//  Implementation of the Class SignRecognizer
//  Created on:      31-10-2017 PM 7:55:17
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_70044A3D_0794_4325_802A_75007D298813__INCLUDED_)
#define EA_70044A3D_0794_4325_802A_75007D298813__INCLUDED_

#include <opencv2/opencv.hpp>
#include "../common/Constants.h"

using namespace cv;
class SignRecognizer
{

public:
	SignRecognizer();
	virtual ~SignRecognizer();
    SignType recognizeSign(Mat& orgImage, Mat& synthImage);

};
#endif // !defined(EA_70044A3D_0794_4325_802A_75007D298813__INCLUDED_)
