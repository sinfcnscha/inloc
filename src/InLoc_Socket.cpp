// ############################### InLoc_Socket.cpp ###########################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte Änderung: 03.01.2013

#include "InLoc_Socket.h"

InLoc_Socket::InLoc_Socket(void)
{
	//err?
}

int InLoc_Socket::startWinsock(){
	WSADATA wsa;
	return (int)WSAStartup(MAKEWORD(2,0),&wsa);
}

int InLoc_Socket::sendString(string message)
{
	long rc;
	SOCKET s;
	SOCKADDR_IN addr;

	rc = InLoc_Socket::startWinsock();

	s = socket(AF_INET, SOCK_STREAM, 0);
	cout << "socket: " << s << endl;

	memset(&addr,0,sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(s, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	
	if(connect < 0){
		cout << "FEHLER: fehler code: "<< WSAGetLastError() << endl;
		return -1;
	}

	send(s, message.c_str(), message.length(), 0);
	return 0;
}


