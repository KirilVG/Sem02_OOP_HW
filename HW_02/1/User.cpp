#include "User.hpp"
#include "StringFunctions.hpp"
#include "Book.hpp"
#include <iostream>


//sets the username
void User::SetUsername(const char* Username) {
	int len = strlenth(Username);
	username = new char[len + 1];
	coppystr(Username, username);
}
//sets the password
void User::SetPassword(const char* Password) {
	int len = strlenth(Password);
	password = new char[len + 1];
	coppystr(Password, password);
}
//returns the username
char* User::GetUsername() const{
	return username;
}
//returns the password
char* User::GetPassword() const{
	return password;
}
//returns the number of books the user har read
int User::GetNumberOfBooksRead() const{
	return numberofbooksreadorwritten[0];
}
//returns the number of books the user has written
int User::GetNumberOfBooksWritten() const{
	return numberofbooksreadorwritten[1];
}
//constructor with parameters
User::User(const char* Username, const char* Password)
{
	numberofbooksreadorwritten = new int[2];
	numberofbooksreadorwritten[0] = 0;
	numberofbooksreadorwritten[1] = 0;
	bookswritten = new Book[5];
	booksread = new Book[5];
	capacityifbokswritten = 5;
	capacityofbooksread = 5;
	SetPassword(Password);
	SetUsername(Username);
}
//adds a book to the booksread array
void User::ReadBook(const Book& book) {
	if (HasReadBook(book.GetTitle()) == -1) {
		if (numberofbooksreadorwritten[0] + 1 > capacityofbooksread) {
			enlargebooksread();
		}
		booksread[numberofbooksreadorwritten[0]] = book;
		++numberofbooksreadorwritten[0];
	}
}
//adds a book to the bookswritten array
void User::WriteBook(const Book& book) {
	if (numberofbooksreadorwritten[1] + 1 > capacityifbokswritten) {
		enlargebookswritten();
	}
	bookswritten[numberofbooksreadorwritten[1]] = book;
	++numberofbooksreadorwritten[1];
}
//returns -1 if the user has not read a book with the same name or the index of the book in the corresponding array if they have
int User::HasReadBook(const char*  booktitle) const{
	for (int i = 0; i < numberofbooksreadorwritten[0]; ++i) {
		if (samestr(booktitle, booksread[i].GetTitle())) {
			return i;
		}
	}
	return -1;
}
//returns -1 if the user has not written a book with the same name or the index of the book in the corresponding array if they have
int User::HasWrittenBook(const char* booktitle) const{
	for (int i = 0; i < numberofbooksreadorwritten[1]; ++i) {
		if (samestr(booktitle, bookswritten[i].GetTitle())) {
			return i;
		}
	}
	return -1;
}
//constructor with no parameters
User::User() {
	numberofbooksreadorwritten = new int[2];
	numberofbooksreadorwritten[0] = 0;
	numberofbooksreadorwritten[1] = 0;
	bookswritten = new Book[5];
	booksread = new Book[5];
	capacityifbokswritten = 5;
	capacityofbooksread = 5;
}
//destructor
User::~User()
{
	
}
//increase the cap of the booksread array
void User::enlargebooksread() {
	capacityofbooksread += 5;
	Book * newbooksread = new Book[capacityofbooksread];
	for (int i = 0; i < numberofbooksreadorwritten[0]; i++) {
		newbooksread[i] = booksread[i];
	}
	delete[] booksread;
	booksread = newbooksread;
}
//increase the cap of the bookswritten array
void User::enlargebookswritten() {
	capacityifbokswritten += 5;
	Book* newbookswritten = new Book[capacityifbokswritten];
	for (int i = 0; i < numberofbooksreadorwritten[1]; i++) {
		newbookswritten[i] = bookswritten[i];
	}
	delete[] bookswritten;
	bookswritten = newbookswritten;
}
//saves information about  the user in a file
void User::SaveToFile(std::ofstream& userfile)const {
	userfile << username << std::endl;
	userfile << password << std::endl;
	userfile << numberofbooksreadorwritten[0] << std::endl;
	for (int i = 0; i < numberofbooksreadorwritten[0]; ++i) {
		userfile << booksread[i].GetTitle() << std::endl;
	}
	userfile << numberofbooksreadorwritten[1] << std::endl;
	for (int i = 0; i < numberofbooksreadorwritten[1]; ++i) {
		userfile << bookswritten[i].GetTitle() << std::endl;
	}
}
//frees the memory used by the user
void User::free() {
	delete[] username;
	delete[] password;
	delete[] bookswritten;
	delete[] booksread;
	delete[] numberofbooksreadorwritten;
}