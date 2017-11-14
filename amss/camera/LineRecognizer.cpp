///////////////////////////////////////////////////////////
//  LineRecognizer.cpp
//  Implementation of the Class LineRecognizer
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "LineRecognizer.h"

using namespace std;

#define FUDGE_BIAS 0.01 // Bias robot to the left or right


static const cv::Scalar ROI_COLOR   (  0.0, 255.0,   0.0);
static const cv::Scalar TRACK_COLOR (  0.0,   0.0, 255.0);
static const cv::Scalar SELECT_COLOR(255.0, 255.0, 255.0);
static const cv::Scalar NAV_COLOR   (  0.0, 255.0, 255.0);

LineRecognizer::LineRecognizer(){

}

LineRecognizer::~LineRecognizer(){

}

float LineRecognizer::calculateLineOffset(Mat& orgImg, Mat& synthImg, bool &crossDetect) {
   char text[1024];
   float offsetfromcenter;
   //cv::Scalar mean,stddev;
   vector<vector<Point> > contours;
   vector<Vec4i> hierarchy;
   Mat mono,blur,thresh,erodeImg,dilateImg;
   Rect RoiRec(10, 2*orgImg.rows/3, orgImg.cols-20, orgImg.rows/8); //Define region of interest rectangle

   Mat roi(orgImg,RoiRec); // clip image to region of interest 
   cvtColor(roi, mono, COLOR_BGR2GRAY);  // coovert image to grayscale 
   //meanStdDev(mono,mean,stddev);         // Comppute image mean and stddev -- be to used later if needed

   //std::cout<<"Variance: "<<stddev.val[0]<<std::endl;
   GaussianBlur(mono, blur,Size(7, 7), 2, 2); // blur image to remove small irregularities
   threshold(blur, thresh, 35, 255, THRESH_BINARY_INV);//THRESH_OTSU); //Color thresholding makes image more blacka nd white
   Mat erodeElmt = getStructuringElement(MORPH_RECT, Size(3,3));
   Mat dilateElmt = getStructuringElement(MORPH_RECT, Size(5,5));
   erode(thresh, erodeImg, erodeElmt);       // reduces noise Extract edges 
   dilate(erodeImg, dilateImg, dilateElmt);

  findContours(dilateImg, contours, hierarchy, RETR_LIST,CHAIN_APPROX_SIMPLE);// Find the contours of the frame

  rectangle(synthImg, RoiRec, ROI_COLOR,3); // draw region of interest on camera image

  double minMaxCx = -DBL_MAX;
  Rect selected_edge(0,0,0,0); //Edge beging followed
  Rect nav_point(0,0,0,0);
  float areaContourW = 0.0;

  for(unsigned int i = 0; i<contours.size();i++)  //Find the biggest contour 
    {
        Moments mu = moments(contours[i]);
       if (mu.m00 > 300.0) // area threadhold
        {
           Rect r = boundingRect(contours[i]);
           Rect show(r.x+RoiRec.x,r.y+RoiRec.y,r.width,r.height);
           rectangle(synthImg, show, TRACK_COLOR,3); // Draw contours found

           selected_edge.width=20;
           nav_point.width=20;
           double cx;
           cx = r.x + r.width/2;
           //line( CameraImage,Point(cx+10,0),Point(cx+10,CameraImage.rows),Scalar( 0, 255, 0 ),2,8); 
           if (cx > minMaxCx)
             {
               minMaxCx = cx;
               selected_edge=show;
               selected_edge.x=show.x+r.width-10;
               selected_edge.width=20;
               nav_point=show;
               nav_point.x=10+minMaxCx-10;
               nav_point.width=20;
               areaContourW = mu.m00;
             }
         }
     }

  if (fabs(minMaxCx)==DBL_MAX) minMaxCx = roi.cols/2;


#if 0   //Define region of interest rectangle for height
   Rect RoiRecH(orgImg.cols/2 - orgImg.cols/8, orgImg.rows/3, orgImg.cols/4, 2*(orgImg.rows/3) - 2);

   Mat roiH(orgImg,RoiRecH); // clip image to region of interest 
   cvtColor(roiH, mono, COLOR_BGR2GRAY);  // coovert image to grayscale 
   //meanStdDev(mono,mean,stddev);         // Comppute image mean and stddev -- be to used later if needed

   //std::cout<<"Variance: "<<stddev.val[0]<<std::endl;
   GaussianBlur(mono, blur,Size(7, 7), 2, 2); // blur image to remove small irregularities
   threshold(blur, thresh, 10, 255, THRESH_BINARY_INV);//THRESH_OTSU); //Color thresholding makes image more blacka nd white
   erodeElmt = getStructuringElement(MORPH_RECT, Size(3,3));
   dilateElmt = getStructuringElement(MORPH_RECT, Size(5,5));
   erode(thresh, erodeImg, erodeElmt);       // reduces noise Extract edges 
   dilate(erodeImg, dilateImg, dilateElmt);

  findContours(dilateImg, contours, hierarchy, RETR_LIST,CHAIN_APPROX_SIMPLE);// Find the contours of the frame
  float areaContourH = 0.0;
  for(unsigned int i = 0; i<contours.size();i++)  //Find the biggest contour 
  {
      Moments mu = moments(contours[i]);
      Rect r = boundingRect(contours[i]);
      if (mu.m00 > areaContourH)
        areaContourH = mu.m00;      
      if (mu.m00 > 6000.0) {
        Rect show(r.x+RoiRecH.x,r.y+RoiRecH.y,r.width,r.height);
        rectangle(synthImg, show, TRACK_COLOR,3); // Draw contours found
      }

  }
#endif
  if (areaContourW > 5500.0)//&& areaContourH > 6000.0) 
    crossDetect = true;
  else
    crossDetect = false;


  rectangle(synthImg, selected_edge, SELECT_COLOR,3);
  rectangle(synthImg, nav_point, NAV_COLOR,3);
  line( synthImg,Point(synthImg.cols/2,0),Point(synthImg.cols/2,synthImg.rows),Scalar( 0, 0, 0 ),2,8);
  //if (!IsPi3) imshow( "processed", dilateImg );
  offsetfromcenter=1.0f - 2.0f*(float)minMaxCx/roi.cols;
  sprintf(text,"Nav Value %f",offsetfromcenter);
  cv::putText(synthImg, text,cv::Point(10,50),  CV_FONT_HERSHEY_PLAIN, 2,CV_RGB(0,0,0),3);
  return offsetfromcenter+FUDGE_BIAS;
}