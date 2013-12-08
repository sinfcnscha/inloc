// ############################### InLoc_Cam.h #####################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte Änderung: 01.01.2013

#pragma once

#include <iostream>
#include <cv.h>
#include <highgui.h>

#define DEVICE_STANDARD 0;

using namespace cv;

class InLoc_Cam
{
private:
	string input_vid;
	cv::VideoCapture cap;

public:
	InLoc_Cam(void);
	InLoc_Cam(String input);
	InLoc_Cam( int device);
	~InLoc_Cam(void);

	// ##########################################################################################################################
	bool setDevice(int device);
	// ##########################################################################################################################
	bool setInputVid(String input);

	// ######## Gibt aktuelles Bild zurück ######################################################################################
	bool getCapture(cv::Mat &img);
};

