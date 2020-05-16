#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPortUtils.h"




#ifndef __AirportManager
#define __AirportManager

struct Airport;

typedef struct airportManagers {
	Airport* allAirports; // array of airports, not pointers to airport
	int arrPsclSize;
	int allAirportsCount;
} AirportManager;

#endif

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

AirportManager* InitDataBase();
void addAirportToAirportManager(AirportManager *AirportDB, Airport insertMe);
int enlargeAirPortsArray(AirportManager *AirportDB);
void freeDB(AirportManager *AirportDB);
void printAllAirports(AirportManager *AirportDB);
Airport* findAirportByIATA(const AirportManager* airportDB, const char* inIATA);