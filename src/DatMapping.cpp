// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatMapping.cpp #####################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, Philip Gssner,
//	Stand: 23.01.2013
//
//
//

#include "DatMapping.h"
#include "DatCoord.h"

#include <string>

DatMapping::DatMapping(void)
{
}


DatMapping::~DatMapping(void)
{
}

// ##########################################################################################################################
// ######## DatMappingInit ##################################################################################################
// ##########################################################################################################################
DatCoordPoints DatMapping::DatMappingInit(DatCoordPoints &pics, DatCoord<int> &referenz_punkt)
{
	int tempPos, mitte_Pos;
	int pos_init = 0;
	DatCoordPoints erg;
	DatCoordPoint tmpObjekt;


	// wenn mindestens 3 erkannte Objekte vorhanden
	if( pics.getCntPicObj() > 2){

		// ################################################### Mitte ####################################################################
		mitte_Pos = DatCoordMeth::determineNearest(referenz_punkt, pics);
		erg.addPixelCoord(pics.getCoordAt(mitte_Pos).getPixelCoord().getX(), pics.getCoordAt(mitte_Pos).getPixelCoord().getY(), pics.getCoordAt(mitte_Pos).getPixelCoord().getWidth(), pics.getCoordAt(mitte_Pos).getPixelCoord().getHeight() );
		erg.setWorldObjectAt(pos_init, 0,0,0);

		// ################################################### Horizontal ###############################################################
		tempPos = DatCoordMeth::determineNearestHorizontal(referenz_punkt, mitte_Pos, pics);
		if(tempPos >= 0){
			tmpObjekt = pics.getCoordAt(tempPos);
			erg.addCoord(tmpObjekt);
		}

		// ################################################### Vertikal #################################################################
		tempPos = DatCoordMeth::determineNearestVertical(referenz_punkt, mitte_Pos, pics);
		if(tempPos >= 0){
			tmpObjekt = pics.getCoordAt(tempPos);
			erg.addCoord(tmpObjekt);
		}
	}

	return erg;
}
// **************************************************************************************************************************


// ##########################################################################################################################
// ######## DatMappingUpdate ################################################################################################
// ##########################################################################################################################
DatCoordPoints DatMapping::DatMappingUpdate(DatCoordPoints &pics_neu, DatCoordPoints &pics_alt, DatCoord<int> &referenz_punkt, int SCHWELLWERT_DIST, InLoc_Richtung &richtung){
	int i,j;
	int tempPos;
	int mitte_Pos;// mitte_Pos ist Bezugspunkt
	int pos_aktuell = 0;
	DatCoordPoints erg;

	// Bekannte Punkte ermitteln
	DatCoordMeth::updateKnownPoints(pics_alt, pics_neu, SCHWELLWERT_DIST);



	//  wenn mindestens 3 erkannte Objekte vorhanden
	if( pics_neu.getCntPicObj() > 2){

		// ################################################### Mitte ####################################################################
		mitte_Pos = DatCoordMeth::determineNearest(referenz_punkt, pics_neu);
		erg.addPixelCoord(pics_neu.getCoordAt(mitte_Pos).getPixelCoord().getX(), pics_neu.getCoordAt(mitte_Pos).getPixelCoord().getY(), pics_neu.getCoordAt(mitte_Pos).getPixelCoord().getWidth(), pics_neu.getCoordAt(mitte_Pos).getPixelCoord().getHeight() );
		if(pics_neu.getCoordAt(mitte_Pos).isWorldSet()){
			erg.setWorldObjectAt( 0, pics_neu.getCoordAt(mitte_Pos).getWorldX(),pics_neu.getCoordAt(mitte_Pos).getWorldY(),pics_neu.getCoordAt(mitte_Pos).getWorldZ());
		}

		// ------------------ Richtung ermitteln ----------------------------------------------------------------
		//int richtung = RICHTUNG_VOR;
		//DatCoordPoint vertikaler_punkt;
		//DatCoordPoint mittelpunkt = pics_neu.getCoordAt(mitte_Pos);
		//bool oberhalb = false;

		//// vertikalen Punkt ermitteln
		//for(i = 0; i < pics_neu.getCntPicObj(); i++)
		//{
		//	if(pics_neu.getWorldXCoordAt(i) == mittelpunkt.getWorldX())
		//	{
		//		if(pics_neu.getWorldYCoordAt(i) == (mittelpunkt.getWorldY() + 1))
		//		{
		//			vertikaler_punkt = pics_neu.getCoordAt(i);
		//			oberhalb = true; 
		//		}
		//		if( (!oberhalb) && (pics_neu.getWorldYCoordAt(i) == (mittelpunkt.getWorldY() - 1)))
		//		{
		//			vertikaler_punkt = pics_neu.getCoordAt(i);
		//		}
		//	}
		//}

		//
		//DatCoord<int> vektorTmp = vertikaler_punkt.getPixelCoord() - mittelpunkt.getPixelCoord();
		//DatCoord<double> vektorMitteVert;
		//vektorMitteVert.setX(vektorTmp.getX());
		//vektorMitteVert.setY(vektorTmp.getY());
		//double vektorMitteSteigung = vektorMitteVert.getY() / vektorMitteVert.getX();
		//int v_x = vektorMitteVert.getX();
		//int v_y = vektorMitteVert.getY();

		//if(oberhalb)
		//{
		//	if(abs(vektorMitteSteigung) >= 1)
		//	{
		//		if(v_y <= 0)
		//		{
		//			richtung = RICHTUNG_VOR;
		//		}
		//		else
		//		{
		//			richtung = RICHTUNG_RUECK;
		//		}
		//	}
		//	else
		//	{
		//		if(v_x >= 0)
		//		{
		//			richtung = RICHTUNG_RECHTS;
		//		}
		//		else
		//		{
		//			richtung = RICHTUNG_LINKS;
		//		}
		//	}
		//}
		//// Wenn unterer Punkt verwendet wird
		//else
		//{
		//	if(abs(vektorMitteSteigung) >= 1)
		//	{
		//		if(v_y >= 0)
		//		{
		//			richtung = RICHTUNG_VOR;
		//		}
		//		else
		//		{
		//			richtung = RICHTUNG_RUECK;
		//		}
		//	}
		//	else
		//	{
		//		if(v_x <= 0)
		//		{
		//			richtung = RICHTUNG_RECHTS;
		//		}
		//		else
		//		{
		//			richtung = RICHTUNG_LINKS;
		//		}
		//	}
		//}

		//if(richtung.isSet())
		//{
			string text_richtung = "";
			int tmpRichtung = richtung.getRichtung();
			if(tmpRichtung == RICHTUNG_VOR){
				text_richtung = "++++++++++++++++++++++++++++vor";
			}else if(tmpRichtung == RICHTUNG_RUECK){
				text_richtung = "----------------------------rueck";
			}else if(tmpRichtung == RICHTUNG_RECHTS){
				text_richtung = "............................rechts";
			}else if(tmpRichtung == RICHTUNG_LINKS){
				text_richtung = "____________________________links";
			}else{
				text_richtung = "ACHTUNG FEHLER -> keine Richtung";
			}
			cout << "RICHTUNG: " << text_richtung << endl;
		//}
		//else
		if(!richtung.isSet())
		{
			cout << "///// Richtung noch nicht definiert ///////" << endl;
		}


		// ################################################### Horizontal ###############################################################
		DatCoordMeth::determineHorizontal( erg, referenz_punkt, mitte_Pos, pics_neu, richtung.getRichtung());

		// ################################################### Vertikal #################################################################
		DatCoordMeth::determineVertikal( erg, referenz_punkt, mitte_Pos, pics_neu, richtung.getRichtung());

		// Testen ob vertikale
		if((!richtung.isSet()) && (erg.getCntPicObj() == 3))
		{
			int abweichung_vertikal = abs(erg.getPixelXCoordAt(2) - erg.getPixelXCoordAt(0));

			// Wenn Abweichung kleiner Schwellwert Dann subtrahend setzen
			if(abweichung_vertikal < 5)
			{
				richtung.setSubtrahend(richtung.getKompass());
			}
		}
	}

	return erg;
}
// **************************************************************************************************************************

// ##########################################################################################################################
// ######## ValidateDistance ################################################################################################
// ##########################################################################################################################
void DatMapping::ValidateDistance(DatCoordPoints &pics, double epsilon, int count_x, int count_y)
{
	int len_ref = 0;
	DatCoord<int> tmpVec1;
	DatCoord<int> tmpVec2;

	if(count_x>1)
	{
		tmpVec1 = abs(pics.getCoordAt(0).getPixelCoord() - pics.getCoordAt(1).getPixelCoord());
		tmpVec2 = abs(pics.getCoordAt(0).getPixelCoord() - pics.getCoordAt(2).getPixelCoord());

		if(tmpVec1.getVecLen() < tmpVec2.getVecLen()){
			pics.removePicObjCoord(2);
			count_x--;
		}else{
			pics.removePicObjCoord(1);
			count_x--;
		}
	}

	if(count_y >1)
	{
		tmpVec1 = abs(pics.getCoordAt(0).getPixelCoord() - pics.getCoordAt(count_x + 1).getPixelCoord());
		tmpVec2 = abs(pics.getCoordAt(0).getPixelCoord() - pics.getCoordAt(count_x + 2).getPixelCoord());

		if(tmpVec1.getVecLen() < tmpVec2.getVecLen()){
			pics.removePicObjCoord(count_x + 1);
		}else{
			pics.removePicObjCoord(count_x + 2);
		}
	}

}
// **************************************************************************************************************************
