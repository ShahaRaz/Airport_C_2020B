#include <stdio.h>
#include <string.h>
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
	int count = 0, len = strlen(str), i;
	char fixedString[MAXSTRINGLENGTH];


	//i pointing to first word
	do {
		//before word

		for (i = 0; str[i] == ' '; i++)

			for (i; str[i] != ' ' && str[i] != '\0'; i++) // jumping over corrent word
			{
				fixedString[count++] = str[i];
			}
		fixedString[count++] = ' ';
	} while (str[i] != '\0');


}
