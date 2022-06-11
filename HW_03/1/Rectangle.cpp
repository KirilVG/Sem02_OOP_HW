#include "Rectangle.hpp"
#include "Circle.hpp"
#include <iostream>

const int baseWidth = 0;
const int baseHeight = 0;

Rectangle::Rectangle(int X, int Y, MyString Fill, int Width, int Height):Shape(X,Y,Fill)
{
	SetWidth(Width);
	SetHeight(Height);
}
Rectangle::Rectangle()
{
	SetWidth(baseWidth);
	SetHeight(baseHeight);
}
Rectangle::Rectangle(const Rectangle& R)
	:Shape(R)
{
	width = R.width;
	height = R.height;
}
Rectangle& Rectangle::operator=(const Rectangle& R)
{
	if (this != &R)
	{
		Shape::operator=(R);
		width = R.width;
		height = R.height;
	}
	return *this;
}
Rectangle::~Rectangle()
{
}
int Rectangle::GetWidth() {
	return width;
}
int Rectangle::GetHeight() {
	return height;
}
void Rectangle::SetWidth(int Width) {
	if (Width < 0) {
		width = -Width;
	}
	else {
		width = Width;
	}
}
void Rectangle::SetHeight(int Height) {
	if (Height < 0) {
		height = -Height;
	}
	else {
		height = Height;
	}
}
Shape* Rectangle::clone()const
{
	return new Rectangle(*this);
}
bool Rectangle::WithinCircle(const int X, const int Y, const int R)const
{
	Circle C(X, Y, "", R);
	//check if all points of the rectangle are within the circle
	return C.PointIn(x - width / 2, y - height / 2) && C.PointIn(x + width / 2, y + height / 2) && C.PointIn(x + width / 2, y - height / 2) && C.PointIn(x - width / 2, y + height / 2);
}
bool Rectangle::WithinRect(const int X, const int Y, const int Width, const int Heigth) const
{
	Rectangle R(X, Y,"", Width, Heigth);
	//check if all points of the rectangle are within the new rectangle
	return R.PointIn(x - width / 2, y - height / 2) && R.PointIn(x + width / 2, y + height / 2) && R.PointIn(x + width / 2, y - height / 2) && R.PointIn(x - width / 2, y + height / 2);
}
bool Rectangle::PointIn(const int X, const int Y)const
{
	//check if the coordinates of the the point are within the rectangle
	return ((x-width/2 <= X && X <= x + width/2) && (y-height/2 <= Y && Y <= y + height/2));
}
void Rectangle::Print()const
{
	std::cout << "Rectangle " << x << " " << y << " " << width << " " << height << " " << fill.GetValue() << std::endl;
}
double Rectangle::GetArea()const
{
	return width * height;
}
double Rectangle::GetPerimeter()const
{
	return 2 * width + 2 * height;
}
const char* Rectangle::GetType()const
{
	return "Rectangle";
}
void Rectangle::svgel(std::ofstream& ostr)const
{
	if (ostr.is_open())
	{
		//output the rectangle as an svg element
		ostr << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\"" << fill.GetValue() << "\"/>\n";
	}
}