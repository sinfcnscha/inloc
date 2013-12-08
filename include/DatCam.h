// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCam.h ###########################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 08.11.2011
//
//
//
#pragma once

#include <cv.h>
#include <highgui.h>

#define DEVICE_STANDARD 0;
using namespace cv;

class DatCam
{
private:
	string input_vid;
	cv::VideoCapture cap;

public:
	DatCam(void);
	DatCam(String input);
	DatCam( int device);
	~DatCam(void);

	// ##########################################################################################################################
	bool setDevice(int device);
	// ##########################################################################################################################
	bool setInputVid(String input);

	// ######## Gibt aktuelles Bild zur�ck ######################################################################################
	bool getCapture(cv::Mat &);
};
