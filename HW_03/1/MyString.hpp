#pragma once

class MyString
{
	char* value;
public:
	int GetLength()const;
	const char* GetValue()const;
	MyString(const char* newval="");
	MyString(const MyString& S);
	MyString& operator=(const MyString& nwestr);
	MyString& operator=(const char* nwestr);
	void operator+=(const char*);
	void operator+=(const MyString& str);
	bool operator==(const MyString& nwestr);
	bool operator==(const const char* nwestr);
	MyString substring(const int pos1, const int pos2)const;
	int indexof(const char el,const int instance=1)const;
	void erace(const int pos1, const int pos2);
	~MyString();
};

//functions connected with strings
int stringToInt(const char* str);
int chArlen(const char* str);
void chArcpy(char* dest, const char* sorce);
void split(MyString* &strings, const char* text, int& count,const char* elements);