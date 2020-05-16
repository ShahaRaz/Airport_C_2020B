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





#define M_PI 3.14159265358979323846

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#ifndef __Program_funcs
#define __Program_funcs
void main();
void startMenu(AirportManager* airportDB, AirLine* ourAirLine);
void printsStartMenu();
int pAddAirportToDataBase(AirportManager* airportDB);
void add_data_to_DB( AirportManager* AirportDB);
void testStringUtils();
void pAddFlightToCompany(AirportManager* airportDB, AirLine* ourAirLine);
int pAddAirportToDataBase(AirportManager* airportDB);
void pPrintAirlineDetails(const AirLine* ourAirLine);
void pPrintEntireDataBase(const AirportManager* airportDB);
void pPrintNumOfFlights(const AirportManager* airportDB, const AirLine* ourAirLine);
void freeAll(AirportManager* airportDB, AirLine* ourAirLine);

#endif // !__Program_funcs



