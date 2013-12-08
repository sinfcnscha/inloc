// ############################### InLoc_Utils.cpp ###################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte Änderung: 01.01.2013

#include "InLoc_Utils.h"

// ##########################################################################################################################
// ######## wandelt einen String in ein Integer um ##########################################################################
// ##########################################################################################################################
// 
int InLoc_Utils::stringToInt(string input)
{
	int ret = 0;
	stringstream s(input);

	s >> ret;

	return ret;
}
