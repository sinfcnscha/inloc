// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCam.cpp #########################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 21.12.2011
//
//
//
#include "DatCam.h"


DatCam::DatCam(void)
{
	//this->input_vid = "vid_3.wmv";
	//this->input_vid = "example.avi";
	//this->input_vid = "C:\\DAT\\speed_over_ground\\trunk\\src\\dat_sog\\dat_sog\\example.avi";
	//this->cap.open(this->input_vid);

	//this->cap.open(0);
}

DatCam::DatCam(String input){
	this->input_vid = input;
	this->cap.open(this->input_vid);
}

DatCam::DatCam( int device){
	this->cap.open(device);
}


DatCam::~DatCam(void)
{
}

// ##########################################################################################################################
// ######## setzt Device für Input ##########################################################################################
// ##########################################################################################################################
// Liefert true bei erfolg
bool DatCam::setDevice(int device){
	if(this->cap.isOpened()){
		this->cap.release();
	}

	if(this->cap.open(device)){
		return true;
	}else{
		return false;
	}
}

// ##########################################################################################################################
// ######## setzt zu lesendes Video #########################################################################################
// ##########################################################################################################################
// Liefert true bei erfolg
bool DatCam::setInputVid(String input){
	if(this->cap.isOpened()){
		this->cap.release();
	}

	this->input_vid = input;
	if(this->cap.open(input)){
		return true;
	}else{
		return false;
	}
}

// ##########################################################################################################################
// ######## Gibt aktuelles Bild zurück ######################################################################################
// ##########################################################################################################################
// Liefert true bei erfolg
bool DatCam::getCapture(cv::Mat &img){

	return this->cap.read(img);
}