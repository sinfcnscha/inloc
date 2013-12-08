// ############################### InLoc_ReadCom.h #################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 06.01.2013
// Datum letzte Änderung: 06.01.2013

#pragma once

#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

class InLoc_ReadCom
{
private:
	int port;

public:
	InLoc_ReadCom(void);
	InLoc_ReadCom(int input);
	~InLoc_ReadCom(void);

	// ##########################################################################################################################
	void getValues(int values[], int valuesLen);
	// ##########################################################################################################################

};
