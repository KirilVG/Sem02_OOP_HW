#pragma once
#include "MyString.hpp"
#include "Shape.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include <fstream>

class APPengine
{
	Shape** shapes;
	int numberofshapes;
	int shapescap;
	MyString currentfilepath;
public:
	APPengine();
	~APPengine();
	void Run();
private:
	void AddLine(const Line & L);
	void AddCircle(const Circle &C);
	void AddRectangle(const Rectangle& R);
	void print() const;
	void Create(MyString * tokens,const int tcount);
	void Erase(MyString* tokens,const int tcount);
	void Within(MyString* tokens, const int tcount)const;
	void PointIn(MyString* tokens, const int tcount)const;
	void Areas()const;
	void Pers()const;
	void takefromfile(MyString* tokens, const int tcount);
	void savetofile(MyString* tokens, const int tcount);
	void resize();
	void translate(MyString* tokens, const int tcount);
	void freememory();
};
