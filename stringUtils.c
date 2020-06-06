
#include "stringUtils.h"
#define MAX_STRING_LENGTH 256
#define DATE_STRING_LENGTH 11

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4013) // gets dosn't fit for this ass


char getCharNOnewLine() {
	char input[10] = {0};
	int fuckCCompilerForThisError = gets(input);
	return input[0];
}

char* getStrExactLength() {
	char* pN;
	char input[MAX_STRING_LENGTH];
	gets(input);

	pN = _strdup(input);


	removeSpaces(pN);
	capitalizeFirstLetter(pN);

	return pN;

}

char* getStrExactLengthFromFile(FILE* f) {
	char temp[MAX_STRING_LENGTH];
	myGets(temp, MAX_STRING_LENGTH, f);
	return _strdup(temp);
	//if (!f) 
//	return NULL;
//char sentence[MAX_STRING_LENGTH], *pN;
//
//fgets(sentence, MAX_STRING_LENGTH, f); // dropeed & 
//pN = _strdup(sentence);
//return pN;
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

void removeSpaces(char* trimMe) {
	int i, j;
	for (i = 0; trimMe[i] == ' '; i++) {}
	int spacesCounter = 0;
	for (j = i; trimMe[j] != '\0'; j++) {
		trimMe[j - i] = trimMe[j];
		if (trimMe[j] == ' ' && (trimMe[j + 1] == ' ' || trimMe[j + 1] == '\0'))
			i++; // if found more than one space - jump over the rest.
	}
	if (trimMe[j - 1] == ' ')
		trimMe[j - 1] = trimMe[j];

}


char* getDate() {
	printf("insert date in next format 23/05/1995\n");
	char* date;
	date = getStrExactLength();
	while (checkDate(date) == 0) {
		printf("Use the next format : 23/05/2002\n");
		date = getStrExactLength();
	}
	return date;
} // modify 


int DateToInt(char* dateString, int* day, int* month, int* year) {
	char* input = dateString;
	int nDay = 0, nMonth = 0, nYear = 0; // new day
	if (strlen(input) != DATE_STRING_LENGTH - 1) return 0;
	int i = 0;
	for (i; i < 2; i++) {
		if (!isdigit(input[i]))return 0;
		if (i == 0)
			nDay += 10 * charToDigit(input[i]);
		else // i==1
			nDay += charToDigit(input[i]);
	}
	// _ _ 
	if (input[i] != 47) return 0; // ASCII -> [ '/' == 47 ] 
	i++;
	// _ _ /
	for (i; i < 5; i++) {
		if (!isdigit(input[i]))return 0;
		if (i == 3)
			nMonth += 10 * charToDigit(input[i]);
		else // i==4
			nMonth += charToDigit(input[i]);
	}
	// _ _ / _ _ 
	if (input[i] != 47) return 0;
	i++;
	// _ _ / _ _ /
	for (i; i < 10; i++) {
		if (!isdigit(input[i]))return 0;
	}
	nYear += 1000 * charToDigit(input[6]);

	nYear += 100 * charToDigit(input[7]);

	nYear += 10 * charToDigit(input[8]);

	nYear += charToDigit(input[9]);

	// _ _ / _ _ / _ _ _ _ GOOD
	*day = nDay;
	*month = nMonth;
	*year = nYear;
	return 1;
}


void intsToDate(int day, int month, int year, char* resultExtern) {
	snprintf(resultExtern, DATE_STRING_LENGTH, "%02d/%02d/%d", day, month, year);
}


char* intToChar(int TransformMe) {
	char retrnMe[DATE_STRING_LENGTH];
	snprintf(retrnMe, 5, "%d", TransformMe);
	return _strdup(retrnMe); // trims to right size
}

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
	do {
		printf("insert 3dig IATA:");
		IATA = getStrExactLength();
	} while (strlen(IATA) != 3);
	return IATA;
}

void copyString(char* source,char* destination)
{
	destination = _strdup(source);
	//int size1 = sizeof(source);
	//if (!(destination = (char*)malloc(sizeof(char)* size1))) //+1 is to make room for the NULL char that terminates C strings
	//{
	//	return;
	//}
	//strncpy(destination, source, size1);
	//note that '\0' is not included with Alpha, it is handled by strcpy
//do whatever with one.name
}

int charToDigit(char replaceMe) {
	return (int)replaceMe - 48;
}

char* myGets(char* buffer, int size, FILE* fp)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, fp))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}
// get from user using: 




