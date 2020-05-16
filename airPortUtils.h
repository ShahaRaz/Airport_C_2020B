#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846
#define IATA_CODE_LENGTH 3
#include <stdio.h>
#include <math.h>
#include "stringUtils.h"


#ifndef __Airport
#define __Airport
typedef struct airports {
	char* name;
	char* country;
	char* IATAcode;
	float latitude;
	float longitude;
} Airport;
#endif


Airport* ManuallyaddNewAirport();
Airport* AutoaddNewAirport(char* name, char* country, char* IATAcode, float latitude, float longitude);
int isAirPortsEq(Airport a1, Airport a2);
int isAirportCodeFit(Airport a1, char* checkIATAcode);
float calcDistanceBetweenAirports(Airport a1, Airport a2);
float deg2rad(float deg);
void printPortDetails(Airport aP);