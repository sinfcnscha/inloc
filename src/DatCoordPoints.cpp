// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordPoints.cpp #################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 16.11.2011
//
//
//

#include "DatCoordPoints.h"


DatCoordPoints::DatCoordPoints(void)
{
}


DatCoordPoints::~DatCoordPoints(void)
{
	//delete(this);
}

	int DatCoordPoints::getCntPicObj(void){
		return this->pic_objects.size();
	}

	DatCoordPoint DatCoordPoints::getCoordAt(int pos){
		return this->pic_objects[pos];
	}
	int DatCoordPoints::getPixelXCoordAt( int pos){
		return this->pic_objects[pos].getPixelX(); //; .getX();
	}
	int DatCoordPoints::getPixelYCoordAt( int pos){
		return this->pic_objects[pos].getPixelY();
	}
	int DatCoordPoints::getPixelWidthAt( int pos){
		return this->pic_objects[pos].getPixelW();
	}
	int DatCoordPoints::getPixelHeightAt( int pos){
		return this->pic_objects[pos].getPixelH();
	}
	double DatCoordPoints::getWorldXCoordAt( int pos){
		return this->pic_objects[pos].getWorldX();
	}
	double DatCoordPoints::getWorldYCoordAt( int pos){
		return this->pic_objects[pos].getWorldY();
	}
	double DatCoordPoints::getWorldZCoordAt( int pos){
		return this->pic_objects[pos].getWorldZ();
	}
	double DatCoordPoints::getWorldWidthAt( int pos){
		return this->pic_objects[pos].getWorldW();
	}
	double DatCoordPoints::getWorldHeightAt( int pos){
		return this->pic_objects[pos].getWorldH();
	}


	void DatCoordPoints::addCoord(DatCoordPoint Coord){
		this->pic_objects.push_back(Coord);
	}

	void DatCoordPoints::addPixelCoord(int x, int y, int width, int height){

		this->pic_objects.push_back(DatCoordPoint(x,y,width,height));
		//this->pic_objects_world.push_back(DatCoord<double>(0,0,0,0,0));
	}

	void DatCoordPoints::insertPixelCoord(int x, int y, int width, int height, int pos){

		this->pic_objects.insert(this->pic_objects.begin() + pos, DatCoordPoint(x,y,width,height));
	}

	void DatCoordPoints::removePicObjCoord(int pos){
		this->pic_objects.erase(this->pic_objects.begin() + pos);
	}
	void DatCoordPoints::removeLastPicObjCoord(int pos){
		this->pic_objects.pop_back();
	}
	void DatCoordPoints::clear(void){
		this->pic_objects.clear();
	}

	void DatCoordPoints::setWorldObjectAt(int pos, double x, double y, double z){
		this->pic_objects[pos].setWorld(x,y,z);
	}
