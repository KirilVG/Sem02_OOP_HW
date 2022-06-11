#include "functions.hpp"

void strCoppy(char str1[], char str2[]) // a function that coppies the values of a string into another one
{
    int counter = 0;
    for (; str2[counter] != '\0'; counter++)
    {
        str1[counter] = str2[counter];
    }
    str1[counter] = '\0';
}
int stringtoint(char str[]) // afunction that converts a sting to an intiger
{
    bool negative = false;
    int num = 0;
    int counter = 0;
    if (str[0] == '-')
    {
        negative = true;
        counter++;
    }
    for (; str[counter] != '\0'; counter++)
    {
        if (str[counter] >= '0' && str[counter] <= '9')
            num = num * 10 + str[counter] - '0';
        else
        {
            return 0;
        }
    }
    if (negative)
        num *= -1;
    return num;
}
float stringtofloat(char str[]) // a function that converts a string to a float
{
    bool negative = false;
    int counter = 0;
    bool beforepoint = true;
    float num = 0.0;
    int devider = 1;
    if (str[0] == '-')
    {
        negative = true;
        counter++;
    }
    for (; str[counter] != '\0'; counter++)
    {
        if (str[counter] >= '0' && str[counter] <= '9')
        {
            num = num * 10 + str[counter] - '0';
            if (!beforepoint)
                devider *= 10;
        }
        else if (beforepoint && str[counter] == '.')
        {
            beforepoint = false;
        }
        else
        {
            return 0.0;
        }
    }
    num /= devider;
    if (negative)
        num *= -1;
    return num;
}

void split(char *str, char tokens[100][100], int &tokenscounter, bool byspace) // a function that splits a string(it is specific to this program) by whitespace ot '>' and '<' signs
{
    tokenscounter = 0;
    int charactercounter = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((byspace && str[i] == ' ' && tokenscounter < 3) || !byspace && (str[i] == '<' || str[i] == '>'))
        {
            tokens[tokenscounter][charactercounter] = '\0';
            tokenscounter++;
            charactercounter = 0;
        }
        else
        {
            tokens[tokenscounter][charactercounter] = str[i];
            charactercounter++;
        }
    }
    tokens[tokenscounter][charactercounter] = '\0';
}
bool equalstrings(char str1[], char str2[]) // a function that checks if two stings have the same value
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
bool highervalue(char str1[], char str2[]) // a function that checks if a string has a higher value than another sring
{
    int counter = 0;
    while (str1[counter] != '\0' && str2[counter] != '\0')
    {
        if (str1[counter] > str2[counter])
            return true;
        else if (str1[counter] < str2[counter])
            return false;
        counter++;
    }
    return false;
}