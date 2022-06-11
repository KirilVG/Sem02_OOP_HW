#include "Page.hpp"
#include "StringFunctions.hpp"
#include <iostream>


//constructor
Page::Page(/* args */)
{
    text = nullptr;
}
//destructor
Page::~Page()
{
   
}
//reads the page from the console
void Page::WritePage() {
    char newpage[100][100];
    int i = 0;
    for (; i < 100; ++i) {
        std::cin.getline(newpage[i], 100);
        if (samestr(":quit", newpage[i])) {
            break;
        }
    }
    int numberofcharacters = 0;
    for (int j = 0; j < i; j++) {
        for (int k = 0; newpage[j][k] != '\0'; ++k) {
            ++numberofcharacters;
        }
        ++numberofcharacters;
    }
    ++numberofcharacters;

    
    if (text != nullptr) {
        delete[] text;
    }
    text = new char[numberofcharacters];


    int counter = 0;
    for (int j = 0; j < i; j++) {

        for (int k = 0; newpage[j][k] != '\0'; ++k) {
            text[counter] = newpage[j][k];
            counter++;
        }
        text[counter] = '\n';
        counter++;
    }
    text[counter] = '\0';
}
//displays the page
void Page::PrintPage() const{
    std::cout << this->text;
}
//returns the text
char* Page::GetText() const{
    return this->text;
}
//reads the page from a file
void Page::WritePagefromfile(std::ifstream& bookfile) {
    char newpage[100][100];
    int i = 0;
    for (; i < 100; ++i) {
        bookfile.getline(newpage[i], 100);
        if (samestr(":quit", newpage[i])) {
            break;
        }
    }
    int numberofcharacters = 0;
    for (int j = 0; j < i; j++) {
        for (int k = 0; newpage[j][k] != '\0'; ++k) {
            ++numberofcharacters;
        }
        ++numberofcharacters;
    }
    ++numberofcharacters;


    if (text != nullptr) {
        delete[] text;
    }
    text = new char[numberofcharacters];


    int counter = 0;
    for (int j = 0; j < i; j++) {

        for (int k = 0; newpage[j][k] != '\0'; ++k) {
            text[counter] = newpage[j][k];
            counter++;
        }
        text[counter] = '\n';
        counter++;
    }
    text[counter] = '\0';
}
//frees the information used by the page
void Page::free() {
    delete[] text;
}