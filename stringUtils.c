#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringUtils.h"
#define MAXSTRINGLENGTH 512


#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)



char* getStrExactLength() {
	char* pN;
	char input[MAXSTRINGLENGTH];
	gets(input);
	/*scanf("%s", &input);*/
	//
	//int length = strlen(input);
	//pN = (char*)malloc((length + 1) * sizeof(char));
	//if (!pN)
	//	return NULL;
	//strcpy(pN, input);
	//

	pN = _strdup(input);
	return pN;
}


int capitalizeFirstLetter(char* changeMe) {
	// call function after calling _removeSpaces_
	int asciVal = (int)changeMe[0];
	if (asciVal >= 65 && asciVal <= 90) return 1; 
	if (asciVal >= 97 && asciVal <= 122) {
		changeMe[0] = changeMe[0] - 32;
		return 1;
	}
	return 0; // ascii is not a char
	

}

void removeSpaces(char* str) {
	int i = 0, j = 0;
	while (str[i] != '\0' && str[i] ==' ' ) {
		if (str[i] == ' ') i++;
		while (j < i) {

	}

	}


}

void remove_spaces(char*  str_trimmed, const char*  str_untrimmed)
{
	while (isspace(*str_untrimmed)) str_untrimmed++; // spaces before sentnce

	while (*str_untrimmed != '\0')
	{
		

		
			if (!isspace(*str_untrimmed))
			{
				*str_trimmed = *str_untrimmed;
				str_trimmed++;
			}
			str_untrimmed++;


		
	
	}
	*str_trimmed = '\0';
}


char* getDate() {
	printf("insert date in next format 23/05/1995\n");
	char* date;
	date = getStrExactLength();
	while (checkDate(date)==0) {
		printf("Use the next format : 23/05/2002\n");
		date = getStrExactLength();
	}
	return date;
} // modify 

int checkDate(char* input) {
	char* pDate = input;
	if (strlen(pDate) != 10) return 0;
	int i = 0;
	for (i; i < 2; i++) {
		if (!isdigit(pDate[i]))return 0;
	}
	// _ _ 
	if (pDate[i] != 47) return 0; // ASCII -> [ '/' == 47 ] 
	i++;
	// _ _ /
	for (i; i < 5; i++) {
		if (!isdigit(pDate[i]))return 0;
	}
	// _ _ / _ _ 
	if (pDate[i] != 47) return 0;
	i++;
	// _ _ / _ _ /
	for (i; i < 10; i++) {
		if (!isdigit(pDate[i]))return 0; 
	}
	// _ _ / _ _ / _ _ _ _ GOOD
	return 1;
}

char* getIATA()
{
	char* IATA;
	do{
		printf("insert 3dig IATA:");
		IATA = getStrExactLength();
	} while (strlen(IATA) != 3);
	return IATA;
}
\


