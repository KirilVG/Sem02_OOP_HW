#pragma once
#pragma once

class Student
{
private:
    char name[26];
    int fn;
    int age;
    char gender[10];
    char email[26];
    float grade;

public:
    Student(/* args */);
    ~Student();
    bool setGrade(float grade);
    bool setEmail(char mail[]);
    bool setGender(char gender[]);
    bool setAge(int age);
    bool setFn(int fn);
    bool setName(char name[]);
    char *getName();
    int getFn();
    int getAge();
    char *getGender();
    char *getEmail();
    float getGrade();

private:
    bool equalstrings(char str1[], char str2[]);
};
void swapstudents(Student &a, Student &b);
