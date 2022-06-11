#pragma once

class Coment
{
	char* author;
	char* content;
public:
	//constructors
	Coment();
	Coment(const char* Author,const char * Content);
	//setters
	void SetAuthor(const char* Author);
	void SetContent(const char* Content);
	//getters
	char* GetAuthor()const;
	char* GetContent()const;
	//destructor
	~Coment();
	//frees the memory used by the coment
	void free();
private:


};
