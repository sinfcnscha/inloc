#pragma once

#include "DatPicObjects.h"

class DatCoordContainer
{
private:
	DatPicObjects<int> pics;
	DatPicObjects<double> map;

public:
	DatCoordContainer(void);
	~DatCoordContainer(void);

	void setPics(DatPicObjects<int> pics){
		this->pics = pics;
	}

	DatPicObjects<int> getPics(void){
		return this->pics;
	}

	void setMap(DatPicObjects<double> map){
		this->map = map;
	}

	DatPicObjects<double> getMap(void){
		return this->map;
	}

};

