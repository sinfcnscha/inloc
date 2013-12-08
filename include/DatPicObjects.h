// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatPicObjects.h ##################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 08.11.2011
//
//
//
#pragma once

#include "DatCoord.h"
#include <vector>

using namespace std;

template <class T> class DatPicObjects
{
private:
	//string pic_path;
	// ################## Die einzelnen erkannten Objekte/Koordinatenpunkte #####################################################
	vector< DatCoord<T> > pic_objects;

public:
	DatPicObjects(void){};

	~DatPicObjects(void){};

	int getCntPicObj(void){
		return pic_objects.size();
	}

	DatCoord<T> getObjectAt(int pos){
		return this->pic_objects[pos];
	}

	/*void setPicPath(string input){
		this->pic_path = input;
	}

	string getPicPath(void){
		return this->pic_path;
	}*/

	int getPicXCoordAt( int pos){
		return pic_objects[pos].getX();
	}
	int getPicYCoordAt( int pos){
		return pic_objects[pos].getY();
	}
	int getPicWidthAt( int pos){
		return pic_objects[pos].getWidth();
	}
	int getPicHeightAt( int pos){
		return pic_objects[pos].getHeight();
	}

	void addDatCoord(T x, T y, T width, T height){
		DatCoord<T> tmp_pic_object(x,y,width,height);
		this->pic_objects.push_back(tmp_pic_object);
	}

	void insertDatCoord(T x, T y, T width, T height, int pos){
		DatCoord<T> tmp_pic_object(x,y,width,height);
		this->pic_objects.insert(this->pic_objects.begin() + pos, tmp_pic_object);
	}

	void removePicObjCoord(int pos){
		this->pic_objects.erase(this->pic_objects.begin() + pos);
	}

	void removeLastPicObjCoord(int pos){
		this->pic_objects.pop_back();
	}

	void clear(void){
		this->pic_objects.clear();
		//this->pic_path = "";
	}

	void setObjectAt(int pos, T x, T y){
		this->pic_objects[pos].setX(x);
		this->pic_objects[pos].setY(y);
	}
};
