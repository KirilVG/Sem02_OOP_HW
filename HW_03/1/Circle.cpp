#include "Circle.hpp"
#include <iostream>
#include"Rectangle.hpp"


const int baser = 0;
const double pi = 3.14;
const char* circleasatype = "Circle";

Circle::Circle():Shape()
{
	SetRadius(baser);
}
Circle::Circle(const int X,const int Y, const MyString& Fill,const int R): Shape(X,Y,Fill)
{
	SetRadius(R);
}
void Circle::SetRadius(const int R) 
{
	if (R < 0) {
		radius = -R;
	}
	else {
		radius = R;
	}
}
int Circle::GetRadius()const 
{
	return radius;
}
Circle::~Circle()
{
}
Circle::Circle(const Circle& C)
	:Shape(C)
{
	radius = C.radius;
}
Circle& Circle::operator=(const Circle& C)
{
	if (this != &C)
	{
		Shape::operator=(C);
		radius = C.radius;
	}
	return *this;
}
void Circle::Print()const {
	std::cout << "Circle " << x << " " << y << " " << radius << " " << fill.GetValue() << std::endl;
}
Shape* Circle::clone()const
{
	return new Circle(*this);
}
bool Circle::WithinCircle(const int X, const int Y, const int R)const
{
	Circle C(X, Y, "", R);
	//check if the length between the two centers and the radius is less than the length of R
	return C.PointIn(x, y) && (R >= radius) && (R - radius) * (R - radius) >= ((X - x) * (X - x) + (Y - y) * (Y - y));
}
bool Circle::WithinRect(const int X, const int Y, const int Width, const int Heigth) const
{
	Rectangle R(X, Y, "", Width, Heigth);
	//check if the lowes, the heighest tha most left, and the most right point of the circle are within the rectangle
	return R.PointIn(x, y) && R.PointIn(x - radius, y) && R.PointIn(x + radius, y) && R.PointIn(x, y - radius) && R.PointIn(x, y + radius);
}
bool Circle::PointIn(const int X, const int Y)const
{
	//check if the distane between the center and the pount is less than the radius
	return (radius * radius) >= (((x - X) * (x - X) + (y - Y) * (y - Y)));
}
double Circle::GetArea()const
{
	double Area = pi * radius * radius;
	return Area;
}
const char* Circle::GetType()const
{
	return circleasatype;
}
double Circle::GetPerimeter()const
{
	double Perimeter = pi * 2 * radius;
	return Perimeter;
}
void Circle::svgel(std::ofstream& ostr)const
{
	if (ostr.is_open())
	{
		//output the circle in svg  format
		ostr<< "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << radius << "\" fill=\"" << fill.GetValue() << "\"/>\n";
	}
}