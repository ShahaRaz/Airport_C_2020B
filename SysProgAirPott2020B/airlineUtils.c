#include "airLinesUtils.h"

#define INITIAL_FLIGHTS_SIZE 10
#ifndef ENLARGE_FACTOR
#define ENLARGE_FACTOR 2
#endif// !ENLARGE_FACTOR

AirLine* ManuallyCreateAirline() {
	printf("hey, let's create airline ");
	printf("Insert Companie's name:\n");
	char* cName = getStrExactLength();
	int cNumOfPlanes;
	printf("Insert number of planes:\n");
	scanf("%d", &cNumOfPlanes);
	
	return AutomaticllyCreateAirline(cName,cNumOfPlanes);
}

AirLine* AutomaticllyCreateAirline(char* cName,int cNumOfPlanes) {
	AirLine* pAL = NULL;
	pAL = (AirLine*)malloc(sizeof(AirLine));
	if (pAL == NULL) return NULL;
	pAL->name = cName;
	pAL->numOfFlights = 0;
	pAL->numOfPlanes = cNumOfPlanes;
	Flight** ptrToArr = (Flight**)malloc(sizeof(void*) * INITIAL_FLIGHTS_SIZE); //(void*)=4 size of pointer
	if (ptrToArr == NULL) return NULL;
	pAL->allFlights = ptrToArr;
	pAL->FlightArrCapacity = INITIAL_FLIGHTS_SIZE;
	return pAL;
}

int addFlightToAirLine(AirLine* a1,const Flight* f1) {
	if (a1->numOfFlights == a1->FlightArrCapacity)
		if (!enlargeFlightsArray(a1)) return 0; // rolling back bad allocation
	a1->allFlights[a1->numOfFlights + 1] = f1; // points to it.
}

int enlargeFlightsArray(AirLine* a1) {
	int newSize = ENLARGE_FACTOR * a1->numOfFlights;
	 Flight** tempArr = realloc(a1->allFlights, sizeof(int) * newSize); //(void*)=4 size of pointer
	 if (tempArr == NULL) return 0;
	 a1->allFlights = tempArr;
	 return 1;
}

int countCompanyFlightsFromAtoB(const AirLine* a1, char* flyFromA, char* flyToB) {
	return countFlightsFromAtoB(a1->allFlights, flyFromA, flyToB);
}