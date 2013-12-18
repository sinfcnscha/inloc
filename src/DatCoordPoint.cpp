// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoordPoint.cpp ##################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 12.12.2011
//
//
//

#include "DatCoordPoint.h"


DatCoordPoint::DatCoordPoint(void)
{
	this->PixelCoord = DatCoord<int>(0,0,0,0);
	this->WorldCoord = DatCoord<double>(0,0,0,0,0);
	this->worldExists = false;
}
DatCoordPoint::DatCoordPoint(DatCoord<int> input){
	this->PixelCoord = input;
	this->WorldCoord = DatCoord<double>(0,0,0,0,0);
	this->worldExists = false;
}

DatCoordPoint::DatCoordPoint(int x, int y, int width, int height){
	this->PixelCoord = DatCoord<int>(x,y,width,height);
	this->WorldCoord = DatCoord<double>(0,0,0,0,0);
	this->worldExists = false;
}

DatCoordPoint::~DatCoordPoint(void)
{
}

void DatCoordPoint::setPixel(int x, int y){
	this->PixelCoord = DatCoord<int>(x,y);
}
void DatCoordPoint::setPixel(int x, int y, int width, int height){
	this->PixelCoord = DatCoord<int>(x,y,width,height);
}
void DatCoordPoint::setPixelX(int x){
	this->PixelCoord.setX(x);
}
void DatCoordPoint::setPixelY(int y){
	this->PixelCoord.setY(y);
}
void DatCoordPoint::setPixelW(int width){
	this->PixelCoord.setWidth(width);
}
void DatCoordPoint::setPixelH(int height){
	this->PixelCoord.setHeight(height);
}
int DatCoordPoint::getPixelX(){
	return this->PixelCoord.getX();
}
int DatCoordPoint::getPixelY(){
	return this->PixelCoord.getY();
}
int DatCoordPoint::getPixelW(){
	return this->PixelCoord.getWidth();
}
int DatCoordPoint::getPixelH(){
	return this->PixelCoord.getHeight();
}




DatCoord<double> &DatCoordPoint::getWorldCoord(){
	return this->WorldCoord;
}
DatCoord<int>& DatCoordPoint::getPixelCoord(){
	return this->PixelCoord;
}

void DatCoordPoint::setWorld(DatCoord<double> input){
	this->WorldCoord = input;
	this->worldExists = true;
}

void DatCoordPoint::setWorld(double x, double y, double z){
	this->WorldCoord = DatCoord<double>(x,y,z);
	this->worldExists = true;
}
void DatCoordPoint::setWorld(double x, double y, double z, double width, double height){
	this->WorldCoord = DatCoord<double>(x,y,z,width,height);
	this->worldExists = true;
}
void DatCoordPoint::setWorldX(double x){
	this->WorldCoord.setX(x);
	this->worldExists = true;
}
void DatCoordPoint::setWorldY(double y){
	this->WorldCoord.setY(y);
	this->worldExists = true;
}
void DatCoordPoint::setWorldZ(double z){
	this->WorldCoord.setZ(z);
	this->worldExists = true;
}
void DatCoordPoint::setWorldW(double width){
	this->WorldCoord.setWidth(width);
}
void DatCoordPoint::setWorldH(double height){
	this->WorldCoord.setHeight(height);
}

double DatCoordPoint::getWorldX(){
	return this->WorldCoord.getX();
}
double DatCoordPoint::getWorldY(){
	return this->WorldCoord.getY();
}
double DatCoordPoint::getWorldZ(){
	return WorldCoord.getZ();
}
double DatCoordPoint::getWorldW(){
	return this->WorldCoord.getWidth();
}
double DatCoordPoint::getWorldH(){
	return this->WorldCoord.getHeight();
}

bool DatCoordPoint::isWorldSet(void){
	return this->worldExists;
}

std::string DatCoordPoint::toString(void){

	const int TABELLENBREITE = 40;
	int i;

	std::ostringstream os;
	std::string sx = "# x = ";
	std::string sy = "# y = ";
	std::string sz = "# z = ";
	std::string swidth = "# width = ";
	std::string sheight = "# height = ";
	std::string pixel_part = "";
	std::string world_part = "";
	std::string erg = "";
	const std::string START_LINE = "############# DatCoordPoint #############\n";
	const std::string END_LINE = "#########################################\n";

	// Pixelpart
	os.str("");
	os << this->getPixelX();
	sx.append(os.str());
	for(i = sx.length(); i < TABELLENBREITE; i++){
		sx.append(" ");
	}
	sx.append("#\n");

	os.str("");
	os << this->getPixelY();
	sy.append(os.str());
	for(i = sy.length(); i < TABELLENBREITE; i++){
		sy.append(" ");
	}
	sy.append("#\n");
	
	os.str("");
	os << this->getPixelCoord().getWidth();
	swidth.append(os.str());
	for(int i = swidth.length(); i < TABELLENBREITE; i++){
		swidth.append(" ");
	}
	swidth.append("#\n");
	
	os.str("");
	os << this->getPixelCoord().getHeight();
	sheight.append(os.str());
	for(i = sheight.length(); i < TABELLENBREITE; i++){
		sheight.append(" ");
	}
	sheight.append("#\n");

	pixel_part = "#*** Pixelkoordinaten: *****************#\n" + sx + sy + swidth + sheight;

	sx = "# x = ";
	sy = "# y = ";
	sz = "# z = ";

	// Weltpart
	if(this->isWorldSet()){
		os.str("");
		// ''''''''' x '''''''''''
		os << this->getWorldX();
		sx.append(os.str());
		for(i = sx.length(); i < TABELLENBREITE; i++){
			sx.append(" ");
		}
		sx.append("#\n");
		// ''''''''' y '''''''''''
		os.str("");
		os << this->getWorldY();
		sy.append(os.str());
		for(i = sy.length(); i < TABELLENBREITE; i++){
			sy.append(" ");
		}
		sy.append("#\n");
		os.str("");
		// ''''''''' z '''''''''''
		os << this->getWorldZ();
		sz.append(os.str());
		for(i = sz.length(); i < TABELLENBREITE; i++){
			sz.append(" ");
		}
		sz.append("#\n");
	}else{
		sx.append("not set");
		for(i = sx.length(); i < TABELLENBREITE; i++){
			sx.append(" ");
		}
		sx.append("#\n");

		sy.append("not set");
		for(i = sy.length(); i < TABELLENBREITE; i++){
			sy.append(" ");
		}
		sy.append("#\n");

		sz.append("not set");
		for(i = sz.length(); i < TABELLENBREITE; i++){
			sz.append(" ");
		}
		sz.append("#\n");
	}

	world_part = "#*** Weltkoordinaten: ******************#\n" + sx + sy + sz;

	erg = START_LINE + pixel_part + world_part + END_LINE;
	return erg;
}

std::string DatCoordPoint::toString(std::string title){
	//return title;
	const int TABELLENBREITE = 40;
	int i;
	std::string erg = "";
	std::string title_line = "*** TITLE: ";

	// Titel
	title.append(" ");
	title_line.append(title);
	
	for(i = title_line.length(); i <= TABELLENBREITE; i++){
		title_line.append("*");
	}
	title_line.append("\n");

	erg = title_line + this->toString();
	return erg;
}


