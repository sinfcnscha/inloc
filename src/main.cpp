// ############################### main.c #####################################
// Projekt: Bachelorarbeit Indoorlokalisation mittels AdaBoost
// Autor: Christian Schauer
// Datum Erstellung: 01.01.2013
// Datum letzte Änderung: 12.01.2013

#pragma once

#include <stdio.h>

#include <iostream>
//#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
//#include <WinSock2.h>
//#include <WinSock.h>
//#include <Windows.h>
//#include <conio.h>
//#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "InLoc_Cam.h"
//#include "InLoc_Socket.h"
//#include "InLoc_ReadCom.h"
#include "InLoc_Richtung.h"
#include "DatPicObj.h"
#include "DatCoordMeth.h"
#include "DatCoord.h"
#include "DatCam.h"
#include "DatObjDetect.h"
#include "DatMapping.h"
#include "DatGUI.h"

//#define DEVICE_STANDARD 0
// Positionen der Messwerte des Lagebestimmungsmoduls
#define POS_HOEHE 0
#define POS_D2 1
#define POS_KOMPASS 2
#define POS_DISTANZ 3
#define POS_X 4
#define POS_Z 5
#define ANZ_MESSWERTE 6

#define SCHWELLWERT_WINKEL_MAGNETOMETER 5

#define COM_PORT 3

#define KLEINER_NULL(input) (input < 0)

#define DATEI_MESSWERTE "../../messwerteCore.txt"

using namespace cv;
using namespace std;

int main(){
	 // subtrahend < 0 = Richtung nicht gesetzt
	InLoc_Richtung richtung;
	//InLoc_ReadCom lese_lagemodul;
	int messdaten[ANZ_MESSWERTE];
	float faktor_musterabstand = 1;
	int eingabe_ganzzahl = 0;


	DatCoordPoint aktuelle_Position;
	DatCoordPoint vorherige_Position;
	double speed = 0;
	double track = 0;
	DatCoordPoints BildObjekte;
	DatCoordPoints BildObjekte_alt;
	DatCoordPoints WeltBild;
	DatCoord<int> Bildmitte;
	DatCam cam;
	//DatObjDetect detect("G:\\studium\\Bachelorarbeit\\InLoc\\InLoc_Core\\Debug\\haarcascade.xml");
	DatObjDetect detect("haarcascade.xml");
	//DatObjDetect detect("haarcascadeNEU.xml");
	cv::Mat img;
	cv::Point bildmittelpunkt;
	DatGUI gui;
	
	/*
	fstream f_messwerte;
	f_messwerte.open(DATEI_MESSWERTE, ios::out);
	f_messwerte << "x,y" << endl;
	f_messwerte.close();

	// ################## Benutzereingaben ######################################################################################
	cout << "Abstand der Muster in cm angeben: ";
	cin >> eingabe_ganzzahl;
	faktor_musterabstand = 1 / (float)eingabe_ganzzahl;
	cout << "Ermittelte Werte in cm werden mit " << faktor_musterabstand << " multipliziert" << endl;
	system("pause");
	*/
	/*faktor_musterabstand = 1 / 6.5;*/
	// ################## Time ##################################################################################################

	clock_t start, end, start_t_speed, end_t_speed;
	double diff, diff_s;

	//cam.setInputVid("vid_1.avi");
	cam.setDevice(0);

	if(!cam.getCapture(img))
	{
		cout << "Fehler: Bilddaten konnten nicht gelesen werden (Kamera nicht angeschlossen?)" << endl;
		system("pause");
		return 0;
	}

	detect.detectObjects(img, BildObjekte);

	WeltBild = DatMapping::DatMappingInit( BildObjekte, Bildmitte );

	if(WeltBild.getCntPicObj() > 2){
		aktuelle_Position = DatCoordMeth::calcCurrentPosition(WeltBild, Bildmitte);
	}


	BildObjekte_alt = BildObjekte;
	BildObjekte.clear();


	// ################## Programmschleife solane Bilddaten vorhanden ###########################################################
	while(cam.getCapture(img) ){
	
		start = clock();

		// ################## Bildmittelpunkt bestimmen #########################################################################
		bildmittelpunkt.x = img.cols/2;
		bildmittelpunkt.y = img.rows/2;
		Bildmitte = DatCoord<int>(bildmittelpunkt.x, bildmittelpunkt.y);


		// ################## Objekte erkennen und speichern ####################################################################	
		detect.detectObjects(img, BildObjekte);

		// ################## Messwerte des Lagemoduls holen ####################################################################

		//lese_lagemodul.getValues(messdaten, ANZ_MESSWERTE);

		// d2 an Maßstab des Koordinatensystems anpassen
		//messdaten[POS_D2] = messdaten[POS_D2] * faktor_musterabstand;

		// Magnetometer arbeitet schon ab etwa 5 grad Neigung nichtmehr richtig
		/*
		if( (abs(messdaten[POS_X]) < SCHWELLWERT_WINKEL_MAGNETOMETER) && (abs(messdaten[POS_Z]) < SCHWELLWERT_WINKEL_MAGNETOMETER))
		{
			richtung.setSchreibschutz(false);
		}
		else
		{
			richtung.setSchreibschutz(true);
		}

		richtung.setKompass(messdaten[POS_KOMPASS]);

		cout << "+++++++++++++++ KOMPASS: " << richtung.getKompass() << endl;
		cout << "+++++++++++++++ SUBTRAHEND: " << richtung.getSubtrahend() << endl;
		cout << "+++++++++++++++ RICHTUNG: " << richtung.getRichtung() << endl;
		*/


		// ################## Objekte mappen ####################################################################################	
		if(BildObjekte.getCntPicObj() > 0){

			int schwellwert_dist = BildObjekte.getCoordAt(0).getPixelCoord().getWidth() / 2.5;
			WeltBild = DatMapping::DatMappingUpdate( BildObjekte, BildObjekte_alt, Bildmitte, schwellwert_dist, richtung );// /2.2
		}
		
		if(WeltBild.getCntPicObj() > 2 ){
			aktuelle_Position = DatCoordMeth::calcCurrentPosition(WeltBild, Bildmitte);
		}

		// ################## Messdaten auf aktuelle_Position anwenden ##########################################################
		
		// Quadrant des Systems bestimmen
		/*
		int x_lagemodul = messdaten[POS_X];
		int z_lagemodul = messdaten[POS_Z];

		int winkel_omega_system = 0;
		int winkel_omega_welt = 0;

		double x_gemessen = messdaten[POS_X];
		double z_gemessen = messdaten[POS_Z];
		double x_komponente_d2_system = 0;
		double z_komponente_d2_system = 0;
		double x_komponente_d2_welt = 0;
		double z_komponente_d2_welt = 0;
		int winkel_d2;//=atan(z_komponente_d2_system / x_komponente_d2_system) * 180 / M_PI;

		aktuelle_Position.setWorldZ(messdaten[POS_HOEHE]);

		if(messdaten[POS_X] != 0)
		{
			//x_komponente_d2_system = abs(tan(x_gemessen / 180 * M_PI) * messdaten[POS_HOEHE]);
			x_komponente_d2_system = abs(tan(z_gemessen / 180 * M_PI) * messdaten[POS_HOEHE]);
			//x_komponente_d2_system = abs(tan(x_gemessen / 180 * M_PI) * messdaten[POS_DISTANZ]);
			x_komponente_d2_welt = x_komponente_d2_system * faktor_musterabstand;
			cout << ":::::::::::::::: " << x_komponente_d2_welt << endl;
		}

		if(messdaten[POS_Z] != 0)
		{
			//z_komponente_d2_system = abs(tan(z_gemessen / 180 * M_PI) * messdaten[POS_HOEHE]);
			z_komponente_d2_system = abs(tan(x_gemessen / 180 * M_PI) * messdaten[POS_HOEHE]);
			//z_komponente_d2_system = abs(tan(z_gemessen / 180 * M_PI) * messdaten[POS_DISTANZ]);
			z_komponente_d2_welt = z_komponente_d2_system * faktor_musterabstand;
			cout << ":::::::::::::::: " << z_komponente_d2_welt << endl;
		}

		// ||||||||||||||||||||||||||||||| TEMP. WORKAROUND ||||||||||||||||||||||||||||||||||||
		//int tmp = x_komponente_d2_welt;
		//x_komponente_d2_welt = z_komponente_d2_welt;
		//z_komponente_d2_welt = tmp;
		// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

		// 1 default wen beide Winkel 0
		int quadrant = 1;

		if( !KLEINER_NULL(x_lagemodul) && KLEINER_NULL(z_lagemodul) )
		{
			quadrant = 1;
			winkel_d2 = 90 - winkel_d2;
		}
		if( KLEINER_NULL(x_lagemodul) && KLEINER_NULL(z_lagemodul) )
		{
			quadrant = 2;
		}
		else if( KLEINER_NULL(x_lagemodul) && !KLEINER_NULL(z_lagemodul) )
		{
			quadrant = 3;
			winkel_d2 = 90 - winkel_d2;
		}
		else if( !KLEINER_NULL(x_lagemodul) && !KLEINER_NULL(z_lagemodul) )
		{
			quadrant = 4;	
		}

		//winkel_omega_system = (quadrant - 1) * 90 + winkel_d2;
		//winkel_omega_welt = richtung.getAuslenkung() + winkel_omega_system;

		//if(winkel_omega_welt <= 90)
		//{
		//	aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() - x_komponente_d2_welt);
		//	aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() - z_komponente_d2_welt);
		//}
		//else if(winkel_omega_welt <= 180)
		//{
		//	aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() - x_komponente_d2_welt);
		//	aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() + z_komponente_d2_welt);
		//}
		//else if(winkel_omega_welt <= 270)
		//{
		//	aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() + x_komponente_d2_welt);
		//	aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() - z_komponente_d2_welt);
		//}
		//else
		//{
		//	aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() + x_komponente_d2_welt);
		//	aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() + z_komponente_d2_welt);
		//}

		if( quadrant == 1 )
		{
			aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() - x_komponente_d2_welt);
			cout << "WorldYalt = " << aktuelle_Position.getWorldY() << endl;
			cout << "z_komponente: " << z_komponente_d2_welt << endl;
			aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() - z_komponente_d2_welt);
			cout << "WorldYneu = " << aktuelle_Position.getWorldY() << endl;
		}
		if( quadrant == 2 )
		{
			aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() - x_komponente_d2_welt);
			aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() + z_komponente_d2_welt);
		}
		else if( quadrant == 3 )
		{
			aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() + x_komponente_d2_welt);
			aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() + z_komponente_d2_welt);
		}
		else if( quadrant == 4 )
		{
			aktuelle_Position.setWorldX(aktuelle_Position.getWorldX() + x_komponente_d2_welt);
			aktuelle_Position.setWorldY(aktuelle_Position.getWorldY() - z_komponente_d2_welt);
		}

		// ################## Messwerte zur Genauigkeitsmessung speichern #######################################################
		if(kbhit())
		{
			getch(); // Zeichenpuffer leeren
			f_messwerte.open(DATEI_MESSWERTE, ios::app);
			f_messwerte << aktuelle_Position.getWorldX() << "," << aktuelle_Position.getWorldY() << endl;
			f_messwerte.close();
		}
		*/

		// ################## Grafische Darstellung #############################################################################
		end_t_speed = clock();
		if(vorherige_Position.isWorldSet()){
			diff_s = (end_t_speed - start_t_speed) / double(CLOCKS_PER_SEC);
			track = (aktuelle_Position.getWorldCoord() - vorherige_Position.getWorldCoord()).getVecLen();
			//if(track > 0.1){
			//	cout << "#############################" << endl;
				speed = track  / diff_s;
				speed = abs(speed);
			//}else{
			//	speed = 0;
			//}
			cout << "END: " << end_t_speed << " -- START: " << start_t_speed << endl << "Track: " << track << " -- Speed: " << speed << endl << "diff_s: " << diff_s << endl;
			cout << "x: " << aktuelle_Position.getWorldX() << " -- y: " << aktuelle_Position.getWorldY() << endl;
		}
		
		gui.update(img, aktuelle_Position, WeltBild, BildObjekte, speed);

		end = clock();
		diff = (end - start);
		diff /= CLOCKS_PER_SEC;
		cout << "ellapsed seconds: " << diff << endl;
		BildObjekte_alt = BildObjekte;
		BildObjekte.clear();

		vorherige_Position = aktuelle_Position;

		start_t_speed = clock();
	}

// ##########################################################################################################################
// ##########################################################################################################################
// ##########################################################################################################################
	
	system("pause");
	return 0;
}





