#include "Book.hpp"
#include "StringFunctions.hpp"
#include "Page.hpp"
#include <iostream>
#include <fstream>


//sets the title of the book
void Book::SetTitle(const char* Title) {
	int len = strlenth(Title);
	title = new char[len + 1];
	coppystr(Title, title);
}
//tets the author of the book
void Book::SetAuthor(const char* Author) {
	int len = strlenth(Author);
	author = new char[len + 1];
	coppystr(Author, author);
}
//constructor
Book::Book() {
	author = nullptr;
	title = nullptr;
	numberofpages = 0;
	pages = new Page[5];
	pagecapacity = 5;
	coments = new Coment[5];
	comentcapacity = 5;
	numberofcoments = 0;
	ratings = new int[5];
	ratingscapacity = 5;
	numberofratings = 0;
	ratingsproviders = new char * [5];
}
//rate functionality
void Book::RateBook(const int& r, const char* ratingauthor) {
	//check if a user with the same name has rated this book
	int index = HasBeenRatedBy(ratingauthor);
	int score;
	if (r < 0) {
		score = 0;
	}
	else if (r > 10) {
		score = 10;
	}
	else {
		score = r;
	}
	if (index == -1) {
		//add a new rating
		if (numberofratings + 1 > ratingscapacity) {
			enlargeratings();
		}
		ratings[numberofratings] = score;
		int len = strlenth(ratingauthor);
		ratingsproviders[numberofratings] = new char[len + 1];
		coppystr(ratingauthor, ratingsproviders[numberofratings]);

		++numberofratings;
	}
	else {
		//change the previous rating
		ratings[index] = score;
	}
}
//returns the undex of the rating provider with the sam name or -1 of the book has not been rated by a user with this name
int Book::HasBeenRatedBy(const char* name)const {
	
	for (int i = 0; i < numberofratings; i++) {
		if (samestr(name, ratingsproviders[i])) {
			return i;
		}
	}
	return -1;
}
//displays the ratings
void Book::ShowRatings() const{
	for (int i = 0; i < numberofratings; i++) {
		std::cout << ratingsproviders[i] << " rated " << ratings[i] << " stars." << std::endl;
	}
	if (numberofratings <= 0) {
		std::cout << "This book has not been rated yet." << std::endl;
	}
}
//constructor with parameters
Book::Book(const char* Author, const char* Title) {
	SetAuthor(Author);
	SetTitle(Title);
	numberofpages = 0;
	pages = new Page[5];
	pagecapacity = 5;
	coments = new Coment[5];
	comentcapacity = 5;
	numberofcoments = 0;
	ratingsproviders = new char* [5];
}
//returns the title
char* Book::GetTitle()const {
	return title;
}
//returns the author
char* Book::GetAuthor() const {
	return author;
}
//destructor
Book::~Book()
{

}
//adds a page to the book
void Book::AddPage() {
	//create a new page
	Page newp;
	newp.WritePage();
	if (numberofpages + 1 > pagecapacity) {
		//increase the pages array
		enlargebook();
	}
	//adds the new page
	pages[numberofpages] = newp;
	numberofpages++;

}
//adds an existing page to the page array
void Book::AddGivenPage(const Page & p) {
	
	if (numberofpages + 1 > pagecapacity) {
		//increases the page array
		enlargebook();
	}
	//adds the page to the array 
	pages[numberofpages] = p;
	numberofpages++;

}
//read functionality
void Book::ReadMe() const {
	
	if (numberofpages > 0) {
		char c;
		int currentpage = 0;
		pages[currentpage].PrintPage();
		//get the token
		std::cin >> c;
		std::cin.ignore();
		while (c != 'q') {
			if (c == 'p') {
				//check if this is the firat page or the last
				if (currentpage - 1 < 0) {
					std::cout << "This is the first page." << std::endl;
				}
				else {
					--currentpage;
					//display the new page
					pages[currentpage].PrintPage();
				}
			}
			else if (c == 'n') {
				if (currentpage + 1 == numberofpages) {
					std::cout << "This is the last page." << std::endl;
				}
				else {
					++currentpage;
					//display the new page
					pages[currentpage].PrintPage();
				}
			}
			else
			{
				//display error message
				std::cout << "Incorrect token." << std::endl;
			}
			std::cin >> c;
			std::cin.ignore();
		}
		
	}
	else {
		std::cout << "This book has no pages." << std::endl;
	}
	
}
//add a coment
void Book::AddComent(const char* Comentauthor) {
	//increase the coment array
	if (numberofcoments + 1 > comentcapacity) {
		enlargecomentsec();
	}
	char coment[100];
	std::cout << "Input message:" << std::endl;
	std::cin.getline(coment, 100);
	//create a new coment and add it to the coment array
	coments[numberofcoments] = Coment(Comentauthor,coment);
	++numberofcoments;
}
//displays the coments
void Book::ShowComents() const {
	for (int i = 0; i < numberofcoments; ++i) {
		std::cout << coments[i].GetAuthor() << " wrote: " << coments[i].GetContent() << std::endl;
	}
	if (numberofcoments <= 0) {
		std::cout << "This book has no coments." << std::endl;
	}
}
//increase the page array cap
void Book::enlargebook()
{
	pagecapacity += 5;
	Page* newpages = new Page[pagecapacity];
	for (int i = 0; i < numberofpages; i++) {
		newpages[i] = pages[i];
	}
	delete[] pages;
	pages = newpages;

}
//increase the coment array cap
void Book::enlargecomentsec() {
	comentcapacity += 5;
	Coment* newcoments = new Coment[comentcapacity];
	for (int i = 0; i < numberofcoments; i++) {
		newcoments[i] = coments[i];
	}
	delete[] coments;
	coments = newcoments;
}
//increase the ratings array cap and the ratingsproviders array cap
void Book::enlargeratings() {
	ratingscapacity += 5;
	int* newratings = new int[ratingscapacity];
	char** newraters = new char* [ratingscapacity];
	for (int i = 0; i < numberofratings; i++) {
		newratings[i] = ratings[i];
		newraters[i] = ratingsproviders[i];
	}
	delete[] ratings;
	delete[] ratingsproviders;
	ratings = newratings;
	ratingsproviders = newraters;
}
//take information about the book from a file
void Book::TakeContentsFromFile(std::ifstream& bookfile) {
	char tokens[50];
	bookfile.getline(tokens, 50);
	SetTitle(tokens);
	bookfile.getline(tokens, 50);
	SetAuthor(tokens);
	int number;
	//get the number of pages
	bookfile >> number;
	bookfile.ignore();
	for (int i = 0; i < number; ++i) {
		//read a page from file
		Page newp;
		newp.WritePagefromfile(bookfile);
		if (numberofpages + 1 > pagecapacity) {
			enlargebook();
		}
		//add the new page to the page array
		pages[numberofpages] = newp;
		numberofpages++;
	}
	//get the number of coments
	bookfile >> number;
	bookfile.ignore();
	char coment[100];
	for (int i = 0; i < number; ++i) {
		if (numberofcoments + 1 > comentcapacity) {
			enlargecomentsec();
		}
		//create a new coment and add it to the coment array
		bookfile.getline(tokens, 50);
		bookfile.getline(coment, 100);
		coments[numberofcoments] = Coment(tokens, coment);
		++numberofcoments;
	}
	//get the umber of rates
	bookfile >> number;
	bookfile.ignore();
	int score;
	for (int i = 0; i < number; ++i) {
		//create anew rating and add it to the rtings array and the name of the provider to the ratingproviders array
		bookfile >> score;
		bookfile.ignore();
		bookfile.getline(tokens, 50);
		if (numberofratings + 1 > ratingscapacity) {
			enlargeratings();
		}
		ratings[numberofratings] = score;
		int len = strlenth(tokens);
		ratingsproviders[numberofratings] = new char[len + 1];
		coppystr(tokens, ratingsproviders[numberofratings]);

		++numberofratings;
	}


}
//save the information about the book in a file
void Book::SaveToFile( std::ofstream& bookfile)const {
	bookfile << title << std::endl;
	bookfile << author << std::endl;
	bookfile << numberofpages << std::endl;
	for (int i = 0; i < numberofpages; ++i) {
		bookfile << pages[i].GetText();
		bookfile << ":quit" << std::endl;
	}
	bookfile << numberofcoments << std::endl;
	for (int i = 0; i < numberofcoments; ++i) {
		bookfile << coments[i].GetAuthor() << std::endl;
		bookfile << coments[i].GetContent() << std::endl;
	}
	bookfile << numberofratings << std::endl;
	for (int i = 0; i < numberofratings; ++i) {
		bookfile << ratings[i] << std::endl;
		bookfile << ratingsproviders[i] << std::endl;
	}
}
//free the memory used by the book
void Book::free() {
	delete[] author;
	delete[] title;
	for (int i = 0; i < numberofpages; ++i) {
		pages[i].free();
	}
	delete[] pages;
	for (int i = 0; i < numberofratings; ++i) {
		delete[] ratingsproviders[i];
	}
	delete[] ratingsproviders;
	delete[] ratings;
	for (int i = 0; i < numberofcoments; ++i) {
		coments[i].free();
	}
	delete[] coments;
}