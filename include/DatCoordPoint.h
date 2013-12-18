// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordPoint.h ####################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 13.12.2011
//
//
//
#pragma once

#include "DatCoord.h"
#include <string>
#include <sstream>

class DatCoordPoint
{
private:
	DatCoord<int> PixelCoord;
	DatCoord<double> WorldCoord;
	bool worldExists;

public:
	DatCoordPoint(void);
	DatCoordPoint(DatCoord<int> input);
	DatCoordPoint(int x, int y, int width, int height);
	~DatCoordPoint(void);

	DatCoord<int>& getPixelCoord();
	void setPixel(int x, int y);
	void setPixel(int x, int y, int width, int height);
	void setPixelX(int x);
	void setPixelY(int y);
	void setPixelW(int width);
	void setPixelH(int height);
	int getPixelX();
	int getPixelY();
	int getPixelW();
	int getPixelH();

	DatCoord<double> &getWorldCoord();
	void setWorld(DatCoord<double> input);
	void setWorld(double x, double y, double z);
	void setWorld(double x, double y, double z, double width, double height);
	void setWorldX(double x);
	void setWorldY(double y);
	void setWorldZ(double z);
	void setWorldW(double width);
	void setWorldH(double height);
	double getWorldX();
    double getWorldY();
	double getWorldZ();
	double getWorldW();
	double getWorldH();

	bool isWorldSet(void);

	// erstellt Stringrepresentation des aktuellen Zustandes
	std::string toString(void);
	std::string toString(std::string title);
};
