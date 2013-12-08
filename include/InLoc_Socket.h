// ############################### InLoc_Socket.h #############################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte Änderung: 03.01.2013

#pragma once

#include <string>
#include <iostream>
#include <WinSock.h>
#include <Windows.h>

using namespace std;	

class InLoc_Socket
{
private:

public:
	InLoc_Socket(void);
	int startWinsock(void);
	int sendString(string message);

};