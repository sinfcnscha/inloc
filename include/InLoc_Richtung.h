// ############################### InLoc_Richtung.h ##################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 11.01.2013
// Datum letzte �nderung: 11.01.2013

#pragma once

#include <iostream>

using namespace std;

// ####### Richtungswerte ###################################################################################################
#define RICHTUNG_VOR 0
#define RICHTUNG_RUECK 1
#define RICHTUNG_LINKS 2
#define RICHTUNG_RECHTS 3

class InLoc_Richtung
{
private:
	int richtung;
	int kompass;
	int subtrahend;
	int auslenkung;
	bool schreibschutz;

public:
	InLoc_Richtung(void);
	// wenn nur Richtung subtrahend -1
	InLoc_Richtung(int kompass, int subtrahend);
	~InLoc_Richtung(void);

	// ##########################################################################################################################
	int getRichtung(void);
	// ##########################################################################################################################
	int getKompass(void);
	// ##########################################################################################################################
	int getSubtrahend(void);
	// ##########################################################################################################################
	int getAuslenkung(void);
	// ##########################################################################################################################
	bool isSet(void);
	// ##########################################################################################################################
	bool isSchreibschutz(void);
	// ##########################################################################################################################
	void setRichtung(int input);
	// ##########################################################################################################################
	void setKompass(int input);
	// ##########################################################################################################################
	void setSubtrahend(int input);
	// ##########################################################################################################################
	void setAll(int richtung, int kompass, int subtrahend);
	// ##########################################################################################################################
	void setSchreibschutz(bool input);
	// ##########################################################################################################################
	
};