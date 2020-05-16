#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "airPortUtils.h"
#include "airportManagerUtils.h"


#ifndef  __Flight
#define	 __Flight

struct Airport;

typedef struct flights {
	Airport* flyFrom;
	Airport* flyTo;
	char *dateOfTakeoff; // dd/mm/yyyy + \0 , len=11
	int hourOfTakeoff;
	float fligthVelocity; // MPH

}Flight;
#endif

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


float CalcfligthTime(Flight* flight1);
int isFlightFromAtoB(Flight* f1, char* flyFrom, char* flyTo);
int countFlightsFromAtoB(Flight** arrOfpFlights, char* flyFromA, char* flyToB); 
Flight* manuallyCreateNewFlight();
char* setIATAofFlight(const AirportManager* airportDB);
void printFlightDetails(Flight* f1);
Flight* automaticllyCreateNewFlight(char* depIATA, char* arrIATA,
	char* dateOfTakeOff, int hourOfTakeOff, float flightVelocity, const AirportManager* airportDB);
void freeFlight(Flight* f1);
void freeFlightsptrArray(Flight** pfligthArr);