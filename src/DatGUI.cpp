// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatGUI.cpp #########################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 17.01.2012
//
//
//

#include "DatGUI.h"

using namespace std;

// ################## Button Init #######################################################################################
void callbackTrackbarInit(int state, void*){
	cout << "YESSSSSSSSSSSS!!!" << endl;
}

// ################## Pause #############################################################################################
boolean paused = false;
void onMouse( int event, int x, int y, int , void*)
{
	if( event == CV_EVENT_LBUTTONDOWN ){
		paused = true;
	}
}

DatGUI::DatGUI(void)
{
}


DatGUI::~DatGUI(void)
{
	//delete(this);
}

void DatGUI::init(){

}
void DatGUI::update(cv::Mat &img, DatCoordPoint& bildmitte, DatCoordPoints WeltBild, DatCoordPoints BildObjekte, double speed){
	int i;
	CvFont font;
	cv::Point bildmittelpunkt;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1.8, CV_AA);
	string objekt_text, text_pixelCoord, text_worldCoord, text_speed;
	char tmp[512];

	cv::Point pt1, pt1_text, pt1_text2, pt_mitte, pt_img2;
	cv::Point ptSpeed;
	cv::Point pt_welt_seitlich, pt_welt_mitte, pt_welt_rechts, pt_welt_vertikale, pt_welt_unten, pt_tmp1, pt_tmp2;
	int x, y, height, width;

	cv::Mat img2 = img.clone();

	bildmittelpunkt.x = bildmitte.getPixelX();// img.cols / 2;
	bildmittelpunkt.y = bildmitte.getPixelY();//img.rows / 2;


	// |||||||||||||||||||||||||||||||||||||||||||||||||||
	cv::Point pt_mittelpunkt_text( bildmittelpunkt.x, bildmittelpunkt.y + 20);

	// Markiere Mittelpunkt
	// TEXT PIXEL_COORD
	text_pixelCoord = "x: ";
	itoa( bildmittelpunkt.x , tmp,10);
	text_pixelCoord += tmp;	
	text_pixelCoord +=  "; y: ";
	itoa( bildmittelpunkt.y, tmp,10);
	text_pixelCoord+= tmp;

	// TEXT WORLD_COORD
	stringstream NumberStringX;
	NumberStringX << bildmitte.getWorldX();   
	text_worldCoord = "x: ";
	text_worldCoord += NumberStringX.str();	
	text_worldCoord +=  "; y: ";
	stringstream NumberStringY;
	NumberStringY << bildmitte.getWorldY();   
	text_worldCoord+= NumberStringY.str();

	circle(img, bildmittelpunkt, 10, CV_RGB(255,255,255), 2, 1, 0);
	circle(img2, bildmittelpunkt, 10, CV_RGB(255,255,255), 2, 1, 0);

	//putText(img, text_pixelCoord, pt_mittelpunkt_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,255,255), 1.8, 8, false );
	putText(img, text_worldCoord, pt_mittelpunkt_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,255,255), 1.8, 8, false );

	cv::setMouseCallback( "result", onMouse, 0);

	// |||||||||||||||||||||||||||||||||||||||||||||||||||

	// ################## gespeicherte Objekte im Bild markieren ############################################################
	if(WeltBild.getCntPicObj() > 2){
		for( i = 0; i < WeltBild.getCntPicObj(); i++){
			x = WeltBild.getPixelXCoordAt(i);
			y = WeltBild.getPixelYCoordAt(i);
			width = WeltBild.getPixelWidthAt(i);
			height = WeltBild.getPixelHeightAt(i);

			pt1.x = x; 
			pt1.y = y;

			pt1_text.x = pt1.x - width/2; 
			pt1_text.y = pt1.y - height/2 - 5;

			pt1_text2.x = pt1.x - width/2; 
			pt1_text2.y = pt1.y + height/2 + 15;

			// Text für Pixelkoordinate
			text_pixelCoord = "x: ";
			itoa( x , tmp,10);
			text_pixelCoord += tmp;	
			text_pixelCoord +=  "; y: ";
			itoa( y, tmp,10);
			text_pixelCoord+= tmp;

			// Text für Weltkoordinate
			objekt_text = "x: ";
			itoa( WeltBild.getWorldXCoordAt(i), tmp,10);
			/*cout << "------------------ " << WeltBild.getWorldXCoordAt(i) << " " << WeltBild.getWorldYCoordAt(i) << endl;*/
			objekt_text += tmp;	
			objekt_text +=  "; y: ";
			itoa( WeltBild.getWorldYCoordAt(i), tmp,10);
			objekt_text+= tmp;

			// Male Weltkoordinate (0,0) grün Mittelpunkt +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			if(i == 0){
				pt_welt_mitte.x = WeltBild.getCoordAt(i).getPixelCoord().getX();
				pt_welt_mitte.y = WeltBild.getCoordAt(i).getPixelCoord().getY();

				putText(img, objekt_text, pt1_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0,255,0), 1.5, 8, false );

				putText(img, text_pixelCoord, pt1_text2, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0,255,0), 1.5, 8, false );

				circle(img, pt1, (width/2), CV_RGB(0,255,0), 2, 1, 0);

				// Male Linie zum Bildmittelpunkt
				line(img, pt_welt_mitte, bildmittelpunkt,CV_RGB(0,255,0), 2, 8, 0);

				// Dreieck
				//pt_tmp1.x = pt_welt_mitte.x - ( pt_welt_mitte.x - bildmittelpunkt.x);// - pt_welt_mitte.x;
				//pt_tmp1.y = pt_welt_mitte.y;

				//line(img, pt_welt_mitte, pt_tmp1,CV_RGB(0,255,0), 2, 8, 0);
				//line(img, pt_tmp1, bildmittelpunkt,CV_RGB(0,255,0), 2, 8, 0);

				// ############################# Vektortext #######################################################################
				// Vektortext
				//text_pixelCoord = "x: ";
				//itoa( pt_tmp1.x , tmp,10);
				//text_pixelCoord += tmp;	
				//text_pixelCoord +=  "; y: ";
				//itoa( pt_tmp1.y - ( pt_welt_mitte.y - bildmittelpunkt.y), tmp,10);
				//text_pixelCoord+= tmp;


				//pt_tmp1.x = bildmittelpunkt.x;
				//pt_tmp1.y = bildmittelpunkt.y - 5;
				//putText(img, text_pixelCoord, pt_tmp1, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0x00,0xFF,0x00), 1.9, 8, false );


				//text_pixelCoord = "x: ";
				//itoa( bildmittelpunkt.x - pt_welt_mitte.x , tmp,10);
				//text_pixelCoord += tmp;	
				//text_pixelCoord +=  "; y: ";
				//itoa( bildmittelpunkt.y - pt_welt_mitte.y - ( pt_welt_mitte.y - bildmittelpunkt.y), tmp,10);
				//text_pixelCoord+= tmp;


				//pt_tmp1.x = bildmittelpunkt.x;
				//pt_tmp1.y = pt_tmp1.y - 15;
				//putText(img, text_pixelCoord, pt_tmp1, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0x00,0xFF,0x00), 1.96, 8, false );
				// ################################################################################################################

			}
			// ################################## seitlicher Punkt ################################################################
			// FARBE: blau
			else if(i == 1){
				pt_welt_seitlich.x = WeltBild.getCoordAt(i).getPixelCoord().getX();
				pt_welt_seitlich.y = WeltBild.getCoordAt(i).getPixelCoord().getY();

				putText(img, objekt_text, pt1_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0,0,255), 1.5, 8, false );

				putText(img, text_pixelCoord, pt1_text2, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0,0,255), 1.5, 8, false );

				circle(img, pt1, (width/2), CV_RGB(0,0,255), 2, 1, 0);

				// Male Linie zum Bildmittelpunkt
				line(img, pt_welt_seitlich, bildmittelpunkt,CV_RGB(0,0,255), 2, 8, 0);
			}

			// ################################## vertikaler Punkt ################################################################
			// FARBE: rot
			else if(i == 2){
				pt_welt_vertikale.x = WeltBild.getCoordAt(i).getPixelCoord().getX();
				pt_welt_vertikale.y = WeltBild.getCoordAt(i).getPixelCoord().getY();

				putText(img, objekt_text, pt1_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,0,0), 1.5, 8, false );

				putText(img, text_pixelCoord, pt1_text2, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,0,0), 1.5, 8, false );

				circle(img, pt1, (width/2), CV_RGB(255,0,0), 2, 1, 0);
				// Male Linie zum Bildmittelpunkt
				line(img, pt_welt_vertikale, bildmittelpunkt,CV_RGB(255,0,0), 2, 8, 0);
			}
			// ################################## Geschwindigkeit #################################################################
			// Text für Geschwindigkeit
			ptSpeed.x = 0;
			ptSpeed.y = 15;
			stringstream NumberStringSpeed;
			NumberStringSpeed << speed;   
			text_speed = "SPEED: ";
			text_speed += NumberStringSpeed.str();	
			putText(img, text_speed, ptSpeed, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,0,0), 1.5, 8, false );

			imshow("result", img);cv::waitKey(1);//ms

			//cvMoveWindow("result", 500, 0);

			//img.release();
		}
	}

	// ################## Male Bild mit allen erkannten Objekten ############################################################

	//cv::createTrackbar("INIT_BAR", "result", 0, 1, callbackTrackbarInit, 0);
	 
	for( i = 0; i < BildObjekte.getCntPicObj(); i++){
		x = BildObjekte.getPixelXCoordAt(i);
		y = BildObjekte.getPixelYCoordAt(i);
		width = BildObjekte.getPixelWidthAt(i);
		height = BildObjekte.getPixelHeightAt(i);

		pt1.x = x; 
		pt1.y = y;

		pt1_text.x = pt1.x - width/2; 
		pt1_text.y = pt1.y - height/2 - 5;
		pt1_text2.x = pt1.x - width/2; 
		pt1_text2.y = pt1.y + height/2 + 15;

		// Text für Pixelkoordinate
		text_pixelCoord = "x: ";
		itoa( x , tmp,10);
		text_pixelCoord += tmp;	
		text_pixelCoord +=  "; y: ";
		itoa( y, tmp,10);
		text_pixelCoord+= tmp;
		// Text für Weltkoordinate
		objekt_text = "x: ";
		itoa( BildObjekte.getWorldXCoordAt(i), tmp,10);
		objekt_text += tmp;	
		objekt_text +=  "; y: ";
		itoa( BildObjekte.getWorldYCoordAt(i), tmp,10);
		objekt_text+= tmp;

		
		pt_img2.x = BildObjekte.getCoordAt(i).getPixelCoord().getX();
		pt_img2.y = BildObjekte.getCoordAt(i).getPixelCoord().getY();
		//circle(img2, pt_img2, (BildObjekte.getCoordAt(i).getPixelCoord().getWidth() / 2), CV_RGB(255,0,0), 2, 1, 0);
		
		if(BildObjekte.getCoordAt(i).isWorldSet()){
			circle(img2, pt_img2, (BildObjekte.getCoordAt(i).getPixelCoord().getWidth() / 2), CV_RGB(255,0,0), 2, 1, 0);
			putText(img2, objekt_text, pt1_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,0,0), 1.5, 8, false );
		}else{
			circle(img2, pt_img2, (BildObjekte.getCoordAt(i).getPixelCoord().getWidth() / 2), CV_RGB(255,255,255), 2, 1, 0);
			putText(img2, objekt_text, pt1_text, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,255,255), 1.5, 8, false );
		}
		putText(img2, text_pixelCoord, pt1_text2, CV_FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(0,255,0), 1.5, 8, false );
	}
	imshow("result2", img2);
	//cvMoveWindow("result2", 1000, 550);
	cv::waitKey(1);//ms

	// ################## Pause????????? ####################################################################################
	if(paused){
		cv::waitKey();
		paused = false;
	}
}
void DatGUI::destroy(void){
	cv::destroyWindow("result");
}
