#pragma once
#include <fstream>
class Page
{
private:
    char* text;
public:
    //constructor
    Page();

    //destructor
    ~Page();

    //reads the text from the console
    void WritePage();

    //displays the text on the console
    void PrintPage()const;

    //getter
    char* GetText()const;

    //reads the text from a file
    void WritePagefromfile(std::ifstream &bookfile);

    //frees the memory used by the page
    void free();
};