#include <iostream>
#include <fstream>

using namespace std;
// a function that splits a string by white spaces
void split(char *str, char tokens[100][100], int &tokenscounter)
{
    tokenscounter = 0;
    int charactercounter = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
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
// a function that checks if two strings have the same value
bool equalstrings(char str1[], char str2[])
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
// a function that parses a string to an intiger
int strToInt(char str[])
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
// a functon that parses a hex number(as a string) to an intiger
int hexChToInt(char str[])
{
    char hexstr[] = "0123456789ABCDEF";
    int newb = 0;
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++)
        counter++;
    for (int i = 0; str[i] != '\0'; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (hexstr[j] == str[i])
            {
                int mult = 1;
                for (int k = 0; k < counter - i - 1; k++)
                {
                    mult *= 16;
                }
                newb = newb + mult * j;
            }
        }
    }
    return newb;
}
int main()
{
    // declare kay variables
    char input[100];
    char filename[100];
    char bts[1000];
    int btscounter = 0;
    int tokenscounter = 0;
    char viewComand[] = "view";
    char changeComand[] = "change";
    char removeComand[] = "remove";
    char addComand[] = "add";
    char saveComand[] = "save";
    char tokens[100][100];

    // open a file
    cin.getline(filename, 100);
    ifstream binFile(filename, ios::binary);
    if (!binFile.is_open())
    {
        cout << "Could not oppen file" << endl;
        return 0;
    }
    cout << "File oppened successfuly" << endl;

    // store the bytes from the file as characters
    while (binFile.get(bts[btscounter]))
    {
        btscounter++;
    }
    binFile.close();

    // input command functionality
    while (cin.getline(input, 100))
    {
        // split the whole command into substrings
        split(input, tokens, tokenscounter);
        if (equalstrings(tokens[0], viewComand))
        {
            // print functionality
            if (btscounter > 0)
            {
                cout << hex << (int)bts[0];
                for (int i = 1; i < btscounter; i++)
                {
                    cout << " " << hex << (int)bts[i]; // display the characters as hex numbers
                }
                cout << endl;
                for (int i = 0; i < btscounter; i++)
                {
                    if ((bts[i] >= 'a' && bts[i] <= 'z') || (bts[i] >= 'A' && bts[i] <= 'Z'))
                        cout << bts[i] << " "; // display the characters
                    else
                    {
                        cout << ". "; // display the nivalid characters
                    }
                }
                cout << endl;
            }
        }
        else if (equalstrings(tokens[0], changeComand))
        {
            // edit functionality
            int pos = strToInt(tokens[1]);    // take the position
            int newb = hexChToInt(tokens[2]); // take the hex num as an intiger
            if (pos < btscounter)
            {
                bts[pos] = (char)newb; // change the character if the position is correct
            }
            else
            {
                cout << "incorect position" << endl;
            }
        }
        else if (equalstrings(tokens[0], removeComand))
        {
            // remove functionality
            if (btscounter > 0)
            {
                btscounter--;
            }
            else
            {
                cout << "Cannot execute the command. There are no more bytes" << endl;
            }
        }
        else if (equalstrings(tokens[0], addComand))
        {
            // add functionality
            int newb = hexChToInt(tokens[1]);
            bts[btscounter] = (char)newb;
            btscounter++;
        }
        else if (equalstrings(tokens[0], saveComand))
        {
            // save functionality
            ofstream ofile;
            if (tokenscounter > 1)
            {
                ofile.open(tokens[2], ios::binary);
            }
            else
            {
                ofile.open(filename, ios::binary);
            }
            if (!ofile.is_open()) // check if the file has oppened successfuly
            {
                cout << "could not oppen file" << endl;
            }
            else
            {
                ofile.write((const char *)&bts, sizeof(char) * btscounter);
            }

            ofile.close();
        }
        else
        {
            cout << "invalid comamnd" << endl;
        }
    }

    return 0;
}