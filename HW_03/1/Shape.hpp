#pragma once
#include "MyString.hpp"
#include <fstream>

class Shape
{
protected:
	MyString fill;
	int x;
	int y;
public:
	void SetX(const int X);
	void SetY(const int Y);
	void SetFill(const MyString & Fill);
	int GetX()const;
	int GetY()const;
	const MyString getFill()const;
	Shape();
	Shape(const int X, const int Y, const  MyString& Fill);
	Shape(const Shape& S);
	virtual Shape* clone()const = 0;
	virtual bool WithinCircle(const int X,const int Y,const int R)const=0;
	virtual bool WithinRect(const int X,const int Y,const int Width,const int Heigth) const=0;
	virtual bool PointIn(const int X, const int Y)const =0;
	virtual void Print()const = 0;
	virtual double GetArea()const = 0;
	virtual double GetPerimeter()const = 0;
	virtual void translate(const int Vertical, const int horizontal);
	virtual const char* GetType()const = 0;
	virtual void svgel(std::ofstream& ostr)const  = 0;
	virtual ~Shape();
};
