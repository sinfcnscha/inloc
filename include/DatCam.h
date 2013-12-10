// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCam.h ###########################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 08.11.2011
//
//
//
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

	// ######## Gibt aktuelles Bild zurück ######################################################################################
	bool getCapture(cv::Mat &);
};

