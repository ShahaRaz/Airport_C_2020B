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

#ifndef __AirportUtils
#define __AirportUtils
void ManuallyaddNewAirport(Airport* pNuAirport);
int AutoaddNewAirport(char* name, char* country, char* IATAcode, float latitude, float longitude, Airport* pNuAirport);
int isAirPortsEq(const Airport* a1, const  Airport* a2);
int isAirportCodeFit(const Airport a1, const  char* checkIATAcode);
float deg2rad(float deg);
void printPortDetails(Airport aP);
void writeAirportToFile(FILE* f, const Airport* a1);
void readAirportFromFile(FILE* f, Airport* a1);
void printPortDetails_Void(const void* port);
float calcDistanceBetweenAirports(const Airport a1, const  Airport a2);
void freeAirport(Airport* a1);
#endif