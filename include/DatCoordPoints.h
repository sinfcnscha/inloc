// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordPoints.h ###################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 16.11.2011
//
//
//
#pragma once

#include "DatCoord.h"
#include <vector>
#include "DatCoordPoint.h"

using namespace std;

class DatCoordPoints
{

	private:
	// ################## Die einzelnen erkannten Objekte/Koordinatenpunkte #####################################################
	//vector<DatCoord<int>> pic_objects_pixel;
	//vector<DatCoord<double>> pic_objects_world;
	vector<DatCoordPoint> pic_objects;

public:
	DatCoordPoints(void);
	~DatCoordPoints(void);

	int getCntPicObj(void);

	DatCoordPoint& getCoordAt(int pos);

	int getPixelXCoordAt( int pos);
	int getPixelYCoordAt( int pos);
	int getPixelWidthAt( int pos);
	int getPixelHeightAt( int pos);
	double getWorldXCoordAt( int pos);
	double getWorldYCoordAt( int pos);
	double getWorldZCoordAt( int pos);
	double getWorldWidthAt( int pos);
	double getWorldHeightAt( int pos);

	void addCoord(DatCoordPoint Coord);
	void addPixelCoord(int x, int y, int width, int height);
	void insertPixelCoord(int x, int y, int width, int height, int pos);
	void removePicObjCoord(int pos);
	void removeLastPicObjCoord(int pos);
	void clear(void);

	void setWorldObjectAt(int pos, double x, double y, double z);

};

