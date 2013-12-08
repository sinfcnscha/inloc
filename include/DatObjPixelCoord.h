#pragma once

class DatObjPixelCoord
{
private:
	int x;
	int y;
	int width;
	int height;
public:

	DatObjPixelCoord(void);

	DatObjPixelCoord(int x, int y, int width, int height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	~DatObjPixelCoord(void);

	int getX(void){
		return this->x;
	}

	void setX(int x){
		this->x = x;
	}

	int getY(void){
		return this->y;
	}

	void setY(int y){
		this->y = y;
	}

	int getWidth(void){
		return this->width;
	}

	void setWidth(int width){
		this->width = width;
	}

	int getHeight(void){
		return this->height;
	}

	void setHeight(int height){
		this->height = height;
	}

};

