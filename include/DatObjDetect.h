// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatObjDetect.h #####################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 08.11.2011
//
//
//
#pragma once
#include "DatCoordMeth.h"
#include "DatPicObjects.h"
#include "DatCoordPoints.h"
#include <ctype.h>
#include <opencv2/core/core.hpp>

using namespace cv;

class DatObjDetect
{

private:
	int x, y, height, width, x_m, y_m;
	
	// Load the HaarClassifierCascade
	CascadeClassifier cascade_cpp;
	


public:
	DatObjDetect(string abs_cascade_path);
	~DatObjDetect(void);

	// ##########################################################################################################################
	// ######## Liefert die Mittelpunkte der gefundenen Objekte	#################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	void detectObjects(cv::Mat &img, DatCoordPoints &BildObjekte);
	// **************************************************************************************************************************
};

