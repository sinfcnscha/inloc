// ############################### InLoc_ReadCom.cpp #################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 06.01.2013
// Datum letzte Änderung: 09.01.2013

#include "InLoc_ReadCom.h"
#include "InLoc_Utils.h"

InLoc_ReadCom::InLoc_ReadCom(void)
{
}


InLoc_ReadCom::InLoc_ReadCom( int input){
	port = input;
}


InLoc_ReadCom::~InLoc_ReadCom(void)
{
}

void InLoc_ReadCom::getValues(int values[], int valuesLen)
{
	int i = 0;

	HANDLE hCom;
	DWORD iBytesRead;
	DWORD dwEventMask;
	DCB   dcb;
	hCom = CreateFile ("COM3", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	dcb.DCBlength = sizeof(DCB); 
	GetCommState (hCom, &dcb);   		         	 
	dcb.BaudRate  = 115200;        				  
	dcb.ByteSize  = 8;          				  
	dcb.Parity    = NOPARITY;   			  
	dcb.StopBits  = ONESTOPBIT;
	SetCommState (hCom, &dcb);   			 

	string line = "";
	// Stichwort Abtasttheorem
	const int LINE_LEN = 60;

	if(!SetCommMask(hCom, EV_RXCHAR ))
		cout << "fehler SetCommmMask" << endl;

	if(WaitCommEvent(hCom, &dwEventMask, NULL))
		{
			char Byte=0;
			float Wert=0;
			DWORD dwBytesRecieved;

			for(int j = 0; j < LINE_LEN; j++)
			{
				ReadFile (hCom,&Byte,sizeof (Byte), &dwBytesRecieved, NULL);
				line += Byte;
			}
	}

	CloseHandle(hCom);
	
	const char BEGIN = '#';
	const char END = '*';
	const char FRAME = '#';
	const char DELIMITER = ';';
	int pos = 0;
	int posBegin = -1;
	int posEnd = -1;

	posBegin = line.find_first_of(FRAME, 0) + 1;

	if(line[posBegin] == FRAME)
	{
		posBegin++;
	}

	posEnd = line.find_first_of(FRAME, posBegin + 1);

	// Messergebnisse in Array schreiben
	line = line.substr(posBegin, posEnd - posBegin);
	pos = line.find_first_of(DELIMITER,0);
	values[i] = InLoc_Utils::stringToInt( line.substr(0,pos));
	pos++;

	for(i = 1; i < valuesLen; i++)
	{
		line = line.substr(pos, line.length() - pos);
		pos = line.find_first_of(DELIMITER,0);
		values[i] = InLoc_Utils::stringToInt( line.substr(0,pos));
		pos++;
	}

}

