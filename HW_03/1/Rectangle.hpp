#pragma once
#include "Shape.hpp"

class Rectangle: public Shape
{
	int width;
	int height;
public:
	int GetWidth();
	int GetHeight();
	void SetWidth(int Width);
	void SetHeight(int Height);
	Rectangle();
	Rectangle(int X, int Y, MyString Fill, int Width, int Height);
	Rectangle(const Rectangle& R);
	Rectangle& operator=(const Rectangle& R);
	~Rectangle();
	virtual Shape* clone()const;
	virtual bool WithinCircle(const int X, const int Y, const int R)const;
	virtual bool WithinRect(const int X, const int Y, const int Width, const int Heigth) const;
	virtual bool PointIn(const int X, const int Y)const;
	virtual void Print()const;
	virtual double GetArea()const;
	virtual double GetPerimeter()const;
	virtual const char* GetType()const;
	virtual void svgel(std::ofstream& ostr)const;
};
