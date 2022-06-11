#include "Shape.hpp"
#include <iostream>

const int baseX = 0;
const int baseY = 0;

void Shape::SetX(const int X) {
	if (X < 0)
	{
		x = -X;
	}
	else
	{
		x = X;
	}
}
void Shape::SetY(const int Y) {
	if (Y < 0)
	{
		y = -Y;
	}
	else
	{
		y = Y;
	}
}
void Shape::SetFill(const MyString& Fill) {
	fill = Fill;
}
int Shape::GetX()const {
	return x;
}
int Shape::GetY()const {
	return y;
}
const MyString Shape::getFill()const {
	return fill;
}
Shape::~Shape()
{
}
Shape::Shape()
{
	x = baseX;
	y = baseY;
	fill = "";
}
Shape::Shape(const int X,const int Y,const  MyString &Fill) 
{
	x = X;
	y = Y;
	fill = Fill;
}
Shape::Shape(const Shape& S)
{
	x = S.x;
	y = S.y;
	fill = S.fill;
}
void Shape::translate(const int Vertical, const int Horizontal)
{
	//add vertical to y and horizonatl to x
	SetX( x += Horizontal);
	SetY(y += Vertical);
}