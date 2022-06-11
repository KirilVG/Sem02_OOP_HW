#include "MyString.hpp"
#include <iostream>

MyString::MyString(const char* newval)
{
	value = new char [chArlen(newval) + 1];
	chArcpy(value, newval);
}
const char* MyString::GetValue()const
{
	if(this!=nullptr)
	return value;
}
MyString::~MyString()
{
	delete[] value;
}
MyString& MyString::operator=(const MyString& newstr) {
	if (this != &newstr) {
		delete[] value;
		value = new char[chArlen(newstr.GetValue()) + 1];
		chArcpy(value, newstr.GetValue());
	}
	return *this;
}
bool MyString::operator==(const MyString& newstr) {
	if (GetLength() != newstr.GetLength()) {
		return false;
	}
	for (int i = 0; i < GetLength(); ++i) {
		if (value[i] != newstr.value[i]) {
			return false;
		}
	}
	return true;
}
bool MyString::operator==(const const char* newstr)
{
	if (GetLength() != chArlen(newstr)) {
		return false;
	}
	for (int i = 0; i < GetLength(); ++i) {
		if (value[i] != newstr[i]) {
			return false;
		}
	}
	return true;
}
int chArlen(const char* str)
{
	int counter;
	for (counter = 0; str[counter] != '\0' && str[counter]; counter++)
	{

	}
	return counter;
}
void chArcpy( char* dest, const char* sorce)
{
	int len = chArlen(sorce);
	for (int i = 0; i < len; i++)
	{
		dest[i] = sorce[i];
	}
	dest[len] = '\0';
}
int MyString::GetLength()const
{
	return chArlen(value);
}
MyString::MyString(const MyString& S)
{
	value = new char[chArlen(S.value) + 1];
	chArcpy(value, S.value);
}
MyString& MyString::operator=(const char* newstr)
{
	delete[] value;
	value = new char[chArlen(newstr) + 1];
	chArcpy(value, newstr);
	return *this;
}
MyString MyString::substring(const int pos1, const int pos2) const
{
	if (pos1 >= 0 && pos2 >= 0 && pos1 <= chArlen(value) && pos2 <= chArlen(value) && pos1 <= pos2)
	{
		char* word = new char[pos2 - pos1 + 2];
		int counter = 0;
		for (int i = pos1; i < pos2; i++)
		{
			word[counter] = value[i];
			++counter;
		}
		word[counter] = '\0';
		MyString str(word);
		delete[] word;
		return str;
	}
	else
	{
		std::cout << "did not fulfill substring requirements" << std::endl;
	}
}
int MyString::indexof(const char el,const int instance) const
{
	
	if (instance >= 1)
	{
		int instancesleft = instance;
		for (int i = 0; i < chArlen(value); i++)
		{
			if (value[i] == el)
			{
				if (instancesleft == 1)
				{
					return i;
				}
				else
				{
					instancesleft--;
				}
			}
		}
		return -1;
	}
	return -1;
}
//erace is not fully functional use at your own risk
void MyString::erace(const int pos1, const int pos2)
{
	if (pos1 >= 0 && pos2 >= 0 && pos1 <= chArlen(value) && pos2 <= chArlen(value) && pos1 <= pos2)
	{
		char* arr = new char[pos1 + chArlen(value) - pos2];
		
		int counter = 0;
		for (int i = 0; i < pos1; i++)
		{
			arr[counter++] = value[i];
		}
		
		for (int i = pos2+1; i < chArlen(value); i++)
		{
			arr[counter++] = value[i];
		}
		
		arr[counter] = '\0';
		
		delete[] value;
		value = arr;
		arr = nullptr;
	}
	else
	{
		std::cout << "erace did not full fill the requirements" << std::endl;
	}
}
int stringToInt(const char* str)
{
	bool negative = false;
	int num = 0;
	int counter = 0;
	if (str[0] == '-')
	{
		negative = true;
		counter++;
	}
	for (; str[counter] != '\0'; counter++)
	{
		if (str[counter] >= '0' && str[counter] <= '9')
			num = num * 10 + str[counter] - '0';
		else
		{
			return 0;
		}
	}
	if (negative)
		num *= -1;
	return num;
}
void split(MyString* &strings, const char* text,int&count, const char *element)
{
	MyString Text(text);
	int numberofstr = 1;
	for (int i = 0; i < chArlen(text); i++)
	{
		for (int j = 0; j < chArlen(element); j++)
		{
			if (text[i] == element[j])
			{
				numberofstr++;
				break;
			}
		}
	}
	strings = new MyString[numberofstr];
	
	count = numberofstr;

	int beginningcount = 0;
	int ind = 0;
	for (int i = 0; text[i] != '\0'; i++)
	{
		for (int j = 0; j < chArlen(element); j++)
		{
			if (text[i] == element[j])
			{
				MyString str(Text.substring(beginningcount, i));
				strings[ind] = str;
				beginningcount = i + 1;
				ind++;
				break;
			}
		}
	}
	MyString str(Text.substring(beginningcount, chArlen(text)));
	strings[ind] = str;
}
void MyString::operator+=(const char* str)
{
	char* newarr = new char[chArlen(value) + chArlen(str) + 1];
	int counter = 0;
	for (int i = 0;i< chArlen(value); i++)
	{
		newarr[counter++] = value[i];
	}
	for (int i = 0; i < chArlen(str); i++)
	{
		newarr[counter++] = str[i];
	}
	newarr[counter] = '\0';

	delete[] value;
	value = newarr;
	newarr = nullptr;
}
void MyString::operator+=(const MyString& str)
{
	char* newarr = new char[chArlen(value) + chArlen(str.GetValue()) + 1];
	int counter = 0;
	for (int i = 0;i< chArlen(value); i++)
	{
		newarr[counter++] = value[i];
	}
	for (int i = 0; i < chArlen(str.GetValue()); i++)
	{
		newarr[counter++] = str.GetValue()[i];
	}
	newarr[counter] = '\0';
	delete[] value;
	value = newarr;
	newarr = nullptr;
}