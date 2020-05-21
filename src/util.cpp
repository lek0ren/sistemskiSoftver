#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

char* stringToCharArray(std::string s, char *array)
{
    strcpy(array, s.c_str());
    return array;
}

