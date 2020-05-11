
#define INITIAL_AIRPORTS_SIZE 10
#define ENLARGE_FACTOR 2

#include "airportManagerUtils.h"
//Manager->allAirports  - needs to contain all airports (not pointers to them)// see how to fix

AirportManager* InitDataBase() {
	printf("___ start Airport Data Base ___\n");
	AirportManager* Manager = NULL;
	Manager = (AirportManager*)malloc(sizeof(AirportManager));
	if (Manager == NULL) return NULL;
	Manager->allAirportsCount = 0;
	// init airports array
	Manager->allAirports = NULL; 
	Manager->allAirports = (Airport*)malloc(sizeof(Airport) * INITIAL_AIRPORTS_SIZE); // check if works
	Manager->arrPsclSize = INITIAL_AIRPORTS_SIZE;

	return Manager;
}

void addAirportToProg(AirportManager *AirportDB, Airport insertMe) {
	struct airportManagers* pAPM = AirportDB;
	if (pAPM->allAirportsCount == pAPM->arrPsclSize) // if array is full
	{
		if (!enlargeAirPortsArray(pAPM)) {
			printf("No memory to enlarge array, process failed\n");
			return;
		}
	}
	pAPM->allAirports[pAPM->allAirportsCount] = insertMe;
	pAPM->allAirportsCount++;


}

int enlargeAirPortsArray(AirportManager *AirportDB) {
	struct airportManagers* pAPM = AirportDB; 
	int enlargmentFactor = (pAPM->arrPsclSize * ENLARGE_FACTOR);
	Airport* reAllocation = (Airport*)realloc(pAPM->allAirports, enlargmentFactor*sizeof(Airport));
	if (reAllocation == NULL) return 0;
	free(pAPM->allAirports); // release the memory
	pAPM->allAirports = reAllocation;
	pAPM->arrPsclSize = enlargmentFactor;
	return 1;
}

void printAllFlights(AirportManager *AirportDB)
{
	struct airportManagers* pAPM = AirportDB;
	for (int i = 0; i < pAPM->allAirportsCount; i++)
	{
		printPortDetails(pAPM->allAirports[i]);
	}
}

void freeDB(AirportManager *AirportDB) {
	struct airportManagers* pAPM = AirportDB; 
	free(pAPM->allAirports);

}