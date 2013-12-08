// ############################### InLoc_Richtung.cpp ################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 11.01.2013
// Datum letzte Änderung: 11.01.2013

#pragma once

#include <iostream>
#include "InLoc_Richtung.h"

using namespace std;


InLoc_Richtung::InLoc_Richtung(void)
{
	richtung = RICHTUNG_VOR;
	kompass = -1;
	subtrahend = -1;
	auslenkung = -1;
	schreibschutz = false;
}
// wenn nur Richtung subtrahend -1
InLoc_Richtung::InLoc_Richtung(int kompass, int subtrahend)
{
	richtung = RICHTUNG_VOR;
	kompass = kompass;
	subtrahend = subtrahend;
	auslenkung = -1;
	schreibschutz = false;
}

InLoc_Richtung::~InLoc_Richtung(void)
{
}

// ##########################################################################################################################
int InLoc_Richtung::getRichtung(void)
{
	//if(isSet())
	//{
		if( (auslenkung <= 45) || (auslenkung >= 315))
		{
			richtung = RICHTUNG_VOR;
		}
		if( (auslenkung > 45) && (auslenkung < 135))
		{
			richtung = RICHTUNG_RECHTS;
		}
		if( (auslenkung >= 135) && (auslenkung <= 225))
		{
			richtung = RICHTUNG_RUECK;
		}
		if( (auslenkung > 225) && (auslenkung < 315))
		{
			richtung = RICHTUNG_LINKS;
		}
	//}
	
	return richtung;
}
// ##########################################################################################################################
int InLoc_Richtung::getKompass(void)
{
	return kompass;
}
// ##########################################################################################################################
int InLoc_Richtung::getAuslenkung(void)
{
	return auslenkung;
}
// ##########################################################################################################################
int InLoc_Richtung::getSubtrahend(void)
{
	return subtrahend;
}
// ##########################################################################################################################
bool InLoc_Richtung::isSet(void)
{
	if (subtrahend < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
// ##########################################################################################################################
bool InLoc_Richtung::isSchreibschutz(void)
{
	return schreibschutz;
}
// ##########################################################################################################################
void InLoc_Richtung::setRichtung(int input)
{
	richtung = input;
}
// ##########################################################################################################################
void InLoc_Richtung::setKompass(int input)
{
	if(!schreibschutz)
	{
		kompass = input;
	}

	if(subtrahend > kompass)
	{
		auslenkung = 360 - abs(kompass - subtrahend);
	}
	else
	{
		auslenkung = kompass - subtrahend;
	}
}
// ##########################################################################################################################
void InLoc_Richtung::setSubtrahend(int input)
{
	subtrahend = input;
}
// ##########################################################################################################################
void InLoc_Richtung::setAll(int richtung, int kompass, int subtrahend)
{
	richtung = richtung;
	kompass = kompass;
	subtrahend = subtrahend;
}

// ##########################################################################################################################
void InLoc_Richtung::setSchreibschutz(bool input)
{
	schreibschutz = input;
}

