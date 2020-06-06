
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef __PRINT
#define __PRINT
#define PRINT(str) printf(#str "\n"); // printf("hey" "\n"); is ok
#endif


#ifndef __stringUtils
#define __stringUtils
char getCharNOnewLine();
char* getStrExactLength();
int capitalizeFirstLetter(char* changeMe);
char* getIATA();
char* getDate();
void removeSpaces(char* trimMe);
int DateToInt(char* dateString, int* day, int* month, int* year);
char* getStrExactLengthFromFile(FILE* f);
void copyString(char* source, char* destination);
char* intToChar(int TransformMe);
void intsToDate(int day, int month, int year, char* result);
int checkDate(char* input);
int charToDigit(char replaceMe);
char* myGets(char* buffer, int size, FILE* fp);

#endif // !__stringUtils
