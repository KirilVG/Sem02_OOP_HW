#include "Line.hpp"
#include "Circle.hpp"
#include <iostream>
#include "Rectangle.hpp"

const int invalid = -1;
const char* lineastype = "Line";

void Line::SetX2(int NewX) {
	if (NewX < 0)
	{
		x2 = -NewX;
	}
	else
	{
		x2 = NewX;
	}
}
void Line::SetY2(int NewY) {
	if (NewY < 0)
	{
		y2 = -NewY;
	}
	else
	{
		y2 = NewY;
	}
}
int Line::GetX2()const {
	return x2;
}
int Line::GetY2()const {
	return y2;
}
Line::Line()
	:Shape()
{
	SetX2(0);
	SetY2(0);
}
Line::Line(const Line& L)
	:Shape(L)
{
	x2 = L.x2;
	y2 = L.y2;
}
Line& Line::operator=(const Line& L)
{
	if (this != &L)
	{
		Shape::operator=(L);
		x2 = L.x2;
		y2 = L.y2;
	}
	return *this;
}
Line::~Line()
{
}
Line::Line(const int X, const int Y, const int X2, const int Y2, const MyString& Fill) 
	:Shape(X,Y,Fill)
{
	SetX2(X2);
	SetY2(Y2);
}
void Line::Print() const{
	std::cout << "Line " << x << " " << y << " " << x2 << " " << y2 <<" "<< fill.GetValue() << std::endl;
}
Shape* Line::clone()const
{
	return new Line(*this);
}
bool Line::WithinCircle(const int X, const int Y, const int R)const
{
	Circle C(X, Y, "", R);
	//check if both ends of the line are within the circle
	return C.PointIn(x, y) && C.PointIn(x2, y2);
}
bool Line::WithinRect(const int X, const int Y, const int Width, const int Heigth) const
{
	Rectangle R(X,Y,"", Width, Heigth);
	//check if both ends of the line are within the rectangle
	return R.PointIn(x, y) && R.PointIn(x2, y2);
}
bool Line::PointIn(const int X, const int Y)const
{
	//check if the point belongs to the geometric equasin of the line
	double k = (X - x) / (x2 - x);
	return Y == y + k * (y2 - y);
}
double Line::GetArea()const
{
	return invalid;
}
double Line::GetPerimeter()const
{
	return invalid;
}
const char* Line::GetType()const
{
	return lineastype;
}
void Line::svgel(std::ofstream& ostr)const
{
	if (ostr.is_open())
	{
		//output the line as a svg element
		ostr << "<line x1=\"" << x << "\" y1=\"" << y << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" />\n";
	}
}