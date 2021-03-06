// ############################### InLoc_Cam.h #####################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte �nderung: 01.01.2013

#pragma once

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define DEVICE_STANDARD 0;

using namespace cv;

class InLoc_Cam
{
private:
	std::string input_vid;
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

	// ######## Gibt aktuelles Bild zur�ck ######################################################################################
	bool getCapture(cv::Mat &img);
};

