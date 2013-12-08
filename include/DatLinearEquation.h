// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatLinearEquation.h ################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 29.11.2011
//
//
//
#pragma once

#include "DatCoord.h"

class DatLinearEquation
{
private:
	double steigung;
	double y_schnittpunkt;

public:
	DatLinearEquation(DatCoord<int> p1, DatCoord<int> p2);
	DatLinearEquation(DatCoord<double> p1, DatCoord<double> p2);
	DatLinearEquation(DatCoord<int> p1, double Steigung);

	~DatLinearEquation(void);

	// ##########################################################################################################################
	// ######## ermittelt x f�r gegebenes y #####################################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	int getXfor( int y);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## ermittelt y f�r gegebenes x #####################################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	int getYfor( int x);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## gibt Steigung der Geraden zur�ck ################################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	double getSteigung();
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## gibt Schnittpunkt mit y-Achse zur�ck ############################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	double getYschnitt();
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## erstellt neue Geradengleichung ##################################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	void setLinearEquation(DatCoord<int> p1, DatCoord<int> p2);
	void setLinearEquation(DatCoord<double> p1, DatCoord<double> p2);
	// **************************************************************************************************************************
};

