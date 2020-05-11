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
	int numOfFlights;
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


