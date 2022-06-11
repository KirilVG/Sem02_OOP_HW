#include "Student.hpp"

bool Student::setGrade(float grade) // a function that sets the grade of a student
{
    if (grade >= 2.0 && grade <= 6.0)
    {
        this->grade = grade;
        return true;
    }
    else
    {
        return false;
    }
}
bool Student::setEmail(char mail[]) // a function that sets the email of a student
{
    bool containsatsign = false;
    for (int i = 0; mail[i] != '\0'; i++)
    {
        if (mail[i] == '@')
        {
            containsatsign = true;
            break;
        }
    }
    if (containsatsign)
    {
        int counter = 0;
        for (; mail[counter] != '\0'; counter++)
        {
            this->email[counter] = mail[counter];
        }
        this->email[counter] = '\0';
        return true;
    }
    else
    {
        return false;
    }
}
bool Student::setGender(char gender[]) // a function that sets the gender of a student
{
    char male[] = "Male";
    char female[] = "Female";
    if (equalstrings(gender, male) || equalstrings(gender, female))
    {
        int counter = 0;
        for (; gender[counter] != '\0'; counter++)
        {
            this->gender[counter] = gender[counter];
        }
        this->gender[counter] = '\0';
        return true;
    }
    else
    {
        return false;
    }
}
bool Student::setAge(int age) // a function that sets the age of a student
{
    if (age >= 15 && age <= 65)
    {
        this->age = age;
        return true;
    }
    return false;
}
bool Student::setFn(int fn) // a function that sets the fn of a student
{
    this->fn = fn;
    return true;
}
bool Student::setName(char name[]) // a function that sets the name of a student
{
    int counter = 0;
    for (; name[counter] != '\0'; counter++)
    {
        this->name[counter] = name[counter];
    }
    this->name[counter] = '\0';
    return true;
}
char *Student::getName() // a function that returns the name of a student
{
    return this->name;
}
int Student::getFn() // a function that returns the fn of a student
{
    return this->fn;
}
int Student::getAge() // a function that returns the age of a student
{
    return this->age;
}
char *Student::getGender() // a function that returns the gender of a student
{
    return this->gender;
}
char *Student::getEmail() // a function that returns the email of a student
{
    return this->email;
}
float Student::getGrade() // a function that returns the grade of a student
{
    return this->grade;
}
bool Student::equalstrings(char str1[], char str2[]) // a function that checks if two strings have the same value
{

    int counter = 0;
    while (str1[counter] != '\0' && str2[counter] != '\0')
    {
        if (str1[counter] != str2[counter])
        {
            return false;
        }
        counter++;
    }
    if (str2[counter] != '\0' || str1[counter] != '\0')
        return false;
    return true;
}
void swapstudents(Student &a, Student &b) // a function that swaps 2 students
{
    Student st = a;
    a = b;
    b = st;
}
Student::Student(/* args */) // constructor
{
}

Student::~Student() // destructor
{
}