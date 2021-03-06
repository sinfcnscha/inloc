// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordMeth.h #####################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, Philip Ga�ner ,
//	Stand: 13.12.2011
//
//
//

#pragma once
#include "DatCoord.h"
#include "DatCoordMeth.h"
#include <vector>
#include "DatPicObjects.h"
#include "DatCoordContainer.h"
#include "DatCoordPoints.h"

#include "InLoc_Richtung.h"

using namespace std;

class DatMapping
{

public:
	DatMapping(void);
	~DatMapping(void);

	// ##########################################################################################################################
	// ######## erstes Mapping ##################################################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	static DatCoordPoints DatMappingInit(DatCoordPoints &pics, DatCoord<int> &referenz_punkt);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## aktualisieren der Map ###########################################################################################
	// ##########################################################################################################################
	// -------------------------------------------------------------------------------------------------------------------------
	static DatCoordPoints DatMappingUpdate(DatCoordPoints &pics_neu, DatCoordPoints &pics_alt, DatCoord<int> &referenz_punkt, int SCHWELLWERT_DIST, InLoc_Richtung &richtung);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Pr�ft umliegende Punkte auf pausiblen Abstand ###################################################################
	// ##########################################################################################################################
	// --------------------------------------------------------------------------------------------------------------------------
	static void ValidateDistance(DatCoordPoints &pics, double epsilon,int count_x,int count_y);
	// **************************************************************************************************************************
};

