// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatObjDetect.cpp ###################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 08.11.2011
//
//
//

#include "DatObjDetect.h"

DatObjDetect::DatObjDetect(string abs_cascade_path)
{
	if (!this->cascade_cpp.load(abs_cascade_path)){
		std::cout << "couldn't load cascade: " << abs_cascade_path << std::endl;
		std::cout << "Empty: " << cascade_cpp.empty() << endl;
		//std::system("pause");
	}
}

DatObjDetect::~DatObjDetect(void)
{
	//delete(this);
}

// ##########################################################################################################################
// ######## detectObjects	#################################################################################################
// ##########################################################################################################################
//
// Liefert die Mittelpunkte der gefundenen Objekte

void DatObjDetect::detectObjects(cv::Mat &img, DatCoordPoints &BildObjekte){
	int /*i,*/ width, height;
	unsigned int i;
	if(!cascade_cpp.empty())
	{
		// There can be more than one face in an image. So create a growable sequence of faces.
		// Detect the objects and store them in the sequence
		vector<cv::Rect> my_objects;
		double scale = 1.1;
		// CV_HAAR_SCALE_IMAGE
		cascade_cpp.detectMultiScale(img, my_objects, scale, 2, 0|CASCADE_SCALE_IMAGE);//, min_size, max_size);	

		for( i = 0; i < my_objects.size(); i++){
			width = my_objects[i].width;
			height = my_objects[i].height;
			BildObjekte.addPixelCoord(my_objects[i].x + width/2, my_objects[i].y + height/2, int(width * scale), (height * scale));
		}
	// doppelt erkannte Objekte aussortieren
	DatCoordMeth::filterDuplicates(BildObjekte);
	}
}

