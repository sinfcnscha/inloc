// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordMeth.cpp ###################################################################
// ##########################################################################################################################
//	Autoren: Christian Schauer, Philip Gassner,
//	Stand: 23.01.2013
//
//
//
#include "DatCoordMeth.h"


using namespace std;

DatCoordMeth::DatCoordMeth(void)
{
}


DatCoordMeth::~DatCoordMeth(void)
{
}

// ##########################################################################################################################
// ######## calcVecLen ######################################################################################################
// ##########################################################################################################################
double DatCoordMeth::calcVecLen( DatCoord<double> p1, DatCoord<double> p2){
	DatCoord<double> p_erg = p2 - p1;
	return sqrt(pow(p_erg.getX(), 2.) + pow(p_erg.getY(), 2.));
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## calcCompareDistance #############################################################################################
// ##########################################################################################################################
// zur Bestimmung ob ein Punkt näher ist als ein anderer
static int calcCompareDistance( DatCoord<int> p1, DatCoord<int> p2){
	DatCoord<int> tmp_coord = abs(p1 - p2);
	return tmp_coord.getVecLen();
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## getTier #########################################################################################################
// ##########################################################################################################################
//
// Rückgabewerte:
// <0	 darunter
// 0	 daneben
// >0	 darüber
int  DatCoordMeth::getTier( DatCoord<int> &p_reference, DatCoord<int> &point){
	return p_reference.getY() - point.getY();
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## getSide #########################################################################################################
// ##########################################################################################################################
//
// Rückgabewerte:
// <0	 rechts
// 0	 über/unter
// >0	 links
int  DatCoordMeth::getSide( DatCoord<int> &p_reference, DatCoord<int> &point){
	return p_reference.getX() - point.getX();
}
// **************************************************************************************************************************



// ##########################################################################################################################
// ######## determineNearest<int> ###########################################################################################
// ##########################################################################################################################

int DatCoordMeth::determineNearest( DatCoord<int> &p_reference, DatCoordPoints &points){

	// Erstes Objekt als Startwert für die Ermittlung des Punktes welcher sich am nähesten am Punkt p_center befindet
	DatCoord<int> tmp_coord = abs(p_reference - points.getCoordAt(0).getPixelCoord() );
	int dist = tmp_coord.getVecLen();
	int dis_tmp;
	int i_posErg = 0;
	int i = 0;

	for(i = 1; i < points.getCntPicObj(); i++){
		tmp_coord = abs(p_reference - points.getCoordAt(i).getPixelCoord());
		dis_tmp = tmp_coord.getVecLen();

		// Wenn Punkt näher
		if( dis_tmp < dist){
			dist = dis_tmp;
			i_posErg = i;
		}
	};
	return i_posErg;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestLeft ############################################################################################
// ##########################################################################################################################
int DatCoordMeth::determineNearestLeft( int pos, DatCoordPoints &points){
	unsigned int i;
	int retPosition;
	int betrag;
	int tempBetrag;
	int diff_xy;
	DatCoord<int> tmpVec;
	vector<int> linksPositionen;

	DatCoord<int> vect;

	// zuerst alle linken Elemente finden
	for(i = 0; i < points.getCntPicObj(); i++){
		if( i != pos){

			// wenn links
			if(  DatCoordMeth::getSide(points.getCoordAt(pos).getPixelCoord(), points.getCoordAt(i).getPixelCoord()) > 0){
				// wenn winkel kleiner 45
				tmpVec = points.getCoordAt(pos).getPixelCoord() - points.getCoordAt(i).getPixelCoord();

				diff_xy = abs(tmpVec.getX()) - abs(tmpVec.getY());

				if( diff_xy > 0){
					linksPositionen.push_back(i);
				}
			}
		}
	}

	// Wenn keine Objekte links Return -1
	if(linksPositionen.empty()){
		return -1;
	}else{
		// Das ersete Element zum initialisieren verwenden
		vect = abs(points.getCoordAt(linksPositionen[0]).getPixelCoord()-points.getCoordAt(pos).getPixelCoord());
		betrag = vect.getVecLen();
		retPosition = linksPositionen[0];

		// 1 da Element 0 eben zum initialisieren verwendet wurde
		for(i = 1; i < linksPositionen.size(); i++){

			vect = abs( points.getCoordAt(linksPositionen[i]).getPixelCoord()  -points.getCoordAt(pos).getPixelCoord() );
			tempBetrag = vect.getVecLen();

			if(tempBetrag < betrag){
				betrag = tempBetrag;
				retPosition = linksPositionen[i];
			}
		}
		return retPosition;
	}


}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestRight ###########################################################################################
// ##########################################################################################################################
int DatCoordMeth::determineNearestRight( int pos, DatCoordPoints &points){
	unsigned int i;
	int retPosition;
	int betrag;
	int tempBetrag;
	int diff_xy;
	DatCoord<int> tmpVec;
	vector<int> rechtsPositionen;

	DatCoord<int> vect;

	// zuerst alle linken Elemente finden
	for(i = 0; i < points.getCntPicObj(); i++){
		if( i != pos){
			// wenn links
			if(  DatCoordMeth::getSide(points.getCoordAt(pos).getPixelCoord(), points.getCoordAt(i).getPixelCoord()) < 0){
				// wenn winkel kleiner 45
				tmpVec = points.getCoordAt(pos).getPixelCoord() - points.getCoordAt(i).getPixelCoord();

				diff_xy = abs(tmpVec.getX()) - abs(tmpVec.getY());

				if( diff_xy > 0){
					rechtsPositionen.push_back(i);
				}
			}
		}
	}

	// Wenn keine Objekte links Return -1
	if(rechtsPositionen.size() <= 0){
		return -1;
	}else{
		// Das ersete Element zum initialisieren verwenden
		vect = abs(points.getCoordAt(rechtsPositionen[0]).getPixelCoord() - points.getCoordAt(pos).getPixelCoord());
		betrag = vect.getVecLen();
		retPosition = rechtsPositionen[0];

		// 1 da Element 0 eben zum initialisieren verwendet wurde
		for(i = 1; i < rechtsPositionen.size(); i++){

			vect = abs( points.getCoordAt(rechtsPositionen[i]).getPixelCoord()  - points.getCoordAt(pos).getPixelCoord() );
			tempBetrag = vect.getVecLen();

			if(tempBetrag < betrag){
				betrag = tempBetrag;
				retPosition = rechtsPositionen[i];
			}
		}
		return retPosition;
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestAbove ###########################################################################################
// ##########################################################################################################################
int DatCoordMeth::determineNearestAbove( int pos, DatCoordPoints &points)
{
	unsigned int i;
	int retPosition;
	int betrag = 0;
	int tempBetrag;
	int diff_xy;
	DatCoord<int> tmpVec;
	vector<int> obenPositionen;
	DatCoord<int> vect;

	// zuerst alle oberen Elemente finden
	for(i = 0; i < points.getCntPicObj(); i++)
	{
		if( i != pos)
		{
			if( (points.getCoordAt(pos).getPixelCoord().getY() - points.getCoordAt(i).getPixelCoord().getY()) >= 0) //wenn größer 0 dann oben
			{

				// wenn winkel kleiner 45
				tmpVec = points.getCoordAt(pos).getPixelCoord() - points.getCoordAt(i).getPixelCoord();

				diff_xy = abs(tmpVec.getY()) - abs(tmpVec.getX());

				if( diff_xy > 0){
					obenPositionen.push_back(i);;
				}
			}
		}
	}
	// Wenn keine Objekte links Return -1
	if(obenPositionen.size() <= 0){
		return -1;
	}else{
		// Das ersete Element zum initialisieren verwenden
		vect = abs(points.getCoordAt(obenPositionen[0]).getPixelCoord() - points.getCoordAt(pos).getPixelCoord());
		betrag = vect.getVecLen();
		retPosition = obenPositionen[0];

		// 1 da Element 0 eben zum initialisieren verwendet wurde
		for(i = 1; i < obenPositionen.size(); i++){

			vect = abs( points.getCoordAt(obenPositionen[i]).getPixelCoord()  - points.getCoordAt(pos).getPixelCoord() );
			tempBetrag = vect.getVecLen();

			if(tempBetrag < betrag){
				betrag = tempBetrag;
				retPosition = obenPositionen[i];
			}
		}
		return retPosition;
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestBelow ###########################################################################################
// ##########################################################################################################################
int DatCoordMeth::determineNearestBelow( int pos, DatCoordPoints &points)
{
	unsigned int i;
	int retPosition;
	int betrag = 0;
	int tempBetrag;
	int diff_xy;
	DatCoord<int> tmpVec;
	vector<int> untenPositionen;
	DatCoord<int> vect;

	// zuerst alle oberen Elemente finden
	for(i = 0; i < points.getCntPicObj(); i++)
	{
		if( i != pos)
		{
			if( (points.getCoordAt(pos).getPixelCoord().getY() - points.getCoordAt(i).getPixelCoord().getY()) <= 0) //wenn kleiner 0 dann unten
			{

				// wenn winkel kleiner 45
				tmpVec = points.getCoordAt(pos).getPixelCoord() - points.getCoordAt(i).getPixelCoord();

				diff_xy = abs(tmpVec.getY()) - abs(tmpVec.getX());

				if( diff_xy > 0){
					untenPositionen.push_back(i);;
				}
			}
		}
	}
	// Wenn keine Objekte links Return -1
	if(untenPositionen.size() <= 0){
		return -1;
	}else{
		// Das ersete Element zum initialisieren verwenden
		vect = abs(points.getCoordAt(untenPositionen[0]).getPixelCoord() - points.getCoordAt(pos).getPixelCoord());
		betrag = vect.getVecLen();
		retPosition = untenPositionen[0];

		// 1 da Element 0 eben zum initialisieren verwendet wurde
		for(i = 1; i < untenPositionen.size(); i++){

			vect = abs( points.getCoordAt(untenPositionen[i]).getPixelCoord()  - points.getCoordAt(pos).getPixelCoord() );
			tempBetrag = vect.getVecLen();

			if(tempBetrag < betrag){
				betrag = tempBetrag;
				retPosition = untenPositionen[i];
			}
		}
		return retPosition;
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestHorizontal ######################################################################################
// ##########################################################################################################################
//
// es muss das Objekt auf seiten des Bildmittelpunktes gefunden werden

int DatCoordMeth::determineNearestHorizontal( DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points){
	int links = determineNearestLeft( bezugspunkt , points);
	int rechts = determineNearestRight(bezugspunkt, points);

	double x_rechts = points.getCoordAt(bezugspunkt).getWorldX() + 1;
	double x_links = points.getCoordAt(bezugspunkt).getWorldX() - 1;

	if( (links < 0) && (rechts < 0)){
		return -1;
	}

	if(links < 0){
		points.setWorldObjectAt(rechts,  x_rechts, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
		return rechts;
	}
	if(rechts < 0){
		points.setWorldObjectAt(links, x_links, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
		return links;
	}

	DatCoord<int> mitte_links = abs(points.getCoordAt(links).getPixelCoord() - Bildmitte);
	DatCoord<int> mitte_rechts = abs(points.getCoordAt(rechts).getPixelCoord() - Bildmitte);
	if( mitte_links.getVecLen() < mitte_rechts.getVecLen()){
		points.setWorldObjectAt(links, x_links, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
		return links;
	}else{
		points.setWorldObjectAt(rechts, x_rechts, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
		return rechts;
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestHorizontal 2 ####################################################################################
// ##########################################################################################################################
//
// es muss das Objekt auf seiten des Bildmittelpunktes gefunden werden

int DatCoordMeth::determineNearestHorizontal( DatLinearEquation vertikale, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung){
	int links = determineNearestLeft( bezugspunkt , points);
	int rechts = determineNearestRight(bezugspunkt, points);
	double x_rechts;
	double x_links;
	double y_rechts;
	double y_links;

	bool is_rechts = false;

	if( (links < 0) && (rechts < 0)){
		return -1;
	}

	// schauen auf welcher Seite Bildmittelpunkt
	if((vertikale.getXfor(Bildmitte.getY()) - Bildmitte.getX()) <= 0){
		is_rechts = true;
	}else{
		is_rechts = false;
	}

	// ------------------- VORSICHT: RICHTUNG --------------------------------------
	//if(richtung == RICHTUNG_VOR){
		x_rechts = points.getCoordAt(bezugspunkt).getWorldX() + 1;
		x_links = points.getCoordAt(bezugspunkt).getWorldX() - 1;
	//}
	/*else*/ if(richtung == RICHTUNG_RUECK){
		x_rechts = points.getCoordAt(bezugspunkt).getWorldX() - 1;
		x_links = points.getCoordAt(bezugspunkt).getWorldX() + 1;
	}
	else if(richtung == RICHTUNG_LINKS){
		y_rechts = points.getCoordAt(bezugspunkt).getWorldY() + 1;
		y_links = points.getCoordAt(bezugspunkt).getWorldY() - 1;
	}
	// (richtung == RICHTUNG_LINKS)
	else{
		y_rechts = points.getCoordAt(bezugspunkt).getWorldY() - 1;
		y_links = points.getCoordAt(bezugspunkt).getWorldY() + 1;
	}
	// .............................................................................

	if( (is_rechts == true) && (rechts < 0)){
		return -1;
	}
	if( (is_rechts == false) && (links < 0)){
		return -1;
	}

	if( (is_rechts == true)){
		points.setWorldObjectAt(rechts,  x_rechts, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
		return rechts;
	}
	if(is_rechts == false){
		points.setWorldObjectAt(links, x_links, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
		return links;
	}

	DatCoord<int> mitte_links = abs(points.getCoordAt(links).getPixelCoord() - Bildmitte);
	DatCoord<int> mitte_rechts = abs(points.getCoordAt(rechts).getPixelCoord() - Bildmitte);

	if((richtung == RICHTUNG_VOR) || (richtung == RICHTUNG_RUECK)){
		if( mitte_links.getVecLen() < mitte_rechts.getVecLen()){
			points.setWorldObjectAt(links, x_links, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
			return links;
		}else{
			points.setWorldObjectAt(rechts, x_rechts, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
			return rechts;
		}
	}
	else{
		if( mitte_links.getVecLen() < mitte_rechts.getVecLen()){
			points.setWorldObjectAt(links, points.getCoordAt(bezugspunkt).getWorldX(), y_links, points.getCoordAt(bezugspunkt).getWorldZ());
			return links;
		}else{
			points.setWorldObjectAt(rechts, points.getCoordAt(bezugspunkt).getWorldX(), y_rechts, points.getCoordAt(bezugspunkt).getWorldZ());
			return rechts;
		}
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestVertikal ########################################################################################
// ##########################################################################################################################
int DatCoordMeth::determineNearestVertical( DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points){
	int oben = determineNearestAbove( bezugspunkt , points);
	int unten = determineNearestBelow(bezugspunkt, points);

	double y_oben = points.getCoordAt(bezugspunkt).getWorldY() + 1;
	double y_unten = points.getCoordAt(bezugspunkt).getWorldY() - 1;

	if( (oben < 0) && (unten < 0)){
		return -1;
	}

	if(oben < 0){
		points.setWorldObjectAt(unten, points.getCoordAt(bezugspunkt).getWorldX(), y_unten, points.getCoordAt(bezugspunkt).getWorldZ());
		return unten;
	}
	if(unten < 0){
		points.setWorldObjectAt(oben, points.getCoordAt(bezugspunkt).getWorldX(), y_oben, points.getCoordAt(bezugspunkt).getWorldZ());
		return oben;
	}

	if( points.getCoordAt(oben).getPixelCoord().getVecLen() < points.getCoordAt(unten).getPixelCoord().getVecLen()){
		points.setWorldObjectAt(oben, points.getCoordAt(bezugspunkt).getWorldX(), y_oben, points.getCoordAt(bezugspunkt).getWorldZ());
		return oben;
	}else{
		points.setWorldObjectAt(unten, points.getCoordAt(bezugspunkt).getWorldX(), y_unten, points.getCoordAt(bezugspunkt).getWorldZ());
		return unten;
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestVertikal 2 ######################################################################################
// ##########################################################################################################################
int DatCoordMeth::determineNearestVertical( DatLinearEquation horizontale, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung){
	int oben = determineNearestAbove( bezugspunkt , points);
	int unten = determineNearestBelow(bezugspunkt, points);

	double y_oben;
	double y_unten;
	double x_oben;
	double x_unten;

	bool is_oben = false;

	//double y_oben = points.getCoordAt(bezugspunkt).getWorldY() + 1;
	//double y_unten = points.getCoordAt(bezugspunkt).getWorldY() - 1;

	// ------------------- VORSICHT: RICHTUNG --------------------------------------
	if(richtung == RICHTUNG_VOR){
		y_oben = points.getCoordAt(bezugspunkt).getWorldY() + 1;
		y_unten = points.getCoordAt(bezugspunkt).getWorldY() - 1;
	}
	else if(richtung == RICHTUNG_RUECK){
		y_oben = points.getCoordAt(bezugspunkt).getWorldY() - 1;
		y_unten = points.getCoordAt(bezugspunkt).getWorldY() + 1;
	}
	else if(richtung == RICHTUNG_LINKS){
		x_oben = points.getCoordAt(bezugspunkt).getWorldX() + 1;
		x_unten = points.getCoordAt(bezugspunkt).getWorldX() - 1;
	}
	// (richtung == RICHTUNG_RECHTS)
	else{
		x_oben = points.getCoordAt(bezugspunkt).getWorldX() - 1;
		x_unten = points.getCoordAt(bezugspunkt).getWorldX() + 1;
	}
	// .............................................................................

	if( (horizontale.getYfor(Bildmitte.getX()) - Bildmitte.getY()) >= 0){
		is_oben = true;
	}else{
		is_oben = false;
	}

	if( (oben < 0) && (unten < 0)){
		return -1;
	}

	if( (is_oben == true) && (oben < 0)){
		return -1;
	}
	if( (is_oben == false) && (unten < 0)){
		return -1;
	}

	if( (richtung == RICHTUNG_VOR) || (richtung == RICHTUNG_RUECK)){
		if(is_oben == false){
			points.setWorldObjectAt(unten, points.getCoordAt(bezugspunkt).getWorldX(), y_unten, points.getCoordAt(bezugspunkt).getWorldZ());
			return unten;
		}
		// if(is_oben == true)
		else /*if(is_oben == true)*/{
			points.setWorldObjectAt(oben, points.getCoordAt(bezugspunkt).getWorldX(), y_oben, points.getCoordAt(bezugspunkt).getWorldZ());
			return oben;
		}
	}else{
		if(is_oben == false){
			points.setWorldObjectAt(unten, x_unten, points.getCoordAt(bezugspunkt).getWorldY(), points.getCoordAt(bezugspunkt).getWorldZ());
			return unten;
		}
		// if(is_oben == true)
		else /*if(is_oben == true)*/{
			points.setWorldObjectAt(oben,x_oben, points.getCoordAt(bezugspunkt).getWorldY(),points.getCoordAt(bezugspunkt).getWorldZ());
			return oben;
		}
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestLeftWorld #######################################################################################
// ##########################################################################################################################
//
int DatCoordMeth::determineNearestLeftWorld( DatCoordPoint &p_reference, DatCoordPoints &points){
	int i = 0;

	for(i = 0; i < points.getCntPicObj(); i++){
		if(points.getCoordAt(i).isWorldSet()){
			if( (points.getWorldXCoordAt(i) == (p_reference.getWorldX() - 1)) && (points.getWorldYCoordAt(i) == p_reference.getWorldY())){
				return i;
			}
		}
	}

	return -1;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestRightWorld ######################################################################################
// ##########################################################################################################################
//
int DatCoordMeth::determineNearestRightWorld( DatCoordPoint &p_reference, DatCoordPoints &points){
	int i = 0;

	for(i = 0; i < points.getCntPicObj(); i++){
		if(points.getCoordAt(i).isWorldSet()){
			if( (points.getWorldXCoordAt(i) == (p_reference.getWorldX() + 1)) && (points.getWorldYCoordAt(i) == p_reference.getWorldY())){
				return i;
			}
		}
	}

	return -1;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestAboveWorld ######################################################################################
// ##########################################################################################################################
//
int DatCoordMeth::determineNearestAboveWorld( DatCoordPoint &p_reference, DatCoordPoints &points){
	int i = 0;

	for(i = 0; i < points.getCntPicObj(); i++){
		if(points.getCoordAt(i).isWorldSet()){
			if( (points.getWorldYCoordAt(i) == (p_reference.getWorldY() + 1)) && (points.getWorldXCoordAt(i) == p_reference.getWorldX())){
				return i;
			}
		}
	}

	return -1;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineNearestBelowWorld ######################################################################################
// ##########################################################################################################################
//
int DatCoordMeth::determineNearestBelowWorld( DatCoordPoint &p_reference, DatCoordPoints &points){
	int i = 0;

	for(i = 0; i < points.getCntPicObj(); i++){
		if(points.getCoordAt(i).isWorldSet()){
			if( (points.getWorldYCoordAt(i) == (p_reference.getWorldY() - 1)) && (points.getWorldXCoordAt(i) == p_reference.getWorldX())){
				return i;
			}
		}
	}

	return -1;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineHorizontal #############################################################################################
// ##########################################################################################################################
//
void DatCoordMeth::determineHorizontal( DatCoordPoints &erg, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung){
	int vert;
	int nachbar = -1;
	bool bildmitte_is_left;

	vert = DatCoordMeth::determineNearestVertical( Bildmitte, bezugspunkt, points);

	if(vert >= 0){
		DatLinearEquation vertikale(points.getCoordAt(vert).getPixelCoord(), points.getCoordAt(bezugspunkt).getPixelCoord());



		// erstmal mit Weltkoordinaten versuchen _______________________________________________________
		if( Bildmitte.getX() < vertikale.getXfor(Bildmitte.getY())){
			bildmitte_is_left = true;
		}else{
			bildmitte_is_left = false;
		}

		if(richtung == RICHTUNG_VOR){
			if(bildmitte_is_left){
				nachbar = determineNearestLeftWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				nachbar = determineNearestRightWorld(points.getCoordAt(bezugspunkt), points);
			}
		}
		else if(richtung == RICHTUNG_RUECK){
			if(!bildmitte_is_left){
				nachbar = determineNearestLeftWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				nachbar = determineNearestRightWorld(points.getCoordAt(bezugspunkt), points);
			}

		}
		else if(richtung == RICHTUNG_RECHTS){
			if(bildmitte_is_left){
				nachbar = determineNearestBelowWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				determineNearestAboveWorld(points.getCoordAt(bezugspunkt), points);
			}
		}
		else if(richtung == RICHTUNG_LINKS){
			if(!bildmitte_is_left){
				nachbar = determineNearestBelowWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				determineNearestAboveWorld(points.getCoordAt(bezugspunkt), points);
			}
		}
		// ---------------------------------------------------------------------------------------------

		if(nachbar < 0){
			//cout << "DatCoordMeth::determineNearestHorizontal( vertikale, Bildmitte, bezugspunkt, points, richtung)" << endl;
			//system("pause");
			nachbar = DatCoordMeth::determineNearestHorizontal( vertikale, Bildmitte, bezugspunkt, points, richtung);
			//if(nachbar >= 0){
			//	cout << endl << points.getCoordAt(nachbar).toString("NACHBAR HORIZONTAL") << endl;
			//}else{
			//	cout << "WARNING: kein horizontaler Nachbar" << endl << endl;
			//}
		}
		// wenn Horizontaler Punkt vorhanden
		if(nachbar >= 0){

			DatCoordPoint tmpObjekt = points.getCoordAt(nachbar);

			erg.addCoord(tmpObjekt);
		}
	}
}

// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineVertikal ###############################################################################################
// ##########################################################################################################################
//
void DatCoordMeth::determineVertikal( DatCoordPoints &erg, DatCoord<int> Bildmitte, int bezugspunkt, DatCoordPoints &points, int richtung){
	int nachbar = -1;
	int posHori = erg.getCntPicObj() - 1;
	bool bildmitte_is_oben;

	//int hori = DatCoordMeth::determineNearestHorizontal( Bildmitte, bezugspunkt, points);
	//if(hori >= 0){
	if(erg.getCntPicObj() > 1){
		DatLinearEquation horizontale( points.getCoordAt(bezugspunkt).getPixelCoord(), erg.getCoordAt(posHori).getPixelCoord()/*points.getCoordAt(hori).getPixelCoord()*/);

		// erstmal mit Weltkoordinaten versuchen _______________________________________________________
		if( Bildmitte.getY() < horizontale.getYfor(Bildmitte.getX())){
			bildmitte_is_oben = true;
		}else{
			bildmitte_is_oben = false;
		}

		if(richtung == RICHTUNG_VOR){
			if(bildmitte_is_oben){
				nachbar = determineNearestAboveWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				nachbar = determineNearestBelowWorld(points.getCoordAt(bezugspunkt), points);
			}
		}
		else if(richtung == RICHTUNG_RUECK){
			if(!bildmitte_is_oben){
				nachbar = determineNearestBelowWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				nachbar = determineNearestAboveWorld(points.getCoordAt(bezugspunkt), points);
			}

		}
		else if( richtung == RICHTUNG_RECHTS){
			if(bildmitte_is_oben){
				nachbar = determineNearestLeftWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				determineNearestRightWorld(points.getCoordAt(bezugspunkt), points);
			}
		}
		else if(richtung == RICHTUNG_LINKS){
			if(!bildmitte_is_oben){
				nachbar = determineNearestRightWorld(points.getCoordAt(bezugspunkt), points);
			}else{
				determineNearestLeftWorld(points.getCoordAt(bezugspunkt), points);
			}
		}
		// ---------------------------------------------------------------------------------------------

		if(nachbar < 0){
			//cout << "DatCoordMeth::determineNearestVertical(horizontale, Bildmitte, bezugspunkt, points, richtung)" << endl;
			//system("pause");
			nachbar = DatCoordMeth::determineNearestVertical(horizontale, Bildmitte, bezugspunkt, points, richtung);
			//if(nachbar >= 0){
			//	cout << endl << points.getCoordAt(nachbar).toString("NACHBAR VERTIKAL") << endl;
			//}else{
			//	cout << "WARNING: kein vertikaler Nachbar" << endl << endl;
			//}
		}
		if(nachbar >= 0){
			DatCoordPoint tmpObjekt = points.getCoordAt(nachbar);
			erg.addCoord(tmpObjekt);
		}
	}
}

// **************************************************************************************************************************

// **************************************************************************************************************************

// ##########################################################################################################################
// ######## determineDirection ##############################################################################################
// ##########################################################################################################################
//
int DatCoordMeth::determineDirection( DatCoordPoint p_mitte, DatCoordPoint p_compare){

	int xm = p_mitte.getWorldX();
	int ym = p_mitte.getWorldY();
	int xc = p_compare.getWorldX();
	int yc = p_compare.getWorldY();

	DatCoord<int> PixelVektor = abs(p_compare.getPixelCoord() - p_mitte.getPixelCoord());

	// --------------------------------------------------------------
	// versuchen 1.#inf zu eliminieren
	if (PixelVektor.getX() == 0)
	{
		PixelVektor.getX() == 1;
	}

	double steigung = double(PixelVektor.getY()) / double(PixelVektor.getX());
	//cout << "SV: y:" <<  double(PixelVektor.getY()) << " || x:" << double(PixelVektor.getX()) << endl;
	//cout << "STEIGUNG: " <<  steigung << endl;
	//cout << "mittle.x = " << p_mitte.getWorldCoord().getX() << "   mitte.y = " << p_mitte.getWorldCoord().getY() << endl;
	//cout << "mittle.x = " << p_mitte.getPixelCoord().getX() << "   mitte.y = " << p_mitte.getPixelCoord().getY() << endl;
	//cout << "compare.x = " << p_compare.getWorldCoord().getX() << "   compare.y = " << p_compare.getWorldCoord().getY() << endl;
	//cout << "compare.x = " << p_compare.getPixelCoord().getX() << "   compare.y = " << p_compare.getPixelCoord().getY() << endl;

	// ermitteln ob daneben oder darüber/darunter
	if( steigung  < 1){
		// daneben
		int seite = DatCoordMeth::getSide(p_mitte.getPixelCoord(), p_compare.getPixelCoord());

		if(seite < 0){
			// rechts

			if(xc < xm){
				//cout << "//////////////////////////////////////////" << endl;
				//cout << "RECHTS" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				//system("PAUSE");
				return RICHTUNG_RUECK;
			}else if(xc > xm){
				return RICHTUNG_VOR;
			}else if( yc > ym){
				//cout << "//////////// RECHTS ///////////////////////" << endl;
				//cout << "RECHTS" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				return RICHTUNG_RECHTS;
			}else if(yc < ym){
				//cout << "//////////////////////////////////////////" << endl;
				//cout << "RECHTS: links" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				//cout << "yc: " << yc << "  ym: " << ym << endl;
				//system("PAUSE");
				return RICHTUNG_LINKS;
			}
		}else{
			// links
			if( yc < ym){
				return RICHTUNG_LINKS;
			}else if(yc > ym){
				//cout << "//////////// LINKS ///////////////////////" << endl;
				//cout << "RECHTS" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				return RICHTUNG_RECHTS;
			}else if(xc < xm){
				return RICHTUNG_VOR;
			}else if(xc > xm){
				//cout << "//////////// LINKS ///////////////////////" << endl;
				//cout << "RUECK" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				//system("PAUSE");
				return RICHTUNG_RUECK;
			}
		}


	}else{
		// darüber/darunter
		int tier = DatCoordMeth::getTier(p_mitte.getPixelCoord(), p_compare.getPixelCoord());

		if(tier < 0){
			// darunter
			if(yc < ym){
				return RICHTUNG_VOR;
			}else if( yc > ym){
				return RICHTUNG_RUECK;
			}else if(xc < xm){
				return RICHTUNG_LINKS;
			}else if(xc > xm){
				//cout << "//////////// DARUNTER ///////////////////////" << endl;
				//cout << "RECHTS" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				return RICHTUNG_RECHTS;
			}
		}else{
			// darüber
			if(yc > ym){
				return RICHTUNG_VOR;
			}else if( yc < ym){
				return RICHTUNG_RUECK;
			}else if(xc > xm){
				//cout << "//////////// DARÜBER ///////////////////////" << endl;
				//cout << "RECHTS" << endl;
				//cout << "xc: " << xc << "  xm: " << xm << endl;
				return RICHTUNG_RECHTS;
			}else if(xc < xm){
				//cout << "++++++++++++ RECHTS ++++++++++++++++++" << endl;
				return RICHTUNG_LINKS;
			}
		}

		return RICHTUNG_VOR;
	}
	return RICHTUNG_VOR;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## Ermittelt aktuelle Position des Bildmittelpunkts ################################################################
// ##########################################################################################################################
//
DatCoordPoint DatCoordMeth::calcCurrentPosition(DatCoordPoints &points, DatCoord<int> &Bildmitte){

	DatCoordPoint erg;
	int abs_x;
	int abs_y;
	int abs_vertical;
	int abs_horizontal;
	int pos_horizontal;
	int pos_vertikal;
	int pos_referenz = 0;

	int richtung_bildoberseite = 0;
	int richtung_bildunterseite = 0;

	int richtung_bildrechts = 0;
	int richtung_bildlinks = 0;

	double faktor_x;
	double faktor_y;

	erg.setPixel(Bildmitte.getX(), Bildmitte.getY());
	// ermitteln welcher Punkt über und welcher Punkt neben Mittelpunkt ist
	if(points.getCoordAt(pos_referenz).getWorldCoord().getY() == points.getCoordAt(1).getWorldCoord().getY())
	{
		pos_horizontal = 1;
		pos_vertikal = 2;
	}else{
		pos_horizontal = 2;
		pos_vertikal = 1;
	}


	// *************************************************************************************************************************
	// ************************ x und y-faktor bestimmen ***********************************************************************
	// ##################### y-Richtung bestimmen ##############################################################################

	DatLinearEquation horizontale_mittelpunkt(points.getCoordAt(pos_referenz).getPixelCoord(), points.getCoordAt(pos_horizontal).getPixelCoord());
	DatLinearEquation horizontale_vertikal(points.getCoordAt(pos_vertikal).getPixelCoord(), horizontale_mittelpunkt.getSteigung());

	// ermittel wieviele Pixel Referenzpunkt von Bildmittelpunkt entfernt
	abs_y = abs(horizontale_mittelpunkt.getYfor(Bildmitte.getX()) - Bildmitte.getY());

	// ermittel wieviele Pixel Bildmittelpunkt von Objekt entfernt welches am nähesten am Bildmittelpunkt ist
	abs_vertical =  abs(horizontale_mittelpunkt.getYfor(Bildmitte.getX()) - horizontale_vertikal.getYfor(Bildmitte.getX()));

	// --------------------------------------------------------------
	// versuchen 1.#inf zu eliminieren
	if(abs_vertical == 0)
	{
		abs_vertical = 1;
	}
	// --------------------------------------------------------------

	faktor_y = double(abs_y) / abs_vertical;

	// wenn vertikaler Punkt über Referenzpunkt
	if(points.getCoordAt(pos_vertikal).getPixelY() < horizontale_mittelpunkt.getYfor(points.getCoordAt(pos_vertikal).getPixelX())){
		// Wenn Welt-Y von vertikalen Punkt auch über Referenz dann nach Bildoberseite positive Richtung
		if(points.getCoordAt(pos_vertikal).getWorldY() > points.getCoordAt(pos_referenz).getWorldY()){
			richtung_bildoberseite = 1;
			richtung_bildunterseite = -1;
		}else{
			richtung_bildoberseite = -1;
			richtung_bildunterseite = 1;
		}
	}
	// wenn vertikaler Punkt unter Referenzpunkt
	else{
		// Wenn Welt-Y von vertikalen Punkt auch unter Referenz dann nach Bildoberseite positive Richtung
		if(points.getCoordAt(pos_vertikal).getWorldY() < points.getCoordAt(pos_referenz).getWorldY()){
			richtung_bildoberseite = 1;
			richtung_bildunterseite = -1;
		}else{
			richtung_bildoberseite = -1;
			richtung_bildunterseite = 1;
		}
	}

	// ############ bestimmen ob Bildmittelpunkt über oder unter Referenz ######################################################
	// ############ sowie zuweisung des richtigen Faktors ######################################################################
	// wenn Bildoberseite
	if( Bildmitte.getY() < horizontale_mittelpunkt.getYfor(Bildmitte.getX())){
		faktor_y *= richtung_bildoberseite;
	}
	// else (wenn Bilduntereite)
	else{
		faktor_y *= richtung_bildunterseite;
	}

	// ##################### x-Richtung bestimmen ##############################################################################

	DatLinearEquation vertikale_mittelpunkt(points.getCoordAt(pos_referenz).getPixelCoord(), points.getCoordAt(pos_vertikal).getPixelCoord());
	DatLinearEquation vertikale_seitlich(points.getCoordAt(pos_horizontal).getPixelCoord(), vertikale_mittelpunkt.getSteigung());

	// wenn Bildmittelpunkt rechts von Referenzpunkt oder vert
	if(vertikale_mittelpunkt.getXfor(Bildmitte.getY()) < Bildmitte.getX()){
		// Wenn Welt-X von horizontalem Punkt auch rechts von Referenz dann nach Bildrechts positive Richtung
		if(points.getCoordAt(pos_horizontal).getWorldX() > points.getCoordAt(pos_referenz).getWorldX()){
			richtung_bildrechts = 1;
			richtung_bildlinks = -1;
		}else{
			richtung_bildrechts = -1;
			richtung_bildlinks = 1;
		}
	}
	// wenn horizontaler Punkt links von Referenzpunkt
	else{
		// Wenn Welt-X von horizontalen Punkt auch links von Referenz dann nach Bildlinks negative Richtung
		if(points.getCoordAt(pos_horizontal).getWorldX() < points.getCoordAt(pos_referenz).getWorldX()){
			richtung_bildrechts = 1;
			richtung_bildlinks = -1;
		}else{
			richtung_bildrechts = -1;
			richtung_bildlinks = 1;
		}
	}

	// ############ bestimmen ob Bildmittelpunkt rechts oder links von Referenz ################################################
	// ############ sowie zuweisung des richtigen Faktors ######################################################################

	// ermittel wieviele Pixel Bildmittelpunkt von Referenzpunkt entfernt
	abs_x = abs(vertikale_mittelpunkt.getXfor(Bildmitte.getY()) - Bildmitte.getX());

	// ermittel wieviele Pixel Referenzpunkt von Objekt entfernt welches am nähesten am Bildmittelpunkt ist
	abs_horizontal =  abs(vertikale_mittelpunkt.getXfor(Bildmitte.getY()) - vertikale_seitlich.getXfor(Bildmitte.getY()));

	// --------------------------------------------------------------
	// versuchen 1.#inf zu eliminieren
	if(abs_horizontal == 0)
	{
		abs_horizontal == 1;
	}
	// --------------------------------------------------------------
	
	faktor_x = double(abs_x)/double(abs_horizontal);
	//faktor_x = double(abs_horizontal)/double(abs_x);

	// wenn rechts von punkt_auf_gerade
	if( Bildmitte.getX() > vertikale_mittelpunkt.getXfor(Bildmitte.getY()) ){
		faktor_x *= richtung_bildrechts;
	}
	// else (wenn Bildlinks)
	else{
		faktor_x *= richtung_bildlinks;
	}
	// ************************ ENDE: x und y-faktor bestimmen *****************************************************************
	// *************************************************************************************************************************




	erg.setWorldX(points.getCoordAt(pos_referenz).getWorldCoord().getX() + faktor_x);
	erg.setWorldY(points.getCoordAt(pos_referenz).getWorldCoord().getY() + faktor_y);

	return erg;
}

// **************************************************************************************************************************

// ##########################################################################################################################
// ######## filterDuplicates ################################################################################################
// ##########################################################################################################################
//
void DatCoordMeth::filterDuplicates( DatCoordPoints &input){
	int i = 0;
	int j = 0;
	for(i =0; i<input.getCntPicObj(); i++)
	{
		for (j=(i+1); j < input.getCntPicObj(); j++)
		{
			if(isInObj(input.getCoordAt(i).getPixelCoord(), input.getCoordAt(j).getPixelCoord()))
			{
				// Wenn doppelter Weltkoordinaten enthält sichern
				if(input.getCoordAt(i).isWorldSet()){
					//input.getCoordAt(j).setWorld(input.getCoordAt(i).getWorldCoord());
					input.getCoordAt(i) = input.getCoordAt(j);
					input.removePicObjCoord(j);
					// da liste kleiner???
					j--;
				}else{
					input.removePicObjCoord(j);
					// da liste kleiner???
					j--;
				}
			}
		}
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## isInObj #########################################################################################################
// ##########################################################################################################################
bool DatCoordMeth::isInObj(DatCoord<int> obj1, DatCoord<int> obj2)
{
	DatCoord<int> vect = abs(obj1 - obj2);
	int width = obj2.getWidth() / 2;
	int height = obj2.getHeight() / 2;

	if( (vect.getX() < width) && (vect.getY() < height) )
	{
		cout << "###### object filtered #######" << endl;
		return true;
	}
	return false;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## updateKnownPoints ###############################################################################################
// ##########################################################################################################################
void DatCoordMeth::updateKnownPoints(DatCoordPoints &old_points, DatCoordPoints &new_points, int SCHWELLWERT_DIST)
{
	int i = 0;
	int tempPos = -1;
	std::string outputText = "";

	if(old_points.getCntPicObj() > 0){
		for(i = 0; i < new_points.getCntPicObj(); i++){
			tempPos = DatCoordMeth::determineNearest(new_points.getCoordAt(i).getPixelCoord(), old_points);

			// Wenn determineNearest erfolgreich
			if(tempPos >= 0){
				// Wenn bei alter Weltkoordinate gesetzt ist
				if(old_points.getCoordAt(tempPos).isWorldSet()){

					// Wenn neuer Punkt weniger als SCHWELLWERT_DIST von altem Punkt entfernt
					DatCoordPoint tmpVektor((new_points.getCoordAt(i).getPixelCoord() - old_points.getCoordAt(tempPos).getPixelCoord()));
					if( tmpVektor.getPixelCoord().getVecLen() < SCHWELLWERT_DIST){
						// Weltkoordinate für neuen Punkt setzen
						new_points.setWorldObjectAt(i,  old_points.getWorldXCoordAt(tempPos) ,old_points.getWorldYCoordAt(tempPos),old_points.getWorldZCoordAt(tempPos));

						//cout << "_________________________________________________________" << endl;
						//cout << "Schwellwert: " << SCHWELLWERT_DIST << endl;
						//cout << "Distanz: " << tmpVektor.getPixelCoord().getVecLen()  << endl;
						//cout << "WELTALT: x = " <<  old_points.getCoordAt(tempPos).getWorldX() << "; y = " << old_points.getCoordAt(tempPos).getWorldY() << endl;
						//cout << "WELTNEU: x = " <<  new_points.getCoordAt(i).getWorldX() << "; y = " << new_points.getCoordAt(i).getWorldY() << endl;
						//cout << "PIXELOLD: x = " << old_points.getCoordAt(tempPos).getPixelX() << "; y = " << old_points.getCoordAt(tempPos).getPixelY() << endl;
						//cout << "PIXELNEW: x = " << new_points.getCoordAt(i).getPixelX() << "; y = " << new_points.getCoordAt(i).getPixelY() << endl;
						//outputText.append("_________________________________________________________\n" + old_points.getCoordAt(tempPos).toString("alter Punkt") + "\n" + new_points.getCoordAt(i).toString("neuer Punkt") + "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
						//outputText.append("\n");
					}
				}
			}
		}
		//cout << outputText << endl;
	}
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## sortCoordByDistance #############################################################################################
// ##########################################################################################################################
//
//Eingabewerte:
//		&positionen: Vektor mit den Positionen in der Datenstruktur/Klasse DatPicObjects der Objekte die betrachtet werden
//		&points: Alle gefundenen Objekte im Bild
//		&p_reference: Bezugspunkt

void DatCoordMeth::sortCoordByDistance( DatCoord<int> &p_reference, DatCoordPoints &points, vector<int> &positionen){
	unsigned int i;
	vector<DatCoord<int>> elemente;

	// hole Elemente
	for(i = 0; i < positionen.size(); i++){
		elemente.push_back(points.getCoordAt(positionen[i]).getPixelCoord());
	}

	quickSort(positionen , 0, positionen.size() - 1);
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## quickSort #######################################################################################################
// ##########################################################################################################################
//

void DatCoordMeth::quickSort( vector<int> &input, int first, int last){
	int i, j, x, tmp_int;

	if(first < last){
		x = input[(first + last) / 2];
		i = first;
		j = last;
		do{
			while(input[i] < x){
				i++;
			}
			while(input[j] > x){
				j--;
			}

			if(i <= j){
				tmp_int = input[i];
				input[i] = input[j];
				input[j] = tmp_int;

				i++;
				j--;
			}
		}while( i < j);
		quickSort(input, first, j);
		quickSort(input, i, last);
	}
}

// **************************************************************************************************************************
