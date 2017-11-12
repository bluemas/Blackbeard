///////////////////////////////////////////////////////////
//  CameraReader.h
//  Implementation of the Class CameraReader
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_0A9D67FC_B1A3_4c04_B3B8_58B5020F0F48__INCLUDED_)
#define EA_0A9D67FC_B1A3_4c04_B3B8_58B5020F0F48__INCLUDED_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "PI3OpencvCompat.h"


class CameraReader
{

public:
    CameraReader();
    virtual ~CameraReader();
    int readCamera(cv::Mat &image);

    
private:
    CvCapture* mCapture;



};
#endif // !defined(EA_0A9D67FC_B1A3_4c04_B3B8_58B5020F0F48__INCLUDED_)
