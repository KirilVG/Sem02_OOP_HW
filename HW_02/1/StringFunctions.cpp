#include "StringFunctions.hpp"

//returns the length of a string
int strlenth(const char* sorce) {
    int len = 0;
    for (int i = 0; sorce[i] != '\0'; i++) {
        len++;
    }
    return len;
}

//coppies the value of one string into another
void coppystr(const char* sorce, char* dest) {
    int i = 0;
    for (; sorce[i] != '\0'; i++) {
        dest[i] = sorce[i];
    }
    dest[i] = '\0';
}
//checks if two strings havr the same value
bool samestr(const char* str1, const char* str2) {
    int i = 0;
    for (; str1[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    if (str2[i] != '\0') {
        return false;
    }
    return true;
}