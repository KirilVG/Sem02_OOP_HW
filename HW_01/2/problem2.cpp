#include <iostream>
#include <fstream>
#include "Student.hpp"
#include "functions.hpp"

using namespace std;

int main()
{
    // declare key variables
    Student students[100];
    int numberofstudents = 0;
    char filename[100];
    char input[100];
    char *studentsinp = new char[1000];
    char tokens[100][100];
    int tokenscounter = 0;
    char studentclosingtag[] = "\\student";
    char studenttag[] = "student";
    char nametag[] = "name";
    char fntag[] = "fn";
    char emailtag[] = "email";
    char agetag[] = "age";
    char gendertag[] = "gender";
    char gradetag[] = "grade";
    char editcomand[] = "edit";
    char sortcommand[] = "sort";
    char printcommand[] = "print";
    char savecommand[] = "save";

    // open file
    cin.getline(filename, 100);
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
    {
        cout << "could not oppen file" << endl;
        return 0;
    }
    cout << "file oppened successfuly" << endl;

    // get the text from the file
    char c;
    int studentsinpcounter = 0;
    while (infile.get(c))
    {

        studentsinp[studentsinpcounter] = c;
        studentsinpcounter++;
    }
    studentsinp[studentsinpcounter] = '\0';

    infile.close();

    split(studentsinp, tokens, tokenscounter, false);

    delete[] studentsinp;

    // save the info about the students into an array
    for (int i = 0; i < tokenscounter; i++)
    {

        if (equalstrings(tokens[i], studenttag))
        {
            i++;
            Student student;
            while (!equalstrings(tokens[i], studentclosingtag))
            {
                if (equalstrings(tokens[i], nametag))
                {
                    i++;
                    student.setName(tokens[i]);
                }
                else if (equalstrings(tokens[i], fntag))
                {
                    i++;
                    student.setFn(stringtoint(tokens[i]));
                }
                else if (equalstrings(tokens[i], emailtag))
                {
                    i++;
                    student.setEmail(tokens[i]);
                }
                else if (equalstrings(tokens[i], agetag))
                {
                    i++;
                    student.setAge(stringtoint(tokens[i]));
                }
                else if (equalstrings(tokens[i], gendertag))
                {
                    i++;
                    student.setGender(tokens[i]);
                }
                else if (equalstrings(tokens[i], gradetag))
                {
                    i++;
                    student.setGrade(stringtofloat(tokens[i]));
                }
                i++;
            }
            students[numberofstudents] = student;
            numberofstudents++;
        }
    }
    cout << endl;

    // take commands
    while (cin.getline(input, 100))
    {
        tokenscounter = 0;
        split(input, tokens, tokenscounter, true); // split the comand into substrings
        if (equalstrings(tokens[0], editcomand))
        {
            // edit functionality
            int index = 0;
            bool successful = false;
            int fn = stringtoint(tokens[1]);
            for (int i = 0; i < numberofstudents; i++)
            {
                if (students[i].getFn() == fn)
                {
                    index = i;
                    successful = true;
                }
            }
            if (successful)
            {
                if (equalstrings(tokens[2], nametag))
                {
                    successful = students[index].setName(tokens[3]);
                }
                else if (equalstrings(tokens[2], emailtag))
                {
                    successful = students[index].setEmail(tokens[3]);
                }
                else if (equalstrings(tokens[2], fntag))
                {
                    successful = students[index].setFn(stringtoint(tokens[3]));
                }
                else if (equalstrings(tokens[2], agetag))
                {
                    successful = students[index].setAge(stringtoint(tokens[3]));
                }
                else if (equalstrings(tokens[2], gradetag))
                {
                    successful = students[index].setGrade(stringtofloat(tokens[3]));
                }
                else if (equalstrings(tokens[2], gendertag))
                {
                    successful = students[index].setGender(tokens[3]);
                }
                else
                {
                    successful = false;
                }
            }
            if (successful)
            {
                cout << "Operation successfuly executed" << endl;
                cout << endl;
            }
            else
            {
                cout << "Error! Data not in correct format!" << endl;
                cout << endl;
            }
        }
        else if (equalstrings(tokens[0], printcommand))
        {
            // print functionality
            cout << endl;
            for (int i = 0; i < numberofstudents; i++)
            {
                cout << "Student fn - " << students[i].getFn() << endl;
                cout << "name - " << students[i].getName() << endl;
                cout << "age - " << students[i].getAge() << endl;
                cout << "gender - " << students[i].getGender() << endl;
                cout << "grade - " << students[i].getGrade() << endl;
                cout << "email - " << students[i].getEmail() << endl;
                cout << endl;
            }
        }
        else if (equalstrings(tokens[0], sortcommand))
        {
            // sort functionality
            bool successful = false;
            if (equalstrings(tokens[1], nametag) || equalstrings(tokens[1], fntag) || equalstrings(tokens[1], agetag) || equalstrings(tokens[1], gendertag) || equalstrings(tokens[1], gradetag) || equalstrings(tokens[1], emailtag))
            {
                successful = true;
                for (int i = 0; i < numberofstudents; i++)
                {
                    for (int j = i + 1; j < numberofstudents; j++)
                    {
                        if (equalstrings(tokens[1], nametag))
                        {
                            if (highervalue(students[i].getName(), students[j].getName()))
                            {
                                swapstudents(students[i], students[j]);
                            }
                        }
                        else if (equalstrings(tokens[1], fntag))
                        {
                            if (students[i].getFn() > students[j].getFn())
                            {
                                swapstudents(students[i], students[j]);
                            }
                        }
                        else if (equalstrings(tokens[1], agetag))
                        {
                            if (students[i].getAge() > students[j].getAge())
                            {
                                swapstudents(students[i], students[j]);
                            }
                        }
                        else if (equalstrings(tokens[1], gendertag))
                        {
                            if (highervalue(students[i].getGender(), students[j].getGender()))
                            {
                                swapstudents(students[i], students[j]);
                            }
                        }
                        else if (equalstrings(tokens[1], gradetag))
                        {
                            if (students[i].getGrade() > students[j].getGrade())
                            {
                                swapstudents(students[i], students[j]);
                            }
                        }
                        else if (equalstrings(tokens[1], emailtag))
                        {
                            if (highervalue(students[i].getEmail(), students[j].getEmail()))

                            {

                                swapstudents(students[i], students[j]);
                            }
                        }
                        else
                        {
                            cout << "incorrect tag" << endl;
                        }
                    }
                }
            }
            if (successful)
            {
                cout << "Operation successfuly executed" << endl;
                cout << endl;
            }
            else
            {
                cout << "Error! Data not in correct format!" << endl;
                cout << endl;
            }
        }
        else if (equalstrings(tokens[0], savecommand))
        {
            // save functionality
            ofstream ofile;
            ofile.open(filename);
            if (ofile.is_open())
            {
                for (int i = 0; i < numberofstudents; i++)
                {
                    ofile << "<student>" << endl;
                    ofile << "    <name>" << students[i].getName() << "<\\name>" << endl;
                    ofile << "    <fn>" << students[i].getFn() << "<\\fn>" << endl;
                    ofile << "    <age>" << students[i].getAge() << "<\\age>" << endl;
                    ofile << "    <gender>" << students[i].getGender() << "<\\gender>" << endl;
                    ofile << "    <email>" << students[i].getEmail() << "<\\email>" << endl;
                    ofile << "    <grade>" << students[i].getGrade() << "<\\grade>" << endl;
                    ofile << "<\\student>" << endl;
                    ofile << endl;
                }
                cout << "Operation successfuly executed" << endl;
                cout << endl;
            }
            else
            {
                cout << "Error! Data not in correct format!" << endl;
                cout << endl;
            }

            ofile.close();
        }
        else
        {
            cout << "incorrect input" << endl;
            cout << endl;
        }
    }
    return 0;
}