#pragma once
#include "Shape.hpp"

class Circle: public Shape
{
	int radius;
public:
	Circle();
	Circle(const int x, const int y, const MyString& Fill, const int R);
	Circle(const Circle& C);
	Circle& operator=(const Circle& C);
	~Circle();
	void SetRadius(const int R);
	void Print()const override;
	int GetRadius()const;
	virtual Shape* clone()const override;
	virtual bool WithinCircle(const int X,const  int Y,const  int R)const override;
	virtual bool WithinRect(const int X, const int Y, const int Width,const int Heigth) const override;
	virtual bool PointIn(const int X, const int Y)const override;
	virtual double GetArea()const;
	virtual double GetPerimeter()const;
	virtual const char* GetType()const;
	virtual void svgel(std::ofstream& ostr)const;
};
