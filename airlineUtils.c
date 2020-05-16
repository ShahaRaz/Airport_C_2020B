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
	pAL->lastIndexFilledInFlightsPtrArray = -1;
	pAL->numOfPlanes = cNumOfPlanes;
	Flight** ptrToArr = (Flight**)malloc(sizeof(Flight*) * INITIAL_FLIGHTS_SIZE); 
	if (ptrToArr == NULL) return NULL;
	pAL->allFlights = ptrToArr;
	pAL->FlightArrCapacity = INITIAL_FLIGHTS_SIZE;
	return pAL;
}

int addFlightToAirLine(AirLine* a1,const Flight* f1) {
	// check if array is full
	// 1.check if we have place
	//			if we dont  - reallocate  (Free up memory)
	// 2. insert pointer to array as element in flight** array
	// 3. increment count of logical size array

	if (a1->lastIndexFilledInFlightsPtrArray == (a1->FlightArrCapacity-1)) // when capacity 10, index 9  - --is the limit.
		if (!enlargeFlightsArray(a1)) return -1; // rolling back bad allocation
	int IndexOfCorrentInsertion = a1->lastIndexFilledInFlightsPtrArray+1;
	a1->allFlights[IndexOfCorrentInsertion] = f1; // points to it. // why +1??? ?? TODO
	return ++(a1->lastIndexFilledInFlightsPtrArray); // incrment and return new number of flights

}

int enlargeFlightsArray(AirLine* a1) {
	int newSize = ENLARGE_FACTOR * a1->lastIndexFilledInFlightsPtrArray+1;
	 //Flight** tempArr = realloc(a1->allFlights, sizeof(Flight*) * newSize); //(void*)=4 size of pointer
	 //if (tempArr == NULL) return 0;
	 //freeFlightsptrArray(a1->allFlights);
	 // a1->allFlights = tempArr;
	a1->allFlights = (Flight**)realloc(a1->allFlights, sizeof(Flight*) * newSize); //(void*)=4 size of pointer

	 return 1;
}

int countCompanyFlightsFromAtoB(const AirLine* a1, char* flyFromA, char* flyToB) {
	return countFlightsFromAtoB(a1->allFlights, flyFromA, flyToB);
}

void printAirlineDetails(const AirLine* ourAirLine) {
	Flight* pFlight = (Flight*)ourAirLine->allFlights;
	for (size_t i = 0; i < ourAirLine->lastIndexFilledInFlightsPtrArray ; i++,pFlight++)
	{
		printFlightDetails((pFlight));
		
	}
}

void freeAirline(AirLine* a1) {
	Flight* pFlight = (Flight*)a1->allFlights[0];
	for (size_t i = 0; i < a1->lastIndexFilledInFlightsPtrArray; i++, pFlight++)
	{
		freeFlight(pFlight);

	}
}
