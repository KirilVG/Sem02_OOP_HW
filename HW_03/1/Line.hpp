#pragma once
#include "Shape.hpp"

class Line: public Shape
{
	int x2;
	int y2;
public:
	void SetX2(int NewX);
	void SetY2(int NewY);
	int GetX2()const;
	int GetY2()const;
	Line();
	Line(const int X, const int Y, const int X2, const int Y2, const MyString& Fill);
	Line(const Line& l);
	Line& operator=(const Line& l);
	~Line();
	virtual Shape* clone()const;
	virtual bool WithinCircle(const int X, const int Y, const int R)const;
	virtual bool WithinRect(const int X, const int Y, const int Width, const int Heigth) const;
	virtual bool PointIn(const int X, const int Y)const;
	void Print()const override;
	virtual double GetArea()const;
	virtual double GetPerimeter()const;
	virtual const char* GetType()const;
	virtual void svgel(std::ofstream& ostr)const;
};

