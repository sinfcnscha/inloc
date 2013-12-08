#pragma once

#include "DatObjPixelCoord.h"
#include <vector>

using namespace std;

class DatPicObj
{
private:
	string pic_path;
	vector<DatObjPixelCoord> pic_objects;

public:
	DatPicObj(void);

	~DatPicObj(void);

	int getCntPicObj(void){
		return pic_objects.size();
	}

	void setPicPath(string input){
		this->pic_path = input;
	}

	string getPicPath(void){
		return this->pic_path;
	}

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

	void addPicObjCoord(int x, int y, int width, int height){
		DatObjPixelCoord tmp_pic_object(x,y,width,height);
		this->pic_objects.push_back(tmp_pic_object);
	}

	void instertPicObjCoord(int x, int y, int width, int height, int pos){
		DatObjPixelCoord tmp_pic_object(x,y,width,height);
		this->pic_objects.insert(this->pic_objects.begin() + pos, tmp_pic_object);
	}

	void removePicObjCoord(int pos){
		this->pic_objects.erase(this->pic_objects.begin() + pos);
	}

	void removeLastPicObjCoord(int pos){
		this->pic_objects.pop_back();
	}
};

