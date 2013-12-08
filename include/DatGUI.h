// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatGUI.h ###########################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 17.01.2012
//
//
//
#pragma once

#include <highgui.h>
#include <string>
#include "DatCoordPoints.h"
#include "DatCoord.h"

#include <cv.h>

class DatGUI
{
public:
	DatGUI(void);
	~DatGUI(void);

	void init(void);
	void update(cv::Mat &img, DatCoordPoint& bildmitte,DatCoordPoints WeltBild, DatCoordPoints BildObjekte, double speed);
	void destroy(void);
};

