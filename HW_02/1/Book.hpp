#pragma once
#include "Page.hpp"
#include "Coment.hpp"
#include <fstream>
class Book
{
	char* author;
	char* title;
	int* ratings;
	int numberofratings;
	int ratingscapacity;
	char** ratingsproviders;
	Page* pages;
	int numberofpages;
	int pagecapacity;
	Coment* coments;
	int numberofcoments;
	int comentcapacity;
public:
	//seters
	void SetTitle(const char* Title);
	void SetAuthor(const char* Author);

	//constructors
	Book();
	Book(const char* Author,const char* Title);

	//destructor
	~Book();

	//getters
	char* GetTitle() const;
	char* GetAuthor()const;

	//adds a page to a book
	void AddPage();
	void AddGivenPage(const Page& p);

	//adds a coment to a bok
	void AddComent(const char * Comentauthor);
	//displays the comets
	void ShowComents()const;

	//ads a rating to the book
	void RateBook(const int & r,const char*ratingauthor);
	//displays the ratings
	void ShowRatings()const;
	//returns the undex of the rating provider with the sam name or -1 of the book has not been rated by a user with this name 
	int HasBeenRatedBy(const char* name)const;

	//reed functionality
	void ReadMe() const;
	
	//saves the information about in a file
	void SaveToFile(std::ofstream &bookfile)const;
	//takes information about the book from a file
	void TakeContentsFromFile(std::ifstream& bookfile);

	//frees the data used by the book
	void free();
private:
	//increase the capacity of the arrays
	void enlargebook();
	void enlargecomentsec();
	void enlargeratings();
};

