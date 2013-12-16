// ##########################################################################################################################
// ################## SPEED OVER GROUNG: DatCoord.h #########################################################################
// ##########################################################################################################################	
//	Autoren: Christian Schauer, ,
//	Stand: 12.12.2011
//
//
//

#pragma once
#include <math.h>
#include <stdlib.h>


template <class T> class DatCoord
{

private:
	T x;
	T y;
	T z;
	T width;
	T height;

public:

	DatCoord(void)
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	DatCoord(T x, T y){
		this->x = x;
		this->y = y;
		this->z = 0;
	}

	DatCoord(T x, T y, T width, T height){
		this->x = x;
		this->y = y;
		this->z = 0;
		this->width = width;
		this->height = height;
	}

	DatCoord(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	DatCoord(T x, T y, T z, T width, T height)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->width = width;
		this->height = height;
	}

	~DatCoord()
	{
		//	delete(this);
	}

	void setX( T x){
		this->x = x;
	}

	T getX(void){
		return this->x;
	}

	void setY( T y){
		this->y = y;
	}

	T getY(void){
		return this->y;
	}

	void setZ( T z){
		this->z = z;
	}

	T getZ(void){
		return this->z;
	}

	void setWidth(int width){
		this->width = width;
	}

	T getWidth(void){
		return this->width;
	}

	void setHeight(int height){
		this->height = height;
	}

	T getHeight(void){
		return this->height;
	}

	T getVecLen(void){
		//return this->x + this->y;
		//return sqrt(pow(this->x, 2.0) + pow(this->y, 2.0));
		return sqrt( double((this->x * this->x) + (this->y * this->y)) );
	}

	bool is(T x, T y){
		if((this->x == x) && (this->y == y)){
			return true;
		}
		else{
			return false;
		}
	}

};

template <class T>
DatCoord<T> operator + ( DatCoord<T> &input1, DatCoord<T> &input2){
	DatCoord<T> erg;
	erg.setX(input1.getX() + input2.getX());
	erg.setY(input1.getY() + input2.getY());
	erg.setZ(input1.getZ() + input2.getZ());
	return erg;
};

template <class T>
DatCoord<T> operator * ( int &skalar, DatCoord<T> &input){
	DatCoord<T> erg;
	erg.setX(skalar * input.getX());
	erg.setY(skalar * input.getY());
	erg.setZ(skalar * input.getZ());
	return erg;
};

template <class T>
DatCoord<T> operator - ( DatCoord<T> &input1, DatCoord<T> &input2){
	DatCoord<T> erg;
	erg.setX(input1.getX() - input2.getX());
	erg.setY(input1.getY() - input2.getY());
	erg.setZ(input1.getZ() - input2.getZ());
	return erg;
};

template <class T>
DatCoord<T> abs( DatCoord<T> input){
	DatCoord<T> output;
	output.setX(abs(input.getX()));
	output.setY(abs(input.getY()));
	output.setZ(abs(input.getZ()));
	return output;
};


template <class T>
bool operator == ( DatCoord<T> &input1, DatCoord<T> &input2){

	if( (input1.getX() + input1.getY() + input1.getX()) == (input2.getX() + input2.getY() + input2.getZ())){
		return true;
	}else{
		return false;
	}
};

template <class T>
bool operator != ( DatCoord<T> &input1, DatCoord<T> &input2){

	if( (input1.getX() + input1.getY() + input1.getZ()) != (input2.getX() + input2.getY() + input2.getZ())){
		return true;
	}else{
		return false;
	}
};


template <class T>
bool operator < ( DatCoord<T> &input1, DatCoord<T> &input2){

	if( (input1.getX() + input1.getY() + input1.getZ()) < (input2.getX() + input2.getY() + input2.getZ())){
		return true;
	}else{
		return false;
	}
};

template <class T>
bool operator > ( DatCoord<T> &input1, DatCoord<T> &input2){

	if( (input1.getX() + input1.getY() + input1.getZ()) > (input2.getX() + input2.getY() + input2.getZ())){
		return true;
	}else{
		return false;
	}

	//template <class T>
	//bool operator == ( DatCoord<T> &input1, DatCoord<T> &input2){

	//	if( (input1.getX() == input2.getX()) && (input1.getY() == input2.getY()) && (input1.getZ() == input2.getZ()) && (input1.getWidht() == input2.getWidht() ) && (input1.getHeight() == input2.getHeight()) ){
	//		return true;
	//	}else{
	//		return false;
	//	}
	//}
};


