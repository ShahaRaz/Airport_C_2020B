
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS



#ifndef __PRINT
#define __PRINT
#define PRINT(str) printf(#str "\n"); // printf("hey" "\n"); is ok
#endif

char* getStrExactLength();
int capitalizeFirstLetter(char* changeMe);
void removeSpaces(char* str);
void remove_spaces(char* str_trimmed, const char* str_untrimmed);
char* getIATA();
char* getDate();