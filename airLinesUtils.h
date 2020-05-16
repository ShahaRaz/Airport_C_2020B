#include <stdio.h>
#include <stdlib.h>
#include "stringUtils.h"
#include "ArraylistUtils.h"
#include "flightUtils.h"



#ifndef __AirLine
#define __AirLine

struct Flight; 

typedef struct airLines {
	char* name;
	int numOfPlanes;
	int lastIndexFilledInFlightsPtrArray;
	Flight** allFlights;
	int FlightArrCapacity;
}AirLine;

#endif 


#ifndef  __Flight
#define	 __Flight

struct Airport;

typedef struct flights {
	Airport* flyFrom;
	Airport* flyTo;
	char dateOfTakeoff[11]; // dd/mm/yyyy + \0
	int hourOfTakeoff;
	float fligthVelocity; // MPH

}Flight;
#endif



#ifndef __airlinesUtils
#define __airlinesUtils
AirLine* AutomaticllyCreateAirline(char* cName, int cNumOfPlanes);
void printAirlineDetails(const AirLine* ourAirLine);
int addFlightToAirLine(AirLine* a1, const Flight* f1);
void freeAirline(AirLine* a1);
int addFlightToAirLine(AirLine* a1, const Flight* f1);
int enlargeFlightsArray(AirLine* a1);





#endif // !__airlinesUtils



