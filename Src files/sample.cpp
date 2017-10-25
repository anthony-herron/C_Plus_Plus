// DUO3D code for if something is too close.

///////////////////////////////////////////////////////////////////////////////////
// This code sample demonstrates the use of DUO SDK in your own applications
// For updates and file downloads go to: http://duo3d.com/
// Copyright 2014-2016 (c) Code Laboratories, Inc.  All rights reserved.
///////////////////////////////////////////////////////////////////////////////////
#include "Sample.h"
#include <iostream>  

#define WIDTH	320
#define HEIGHT	240
#define FPS		30
 using namespace std;
Vec3b HSV2RGB(float hue, float sat, float val)
{
	float x, y, z;

	if(hue == 1) hue = 0;
	else         hue *= 6;

	int i = static_cast<int>(floorf(hue));
	
	float f = hue - i;
	float p = val * (1 - sat);
	float q = val * (1 - (sat * f));
	float t = val * (1 - (sat * (1 - f)));

	//cout << "floor: " << i << " f: " << f << " p= " << p << " q= " << q << " t= " << t << endl;

	switch(i)
	{
		case 0: x = val; y = t; z = p; break;
		//cout << "Case 0: x= " << x << ", y= " << y << ", z= " << z << endl; break; //x = 1 
		case 1: x = q; y = val; z = p;  break;  
		case 2: x = p; y = val; z = t; break;  // x = 0
		case 3: x = p; y = q; z = val; break;  // x = 0
		case 4: x = t; y = p; z = val;break;  
		case 5: x = val; y = p; z = q; break;
		//cout << "Case 5: x= " << x << ", y= " << y << ", z= " << z << endl;  break;  //x = 1
		
	}
	return Vec3b((uchar)(x * 255), (uchar)(y * 255), (uchar)(z * 255));
}


int main(int argc, char* argv[])
{
	// Build color lookup table for depth display
	Mat colorLut = Mat(cv::Size(256, 1), CV_8UC3);
	Mat colorLut2 = Mat(cv::Size(256, 1), CV_8UC3);
	 int fontFace = FONT_HERSHEY_COMPLEX_SMALL;
    	double fontScale = 1.5;
   	 int thickness = 2;
    	Point textOrg(50, 20);
    	string someText = "Too Close";

	for(int i = 0; i < 256; i++)
	{
		colorLut.at<Vec3b>(i) = (i==0) ? Vec3b(0, 0, 0) : HSV2RGB(i/256.0f, 1, 1);
		//if ((i > 126))
		//	cout << "i= " << i << " hsv= " << i/256.0f << endl;
		//if ((i > 212))
			//cout << "i= " << i << " hsv= " << i/256.0f << endl;	
	}

	for(int i = 0; i < 256; i++)
	{
		//if ((i < 42))
			//colorLut2.at<Vec3b>(i) = (i==0) ? Vec3b(0, 0, 0) : HSV2RGB(i/256.0f, 1, 1);
		//if ((i > 156) && (i < 200))
		if ((i > 150) && (i < 210))
			colorLut2.at<Vec3b>(i) = (i==0) ? Vec3b(0, 0, 0) : HSV2RGB(i/256.0f, 1, 1);	
	}

	// Open DUO camera and start capturing
	if(!OpenDUOCamera(WIDTH, HEIGHT, FPS))
	{
		printf("Could not open DUO camera\n");
		return 1;
	}

	printf("DUOLib Version:       v%s\n", GetDUOLibVersion());
	printf("Dense3D Version:      v%s\n", Dense3DGetLibVersion());

	// Open Dense3D
	Dense3DInstance dense3d;
	if(!Dense3DOpen(&dense3d))
	{
		printf("Could not open Dense3D library\n");
		// Close DUO camera
		CloseDUOCamera();
		return 1;
	}
	// Set the Dense3D license (visit https://duo3d.com/account)
	if(!SetDense3DLicense(dense3d, "DXF67-FM9HL-DC9QU-75LFA-YEDKU")) // <-- Put your Dense3D license
	{
		printf("Invalid or missing Dense3D license. To get your license visit https://duo3d.com/account\n");
		// Close DUO camera
		CloseDUOCamera();
		// Close Dense3D library
		Dense3DClose(dense3d);
		return 1;
	}
	// Set the image size
	if(!SetDense3DImageSize(dense3d, WIDTH, HEIGHT))
	{
		printf("Invalid image size\n");
		// Close DUO camera
		CloseDUOCamera();
		// Close Dense3D library
		Dense3DClose(dense3d);
		return 1;
	}
	// Get DUO calibration intrinsics and extrinsics
	DUO_STEREO params;
	if(!GetCameraStereoParameters(&params))
	{
		printf("Could not get DUO camera calibration data\n");
		// Close DUO camera
		CloseDUOCamera();
		// Close Dense3D library
		Dense3DClose(dense3d);
		return 1;
	}
	// Set Dense3D parameters
	SetDense3DScale(dense3d, 3);
	SetDense3DMode(dense3d, 0);
	SetDense3DCalibration(dense3d, &params);
	SetDense3DNumDisparities(dense3d, 4);
	SetDense3DSADWindowSize(dense3d, 6);
	SetDense3DPreFilterCap(dense3d, 28);
	SetDense3DUniquenessRatio(dense3d, 27);
	SetDense3DSpeckleWindowSize(dense3d, 52);
	SetDense3DSpeckleRange(dense3d, 14);
	// Set exposure, LED brightness and camera orientation
	SetExposure(85);
	SetLed(28);
	SetVFlip(true);
	// Enable retrieval of undistorted (rectified) frames
	SetUndistort(true);
	// Create Mat for disparity and depth map
	Mat1f disparity = Mat(Size(WIDTH, HEIGHT), CV_32FC1);
	Mat3f depth3d = Mat(Size(WIDTH, HEIGHT), CV_32FC3);
	// Run capture loop until <Esc> key is pressed
	while((cvWaitKey(1) & 0xff) != 27)
	{
		// Capture DUO frame
		PDUOFrame pFrameData = GetDUOFrame();
		if(pFrameData == NULL) continue;
		// Create Mat for left & right frames
		Mat left = Mat(Size(WIDTH, HEIGHT), CV_8UC1, pFrameData->leftData);
		Mat right = Mat(Size(WIDTH, HEIGHT), CV_8UC1, pFrameData->rightData);
		// Process Dense3D depth map here
		if(Dense3DGetDepth(dense3d, pFrameData->leftData, pFrameData->rightData, 
						  (float*)disparity.data, (PDense3DDepth)depth3d.data))
		{
			uint32_t disparities;
			GetDense3DNumDisparities(dense3d, &disparities);
			
			Mat disp8;
			disparity.convertTo(disp8, CV_8UC1, 255.0/(disparities*16));
			
			Mat mRGBDepth;
			cvtColor(disp8, mRGBDepth, COLOR_GRAY2BGR);
			LUT(mRGBDepth, colorLut, mRGBDepth);
			for (int i = 0; i < 256; i++)
			//for (int i = 0; i < 156; i++)
		       {
			//if ((i > 156) && (i < 200))
			if ((i > 150) && (i < 200))
			{
			   for(int x = 0; x < 50; x++)
			    {	
				if (mRGBDepth.at<Vec3b>(i) == colorLut2.at<Vec3b>(i))
					{
					//cout << "too close" << endl;
					 putText(mRGBDepth, someText, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
					}
			     }
		          }
					
			}  

			
		/**/	//inRange(mRGBDepth, lower_red_hue_range, upper_red_hue_range, mask);
			//if(LUT(mRGBDepth, colorLut2, mRGBDepth))
			//	cout << "too close" << endl;
			//else
			//LUT(mRGBDepth, colorLut, mRGBDepth);
		/*	for(int i = 0; i < 40; i++)
			{
			if (mRGBDepth.at<Vec3b>(i) == colorLut.at<Vec3b>(i))
				cout << "too close" << endl;

			}
		*/	//if ((colorLut.at<Vec3b>(i) < 41))
			//cout << "too close" << endl;

			imshow("Dense3D Disparity Map", mRGBDepth);
			//if (colorLut[250])
				//imshow("Too Close", mRGBDepth);
		}
		// Display images
		imshow("Left Image", left);
		imshow("Right Image", right);
	}
	destroyAllWindows();

	// Close Dense3D library
	Dense3DClose(dense3d);
	// Close DUO camera
	CloseDUOCamera();
	return 0;
}
