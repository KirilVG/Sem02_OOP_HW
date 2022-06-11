#include "Kindle.hpp"
#include "User.hpp"
#include "Book.hpp"
#include "StringFunctions.hpp"
#include <iostream>
#include <fstream>


//default constructor
Kindle::Kindle()
{
	coppystr("books.txt", bookfilename);
	coppystr("users.txt", userfilename);
	numberofbooks = 0;
	numberofusers = 0;
	books = new Book[5];
	users = new User[5];
	usercapacity = 5;
	bookcapacity = 5;
	auseriscurrentlylogged = false;
}

//destructor
Kindle::~Kindle()
{
	free();
}

//run the main functionality
void Kindle::run() {
	//take information from the designated files
	ReadFromFile();
	char comand[50];
	std::cout << "Input a comand." << std::endl;
	//take the input
	std::cin.getline(comand, 50);
	while (!samestr("close", comand)) {
		//execute the apropriate comand
		if (samestr("sign up", comand)) {
			SignUp();
		}
		else if(samestr("sign in",comand)) {
			SignIn();
		}
		else if (samestr("write", comand)) {
			if (auseriscurrentlylogged) {
				WriteaBook();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("read", comand)) {
			if (auseriscurrentlylogged) {
				ReadaBook();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("view", comand)) {
			if (auseriscurrentlylogged) {
				ViewBooks();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("sign out", comand)) {
			if (auseriscurrentlylogged) {
				SignOut();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("rate", comand)) {
			if (auseriscurrentlylogged) {
				RateBook();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("rates", comand)) {
			if (auseriscurrentlylogged) {
				ViewRatings();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("add page", comand)) {
			if (auseriscurrentlylogged) {
				AddPage();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}
		}
		else if (samestr("coment", comand)) {
			if (auseriscurrentlylogged) {
				Coment();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}

		}
		else if (samestr("coments", comand)) {
			if (auseriscurrentlylogged) {
				ViewComents();
			}
			else {
				std::cout << "You must first sign in." << std::endl;
			}

		}
		else if (samestr("save", comand)) {
			SaveToFile();

		}
		else {
			std::cout << "Incorrect comand."<<std::endl;
		}
		std::cout << std::endl;
		std::cout << "Input a comand." << std::endl;
		std::cin.getline(comand, 50);
	}
}
//takes information from specific files
void Kindle::ReadFromFile() {
	std::ifstream bookfile;
	bookfile.open(bookfilename);
	//check if the filestream is oppened
	if (bookfile.is_open()) {
		int nob;
		bookfile >> nob;
		//get the number of books to add
		bookfile.ignore();
		for (int i = 0; i < nob; ++i) {
			//reads a book from the file and adds it to the book array
			Book newb;
			newb.TakeContentsFromFile(bookfile);
			AddBookToLibrary(newb);
		}
	}
	else {
		std::cout << "Previous book records have not been found." << std::endl;
	}
	bookfile.close();

	std::ifstream userfile;
	userfile.open(userfilename);
	//check if the stream is oppened
	if (userfile.is_open()) {
		int nob;
		userfile >> nob;
		//get the number of users to add
		userfile.ignore();
		for (int i = 0; i < nob; ++i) {
			//reads a user from the file and adds it to the user array
			User newuser;
			char tokens[50];
			userfile.getline(tokens, 50);
			newuser.SetUsername(tokens);
			userfile.getline(tokens, 50);
			newuser.SetPassword(tokens);
			int number;
			userfile >> number;
			userfile.ignore();
			for (int i = 0; i < number; ++i) {
				userfile.getline(tokens, 50);
				int index = FindBook(tokens);
				if (index >= 0)newuser.ReadBook(books[index]);
			}
			userfile >> number;
			userfile.ignore();
			for (int i = 0; i < number; ++i) {
				userfile.getline(tokens, 50);
				int index = FindBook(tokens);
				if (index >= 0)newuser.WriteBook(books[index]);
			}

			if (numberofusers + 1 > usercapacity) {
				IncreaseUsersCap();
			}
			users[numberofusers] = newuser;
			++numberofusers;
			
		}
	}
	else {
		std::cout << "Previous user records have not been found." << std::endl;
	}
	userfile.close();

}
//save the information stored in the kindle
void Kindle::SaveToFile()const {
	std::ofstream bookfile;
	bookfile.open(bookfilename);
	//check if the file is oppen
	if (bookfile.is_open()) {
		bookfile << numberofbooks << std::endl;
		for (int i = 0; i < numberofbooks; ++i) {
			//save the information about the book in the file
			books[i].SaveToFile(bookfile);
		}
	}
	else {
		std::cout << "Could not save book records." << std::endl;
	}
	bookfile.close();

	std::ofstream userfile;
	userfile.open(userfilename);
	//check if the file is oppen
	if (userfile.is_open()) {
		userfile << numberofusers << std::endl;
		for (int i = 0; i < numberofusers; ++i) {
			//save the information about the user in a file
			users[i].SaveToFile(userfile);
		}
	}
	else {
		std::cout << "Could not save user records." << std::endl;
	}
	userfile.close();
}
//sign up functionality
void Kindle::SignUp() {
	User newuser;
	char tokens[50];
	//take the input
	std::cout << "Enter username:" << std::endl;
	std::cin.getline(tokens, 50);
	newuser.SetUsername(tokens);
	std::cout << "Enter password:" << std::endl;
	std::cin.getline(tokens, 50);
	newuser.SetPassword(tokens);

	if (numberofusers + 1 > usercapacity) {
		IncreaseUsersCap();
	}
	//add the user to the already existing users
	users[numberofusers] = newuser;
	++numberofusers;
	
}
//sign in functionality
void Kindle::SignIn() {
	char username[50];
	//take the input
	std::cout << "Enter username:" << std::endl;
	std::cin.getline(username, 50);
	char password[50];
	std::cout << "Enter password:" << std::endl;
	std::cin.getline(password, 50);
	int index = -1;
	//check if a user with te same username or password exist
	for (int i = 0; i < numberofusers; ++i) {
		if (samestr(users[i].GetUsername(), username) && samestr(users[i].GetPassword(), password)) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "Incorrect username or password" << std::endl;
	}
	else {
		currentuser = users[index];
		auseriscurrentlylogged = true;
		std::cout << username << " logged in sucessfuly." << std::endl;
	}
}
//increase the capacity of the book array
void Kindle::IncreaseBooksCap() {
	bookcapacity += 5;
	Book* newlibrary = new Book[bookcapacity];
	for (int i = 0; i < numberofbooks; i++) {
		newlibrary[i] = books[i];
	}
	delete[] books;
	books = newlibrary;
}
//increase the capacity of the user array
void Kindle::IncreaseUsersCap() {
	usercapacity += 5;
	User* newusers = new User[usercapacity];
	for (int i = 0; i < numberofusers; i++) {
		newusers[i] = users[i];
	}
	delete[] users;
	users = newusers;
}
//adds a book to the book array
void Kindle::AddBookToLibrary(const Book&book) {
	if (numberofbooks + 1 > bookcapacity) {
		IncreaseBooksCap();
	}
	books[numberofbooks] = book;
	++numberofbooks;
}
//sign out functonality
void Kindle::SignOut() {
	auseriscurrentlylogged = false;
}
//view functinality
void Kindle::ViewBooks() const{
	if (numberofbooks == 0) {
		std::cout << "There are no books yet." << std::endl;
	}
	else {
		for (int i = 0; i < numberofbooks; ++i) {
			std::cout << i+1 << " " << books[i].GetTitle() << " by " << books[i].GetAuthor() << std::endl;;
		}
	}
}
//return the index of a book wit hthe same title in the book array or -1 if it doesnt exist
int Kindle::FindBook(const char* title)const {
	for (int i = 0; i < numberofbooks; ++i) {
		if (samestr(title, books[i].GetTitle())) {
			return i;
		}
	}
	return -1;
}
//read functionality
void Kindle::ReadaBook() {
	//get the title of the book
	std::cout << "Enter the title of the book you want to read." << std::endl;
	char booktitle[50];
	std::cin.getline(booktitle, 50);
	int index = FindBook(booktitle);
	if (index == -1) {
		std::cout << "No such book exists." << std::endl;
	}
	else {
		//rad the book
		currentuser.ReadBook(books[index]);
		books[index].ReadMe();
	}
}
//comeny functionality
void Kindle::Coment() {
	char title[50];
	std::cout << "Input the title of the book you want to coment." << std::endl;
	std::cin.getline(title, 50);
	int index = FindBook(title);
	//check if the book exists
	if (index == -1) {
		std::cout << "No such book exists." << std::endl;
	}
	else {
		//check if the user has read this book
		if (currentuser.HasReadBook(title) == -1) {
			std::cout << "User can not coment a book they have not read." << std::endl;
		}
		else {
			//coment on the book
			books[index].AddComent(currentuser.GetUsername());
		}
		
	}
}
//coments functionality
void Kindle::ViewComents() const{
	char title[50];
	std::cout << "Input the title of the book you want to view the coments of." << std::endl;
	std::cin.getline(title, 50);
	int index = FindBook(title);
	//check if the book exists
	if (index == -1) {
		std::cout << "No such book exists." << std::endl;
	}
	else {
		//display the coments
		books[index].ShowComents();
	}
}
//write functionality
void Kindle::WriteaBook() {
	//create a book
	char tokens[50];
	std::cout << "Enter title:" << std::endl;
	std::cin.getline(tokens, 50);
	Book newb(currentuser.GetUsername(), tokens);
	int pagescount;
	std::cout << "Enter pages count:" << std::endl;
	//get the number of pages
	std::cin >> pagescount;
	std::cin.ignore();
	for (int i = 0; i < pagescount; ++i) {
		//add apage to the book
		newb.AddPage();
	}
	//register the book
	AddBookToLibrary(newb);
	currentuser.WriteBook(newb);
	currentuser.ReadBook(newb);
	std::cout << "Books successfuly created" << std::endl;
}
//rate functionality
void Kindle::RateBook() {
	char title[50];
	std::cout << "Input the title of the book you want to rate." << std::endl;
	std::cin.getline(title, 50);
	int index = FindBook(title);
	//check if the book exists
	if (index == -1) {
		std::cout << "No such book exists." << std::endl;
	}
	else {
		if (currentuser.HasWrittenBook(title)!=-1) {
			//check if the user is the author of the book
			std::cout << "A user can not rate a book they have written"<<std::endl;
		}
		else if (currentuser.HasReadBook(title)==-1) {
			//check if the user has read the book
			std::cout << "User can not rate a book they have not read." << std::endl;
		}
		else {
			//rate the book
			int score;
			std::cout << "Input the score you want to give." << std::endl;
			std::cin >> score;
			std::cin.getline(title, 2);
			books[index].RateBook(score, currentuser.GetUsername());
		}
	}
}
//rates functionality
void Kindle::ViewRatings() const{
	char title[50];
	std::cout << "Input the title of the book you want to rate." << std::endl;
	std::cin.getline(title, 50);
	int index = FindBook(title);
	//check if the book exists
	if (index == -1) {
		std::cout << "No such book exists." << std::endl;
	}
	else {
		//display the ratings
		books[index].ShowRatings();
	}
}
//add page functionality
void Kindle::AddPage() {
	char title[50];
	std::cout << "Input the title of the book you want to add a page to." << std::endl;
	std::cin.getline(title, 50);
	int index = FindBook(title);
	//check if the book exists
	if (index == -1) {
		std::cout << "No such book exists." << std::endl;
	}
	else {
		if (currentuser.HasWrittenBook(title) == -1) {
			//check if the user is the author of the book
			std::cout << "A user can not modify a book they have not written." << std::endl;
		}
		else {
			//modify the book
			books[index].AddPage();
		}
	}
}
//frees the memory used by the kindle
void Kindle::free() {
	for (int i = 0; i < numberofbooks; ++i) {
		books[i].free();
	}
	delete[] books;
	for (int i = 0; i < numberofusers; ++i) {
		users[i].free();
	}
	delete[] users;
}