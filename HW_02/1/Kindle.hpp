#pragma once
#include "Book.hpp"
#include "User.hpp"


class Kindle
{
	User* users;
	Book* books;
	int numberofbooks;
	int numberofusers;
	int usercapacity;
	int bookcapacity;
	User currentuser;
	char bookfilename[20];
	char userfilename[20];
	bool auseriscurrentlylogged;
public:
	Kindle();
	~Kindle();
	//runs the kindle
	void run();
private:

	//takes information sved in a file
	void ReadFromFile();

	//saves information in a file
	void SaveToFile()const;

	//sign up functionality
	void SignUp();

	//sign in functionality
	void SignIn();

	//Increase the capacity of the dinalic arrays
	void IncreaseBooksCap();
	void IncreaseUsersCap();

	//adds a book to the dinamic array
	void AddBookToLibrary(const Book& book);

	//sign out functionality
	void SignOut();

	//view functionality;
	void ViewBooks()const;

	//write functionality
	void WriteaBook();

	//read functionality
	void ReadaBook();

	//Returns the index of the book with the same title or -1 if it does not exist
	int FindBook(const char* title)const;

	//rate functionality
	void RateBook();

	//rates functionality
	void ViewRatings()const;

	//add page functionality;
	void AddPage();

	//coment functionality
	void Coment();

	//coments functionality
	void ViewComents()const;

	//frees all the data stored by the kindle
	void free();
};

