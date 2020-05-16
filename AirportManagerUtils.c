
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

void addAirportToAirportManager(AirportManager *AirportDB, Airport insertMe) {
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



void printAllAirports(const AirportManager *airportDB)
{
	struct airportManagers* pAPM = airportDB;
	for (int i = 0; i < pAPM->allAirportsCount; i++)
	{
		printPortDetails(pAPM->allAirports[i]);
	}
}



Airport* findAirportByIATA(const AirportManager* airportDB ,const char* inIATA) {
	Airport* pAirport = (airportDB->allAirports); // point to first airport in array 
	char* correntAirport;
	 //run over all flights in database
	for (int i = 0; i < airportDB->allAirportsCount; i++,pAirport++) { // go to next airport
		correntAirport = pAirport->IATAcode;
		if (strcmp(correntAirport, inIATA)==0)	
			return pAirport;
	}
	//for (int i = 0; i < airportDB->allAirportsCount; i++) { // go to next airport
	//	correntAirport = airportDB->allAirports[i].IATAcode;
	//	if (strcmp(correntAirport, inIATA) == 0)
	//		return &airportDB->allAirports[i];
	//}



	return NULL;
} /// return and check function

void freeDB(AirportManager* airportDB) {
	Airport* pAirport = (airportDB->allAirports); // point to first airport in array 
	char* correntAirport;
	//run over all flights in database
	for (int i = 0; i < airportDB->allAirportsCount; i++, pAirport++) { // go to next airport
		free(pAirport);
		//	free(airportDB->allAirports[i]);

	} // check if works TODO

}