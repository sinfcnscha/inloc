// ############################### InLoc_Cam.cpp #####################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte Änderung: 01.01.2013

#include "InLoc_Cam.h"

InLoc_Cam::InLoc_Cam(void)
{
	//this->input_vid = "vid_3.wmv";
	//this->input_vid = "example.avi";
	//this->input_vid = "C:\\DAT\\speed_over_ground\\trunk\\src\\dat_sog\\dat_sog\\example.avi";
	//this->cap.open(this->input_vid);

	//this->cap.open(0);
}

InLoc_Cam::InLoc_Cam(String input){
	this->input_vid = input;
	this->cap.open(this->input_vid);
}

InLoc_Cam::InLoc_Cam( int device){
	this->cap.open(device);
}


InLoc_Cam::~InLoc_Cam(void)
{
}

// ##########################################################################################################################
// ######## setzt Device für Input ##########################################################################################
// ##########################################################################################################################
// Liefert true bei erfolg
bool InLoc_Cam::setDevice(int device){
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
// ######## Pfad der Videodatei setzen ######################################################################################
// ##########################################################################################################################
// Liefert true bei erfolg
bool InLoc_Cam::setInputVid(String input){
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
bool InLoc_Cam::getCapture(cv::Mat &img){

	return this->cap.read(img);
}