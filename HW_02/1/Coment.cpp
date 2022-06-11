#include "Coment.hpp"
#include "iostream"
#include "StringFunctions.hpp"
//constructor
Coment::Coment(const char* Author,const char* Content)
{
	SetAuthor(Author);
	SetContent(Content);
}
//sets the author
void Coment::SetAuthor(const char* Author) {
	int len = strlenth(Author);
	author = new char[len + 1];
	coppystr(Author, author);
}
//sets the content
void Coment::SetContent(const char* Content) {
	int len = strlenth(Content);
	content = new char[len + 1];
	coppystr(Content, content);
}
//returns the author
char* Coment::GetAuthor() const{
	return this->author;
}
//returns the content
char* Coment::GetContent() const{
	return this->content;
}
//destructor
Coment::~Coment()
{
}
//frees the memory used by the coment
void Coment::free() {
	delete[]content;
	delete[]author;
}
//default constructor
Coment::Coment() {
	author = nullptr;
	content = nullptr;
}
