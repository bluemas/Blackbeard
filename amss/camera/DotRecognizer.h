///////////////////////////////////////////////////////////
//  DotRecognizer.h
//  Implementation of the Class DotRecognizer
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_3DD6C7C0_C4D0_4758_8EE9_2911312FEBA7__INCLUDED_)
#define EA_3DD6C7C0_C4D0_4758_8EE9_2911312FEBA7__INCLUDED_

#include <opencv2/opencv.hpp>


class DotRecognizer
{

public:
	DotRecognizer();
	virtual ~DotRecognizer();
    bool recognizeDot(cv::Mat& orgImg, cv::Mat& synthImg);

};
#endif // !defined(EA_3DD6C7C0_C4D0_4758_8EE9_2911312FEBA7__INCLUDED_)
