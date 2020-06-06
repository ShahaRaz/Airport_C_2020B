#include <stdio.h>
#include <stdlib.h>
#include "stringUtils.h"
#include "ArraylistUtils.h"
#include "flightUtils.h"
#include "generalFunctions.h"

#ifndef __SortEnums
#define __SortEnums
typedef enum {
	NotSorted ,
	SortedByHour , 
	SotrtedByDate  , 
	SortedBySpeed
	} flightsOrder;

#endif // !__SortEnums




#ifndef __AirLine
#define __AirLine

struct Flight; 

typedef struct airLines {
	char* name;
	int numOfPlanes;
	int lastIndexFilledInFlightsPtrArray; // also accicable by quering the arraylist for size (-1/+1) 
	flightsOrder orderBy;
	//__________________________
	//Flight** allFlights;
	//int FlightArrCapacity; delete if doesnt disturb
	//__________________________

	arraylist* allFlights; //arraylist_  : assert(l->size == 4) : remove(l, 1)  : insert(l, 2, c)   :  assert(arraylist_get(l, 0) == a)   :   arraylist_add(l, a);
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
void addFlightToAirLine(AirLine* a1, const Flight* f1);
void freeAirline(AirLine* a1);
void writeAirlineToBinaryFile(const AirLine* a1);
void readAirlineFromBinaryFile(AirLine* a1, FILE* f1, Flight* flightsArray, AirportManager* airportDB);
void sortFlights(AirLine* a1);
void printsSortMenu();
int compareHour(const void* hr1, const  void* hr2);
int compareDate(const void* date1, const  void* date2);
int compareSpeed(const void* speed1, const  void* speed2);
Flight* findFlightInArray(const AirLine* a1);
void createDemoFlight_Hour(Flight* f1);
void createDemoFlight_Date(Flight* f1);
void createDemoFlight_Speed(Flight* f1);
void addCopyOflightToAirLine(AirLine* a1, const Flight* f1);


#endif // !__airlinesUtils
