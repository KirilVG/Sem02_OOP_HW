#pragma once
#include "Book.hpp"
#include "iostream"
class User
{
	char* username;
	char* password;
	int* numberofbooksreadorwritten;
	Book* booksread;
	Book* bookswritten;
	int capacityifbokswritten;
	int capacityofbooksread;
public:
	//setters
	void SetUsername(const char* Username);
	void SetPassword(const char* Password);

	//constructors
	User(const char*Username,const char*Password);
	User();

	//destructor
	~User();

	//getters
	char* GetUsername()const;
	char* GetPassword()const;
	int GetNumberOfBooksRead()const;
	int GetNumberOfBooksWritten()const;

	//adds a book to the corresponding array
	void ReadBook(const Book& book);
	void WriteBook(const Book& book);

	//returns -1 if the user has not read/written a book with the same name ro the index of the book in the corresponding array if they have
	int HasReadBook(const char*booktitle)const;
	int HasWrittenBook(const char* booktitle) const;

	//save information about the user in a file
	void SaveToFile(std::ofstream &userfile)const;

	//free the memory used by the user
	void free();

private:
	//increase the cap of the corrresponding arrays
	void enlargebooksread();
	void enlargebookswritten();
};

