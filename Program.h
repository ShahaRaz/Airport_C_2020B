#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



#include "stringUtils.h"
#include "stringUtils.h"
#include "flightUtils.h"
#include "airLinesUtils.h"
#include "airPortUtils.h"
#include "airportManagerUtils.h"
#include "flightUtils.h"
#include "airportManagerUtils.h"
#include "generalFunctions.h"




#ifndef __DateStruct
#define __DateStruct
typedef struct dates {
	int day;
	int month;
	int year;
}Date;
#endif // !__DateStruct

// Get Enum name Trick // (refers to airlineUtils's sort enum,placed here since cause compilation errors there.): 
#ifndef __sortNaming
#define __sortNaming
//usage example:
const char* flightsOrders[] = { "NotSorted","SortedByHour" ,"SotrtedByDate" ,"SortedBySpeed" };
//flightsOrder t = 2
//printf("seleted order is %s\n", flightsOrders[t]); -> sortedByDate
#endif // !sortNaming


#define _USE_GENERAL_VOID_FUNCTIONS


#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846

#ifndef __Program_funcs
#define __Program_funcs
void main();
void startMenu(AirportManager* airportDB, AirLine* ourAirLine);
void printsStartMenu();
int pAddAirportToDataBase(AirportManager* airportDB);
void add_data_to_DB(AirportManager* airportDB, AirLine* ourAirLine, Flight flightsArr[]);
void pAddFlightToCompany(AirportManager* airportDB, AirLine* ourAirLine);
int pAddAirportToDataBase(AirportManager* airportDB);
void pPrintAirlineDetails(const AirLine* ourAirLine);
void pPrintEntireDataBase(const AirportManager* airportDB);
void pPrintNumOfFlights(const AirportManager* airportDB, AirLine* ourAirLine);
void freeAll(AirportManager* airportDB, AirLine* ourAirLine);
void tests();
void testArrayList();
void testStringUtils();
void pSortFlightsInAirline(AirLine* ourAirLine);
void pSearchFlightByOrder(AirLine* ourAirLine);
void saveDataToFile(AirportManager* airportDB, AirLine* ourAirLine);
void addDataFromFiles(AirportManager* airportDB, AirLine* ourAirLine,
	char* airportDBFileName, char* CompanyBinaryfileName, Flight* flightsArr);

#endif // !__Program_funcs



