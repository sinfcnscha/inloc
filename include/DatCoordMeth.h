// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordMeth.h #####################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, Philip Gassner,
//	Stand: 07.01.2011
//
//
//

#pragma once

#if !defined(DATCOORDMETH_H)

#define DATCOORDMETH_H
#include "DatCoord.h"
#include <vector>
#include "DatPicObjects.h"
#include "DatCoordPoints.h"
#include "DatLinearEquation.h"

#include "InLoc_Richtung.h"

#include <math.h>
#include <vector>

#include <iostream>
#include <stdlib.h>

using namespace std;

//// ####### Richtungswerte ###################################################################################################
//#define RICHTUNG_VOR 0
//#define RICHTUNG_RUECK 1
//#define RICHTUNG_LINKS 2
//#define RICHTUNG_RECHTS 3


class DatCoordMeth
{
public:
	DatCoordMeth(void);
	~DatCoordMeth(void);

	// ##########################################################################################################################
	// ######## Berechnet die Entfernung zweier Punkte in 2D		#############################################################
	// ##########################################################################################################################
	static double calcVecLen( DatCoord<double> p1, DatCoord<double> p2);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt ob ein Punkt über, unter, oder neben einem Referenzpunkt ist in 2D ####################################
	// ##########################################################################################################################
	//
	// Rückgabewerte:
	// <0	 darunter
	// 0	 daneben
	// >0	 darüber
	static int getTier( DatCoord<int> &p_reference, DatCoord<int> &point);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt ob ein Punkt rechts, links oder über/unter zu eiem Refernzpunkt ist ins 2D ############################
	// ##########################################################################################################################
	//
	// Rückgabewerte:
	// <0	 rechts
	// 0	 über/unter
	// >0	 links
	static int getSide(  DatCoord<int> &p_reference, DatCoord<int> &point);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt welcher Punkt im gegeben Vektor am nähesten zu Referenzpunkt ist in 2D ################################
	// ##########################################################################################################################
	//
	// ALLGEMEINE VORBEDINGUNG: input DatCoordPoints nicht leer
	
	// ermittelt Punkte anhand von Pixelkoordinaten
	static int determineNearest( DatCoord<int> &p_reference, DatCoordPoints &points);
	static int determineNearestLeft( int pos, DatCoordPoints &points);
	static int determineNearestRight( int pos, DatCoordPoints &points);
	static int determineNearestAbove( int pos, DatCoordPoints &points);
	static int determineNearestBelow( int pos, DatCoordPoints &points);

	// ermittelt Punkte anhand von Weltkoordinaten
	static int determineNearestLeftWorld( DatCoordPoint &p_reference, DatCoordPoints &points);
	static int determineNearestRightWorld( DatCoordPoint &p_reference, DatCoordPoints &points);
	static int determineNearestAboveWorld( DatCoordPoint &p_reference, DatCoordPoints &points);
	static int determineNearestBelowWorld( DatCoordPoint &p_reference, DatCoordPoints &points);
	// *************************************************************************************************************************
	
	// ##########################################################################################################################
	// ######## Ermittelt den Punkt welcher sich Neben dem Referenzpunkt auf Seiten der Bildmitte befindet ######################
	// ################################### INITIALISIERUNGSVERSION ##############################################################
	// ##########################################################################################################################
	// Beschreibung:
	// ## VORSICHT ##
	// diese Version ist nur zur initialisierung geeignet 
	// da nur darüber/darunter bzw. daneben im 45°-Bereich
	// herangezogen werden ohne Geradengleichungen parallel
	// zur X/Y-Achse
	// ##############
	//	Ermittelt horizontalen Nachbar
	//	horizontal bezieht sich also auf das Bild
	//Eingabewerte:
	//	DatCoord<int> Bildmitte:		Koordinate des Bildmittelpunktes
	//	int bezugspunkt:				Position des Referenzpunktes (Punkt der sich am nähesten des am Bildmittelpunkt befindet)
	//	DatCoordPoints &points:			die detektierten Punkte
	// Ausgabe:
	//	int -> Position des zur Berechnung notwendigen vertikalen (aufs Bild bezogen) Nachbar des Referenzpunktes
	// --------------------------------------------------------------------------------------------------------------------------
	static int determineNearestHorizontal( DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt den Punkt welcher sich Neben dem Referenzpunkt auf Seiten der Bildmitte befindet ######################
	// ##########################################################################################################################
	// Beschreibung:
	//	Ermittelt abhängig von der Richtung vertikalen oder horizontalen Nachbar
	//	horizontal bezieht sich also auf das Bild
	//Eingabewerte:
	//	DatLinearEquation vertikale:	Geradengleichung von Referenzpunkt zu direkten seitlichen 
	//									(oder alternativ auf gleicher Ebene beifindlichen) Nachbar
	//	DatCoord<int> Bildmitte:		Koordinate des Bildmittelpunktes
	//	int bezugspunkt:				Position des Referenzpunktes (Punkt der sich am nähesten des am Bildmittelpunkt befindet)
	//	DatCoordPoints &points:			die detektierten Punkte
	//	int richtung:					aktuelle Bewegungsrichtung (Werte siehe Defintes oben unter Richtungswerte)
	// Ausgabe:
	//	int -> Position des zur Berechnung notwendigen vertikalen (aufs Bild bezogen) Nachbar des Referenzpunktes
	// --------------------------------------------------------------------------------------------------------------------------
	static int determineNearestHorizontal( DatLinearEquation vertikale, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung);
	// **************************************************************************************************************************
	
	// ##########################################################################################################################
	// ######## Ermittelt den Punkt welcher sich Neben dem Referenzpunkt auf Seiten der Bildmitte befindet ######################
	// ################################### INITIALISIERUNGSVERSION ##############################################################
	// ##########################################################################################################################
	// Beschreibung:
	// ## VORSICHT ##
	// diese Version ist nur zur initialisierung geeignet 
	// da nur darüber/darunter bzw. daneben im 45°-Bereich
	// herangezogen werden ohne Geradengleichungen parallel
	// zur X/Y-Achse
	// ##############
	//	Ermittelt den vertikalen Nachbar
	//	vertikal bezieht sich also auf das Bild
	//Eingabewerte:
	//	DatCoord<int> Bildmitte:		Koordinate des Bildmittelpunktes
	//	int bezugspunkt:				Position des Referenzpunktes (Punkt der sich am nähesten des am Bildmittelpunkt befindet)
	//	DatCoordPoints &points:			die detektierten Punkte
	// Ausgabe:
	//	int -> Position des zur Berechnung notwendigen vertikalen (aufs Bild bezogen) Nachbar des Referenzpunktes
	// --------------------------------------------------------------------------------------------------------------------------
	static int determineNearestVertical( DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt den Punkt welcher sich über/unter dem Referenzpunkt auf "Seiten" der Bildmitte befindet ###############
	// ##########################################################################################################################
	//
	// Beschreibung:
	//	Ermittelt abhängig von der Richtung vertikalen oder horizontalen Nachbar
	//	vertikal bezieht sich also auf das Bild
	//Eingabewerte:
	//	DatLinearEquation horizontale:	Geradengleichung von Referenzpunkt zu unterem oder oberen direkten Nachbar
	//	DatCoord<int>					Bildmitte: Koordinate des Bildmittelpunktes
	//	int bezugspunkt:				Position des Referenzpunktes (Punkt der sich am nähesten des am Bildmittelpunkt befindet)
	//	DatCoordPoints &points:			die detektierten Punkte
	//	int richtung:					aktuelle Bewegungsrichtung (Werte siehe Defines oben unter Richtungswerte)
	// Ausgabe:
	//	int -> Position des zur Berechnung notwendigen vertikalen (aufs Bild bezogen) Nachbar des Referenzpunktes
	// --------------------------------------------------------------------------------------------------------------------------
	static int determineNearestVertical( DatLinearEquation horizontale, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Mapped den Punkt welcher sich neben dem Referenzpunkt auf Seiten der Bildmitte befindet #########################
	// ##########################################################################################################################
	//
	// Beschreibung:
	//		Ermittelt den zur Positionsbestimmung erforderlichen horizontalen Punkt und hängt in an DatCoordPoints &erg an
	// Eingabewerte:
	//		DatCoordPoints &erg:		Ergebnis wird hier angehängt
	//		DatCoord<int> Bildmitte:	Pixelkoordinate des Bildmittelpunktes
	//		int bezugspunkt:			Position in points des Punktes welcher sich am nähesten am Bildmittelpunkt befindet
	//		DatCoordPoints &points:		Alle erkannten Punkte
	//		int richtung:				Bewegungsrichtung (Werte siehe Defines oben unter Richtungswerte)
	// --------------------------------------------------------------------------------------------------------------------------
	static void determineHorizontal( DatCoordPoints &erg, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung);
	// **************************************************************************************************************************
	
	// ##########################################################################################################################
	// ######## Mapped den Punkt welcher sich über/unter dem Referenzpunkt auf "Seiten" der Bildmitte befindet ##################
	// ##########################################################################################################################	
	//
	// Beschreibung:
	//		Ermittelt den zur Positionsbestimmung erforderlichen vertikalen Punkt und hängt in an DatCoordPoints &erg an
	//		DatCoordPoints &erg:		Ergebnis wird hier angehängt
	//		DatCoord<int> Bildmitte:	Pixelkoordinate des Bildmittelpunktes
	//		int bezugspunkt:			Position in points des Punktes welcher sich am nähesten am Bildmittelpunkt befindet
	//		DatCoordPoints &points:		Alle erkannten Punkte
	//		int richtung:				Bewegungsrichtung (Werte siehe Defines oben unter Richtungswerte)
	// --------------------------------------------------------------------------------------------------------------------------
	static void determineVertikal( DatCoordPoints &erg, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt Bildrichtung ##########################################################################################
	// ##########################################################################################################################
	//
	// Beschreibung:
	//		Ermittelt aktuelle Bewegungsrichtung
	// Eingabewerte:
	//		DatCoordPoint p_mitte:		aktueller Referenzpunkt (Punkt der sich am nähesten an der Bildmitte befindet)
	//		DatCoordPoint p_compare:	ein direkter Nachbar des "Referenzpunktes" p_mitte
	// Rückgabewerte:
	//		int -> Richtung siehe Defines oben unter Richtungswerte
	// --------------------------------------------------------------------------------------------------------------------------
	static int determineDirection( DatCoordPoint p_mitte, DatCoordPoint p_compare);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Ermittelt aktuelle Position des Bildmittelpunkts ################################################################
	// ##########################################################################################################################
	//
	// Beschreibung:
	//		Erechnet die aktuelle Position des Bildmittelpunktes in der Welt
	// Eingabewerte:
	//		DatCoordPoints &points:		zur Berechnung notwendiger Mittelpunkt, Horizontaler Punkt und Vertikaler Punkt
	//		DatCoord<int> &Bildmitte:	Pixelkoordinate des Bildmittelpunktes
	// Rückgabewerte:
	//		DatCoordPoint -> Koordinatenobjekt der aktuellen Position
	// --------------------------------------------------------------------------------------------------------------------------
	static DatCoordPoint calcCurrentPosition(DatCoordPoints &points, DatCoord<int> &Bildmitte);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## sortiert doppelte Punkte aus ####################################################################################
	// ##########################################################################################################################
	//
	// Beschreibung:
	//		Entfernt doppelt erkannte Objekte
	// Eingabewerte:
	//		DatCoordPoints &input: zu filternde Objektsammlung
	// --------------------------------------------------------------------------------------------------------------------------
	static void filterDuplicates( DatCoordPoints &input);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Prüft ob Objekt mehrfach detektiert #############################################################################
	// ##########################################################################################################################
	//
	// Beschreibung:
	//		Überprüft ob zwei erkannte Objekte sich überschneiden und folglich als doppelt angesehen werden können
	// Eingabewerte:
	//		DatCoord<int> obj1: Pixelkoordinate
	//		DatCoord<int> obj2: Pixelkoordinate
	// Rückgabewerte:
	//		bool -> true falls Objektüberschneidung
	//		bool -> false falls keine Objektüberschneidung
	// --------------------------------------------------------------------------------------------------------------------------
	static bool isInObj(DatCoord<int> obj1, DatCoord<int> obj2);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## Prüft ob detektierte schon im vorherigen Bild gemapped ##########################################################
	// ##########################################################################################################################
	//
	// Eingabewerte:
	//		DatCoordPoints &old_points: Punkte die im vorangegangenen Mapping ermittelt wurden
	//		DatCoordPoints &new_points: Punkte die im aktuellen Mapping ermittelt wurden
	//		int SCHWELLWERT_DIST:		maximale Distanz welche sich der alte Punkt im Bild bewegt haben darf um identifiziert zu werden
	// --------------------------------------------------------------------------------------------------------------------------
	static void updateKnownPoints(DatCoordPoints &old_points, DatCoordPoints &new_points, int SCHWELLWERT_DIST);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## sortiert die übergebenen Positionen nach Abstand zum Referenzpunkt ##############################################
	// ##########################################################################################################################
	//
	//Eingabewerte:
	//		DatCoord<int> &positionen:		Vektor mit den Positionen in der Datenstruktur/Klasse DatPicObjects der Objekte die betrachtet werden
	//		DatCoordPoints &points:			Alle gefundenen Objekte im Bild
	//		DatCoordPoints &p_reference:	Bezugspunkt
	// --------------------------------------------------------------------------------------------------------------------------
	static void sortCoordByDistance( DatCoord<int> &p_reference, DatCoordPoints &points, vector<int> &positionen);
	// **************************************************************************************************************************

	// ##########################################################################################################################
	// ######## sortiert die übergebenen Positionen #############################################################################
	// ##########################################################################################################################
	//
	// --------------------------------------------------------------------------------------------------------------------------
	static void quickSort( vector<int> &positionen, int first, int last);
	// **************************************************************************************************************************

};

#endif
