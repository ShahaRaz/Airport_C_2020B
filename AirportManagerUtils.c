#include "airportManagerUtils.h"

#define INITIAL_AIRPORTS_SIZE 10
#define ENLARGE_FACTOR 2


AirportManager* InitDataBase() {
	printf("___ start Airport Data Base ___\n");
	AirportManager* Manager = NULL;
	Manager = (AirportManager*)malloc(sizeof(AirportManager));
	if (Manager == NULL) return NULL;
	Manager->allAirportsCount = 0;
	// init airports array
	Manager->allAirports = NULL;
	Manager->allAirports = (Airport*)malloc(sizeof(Airport) * INITIAL_AIRPORTS_SIZE);
	if (!Manager->allAirports)
		return NULL;
	Manager->arrPsclSize = INITIAL_AIRPORTS_SIZE;

	return Manager;
}

void addAirportToAirportManager(AirportManager* AirportDB, Airport insertMe) {
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

int enlargeAirPortsArray(AirportManager* AirportDB) {
	struct airportManagers* pAPM = AirportDB;
	int enlargmentFactor = (pAPM->arrPsclSize * ENLARGE_FACTOR);
	Airport* reAllocation = (Airport*)realloc(pAPM->allAirports, enlargmentFactor * sizeof(Airport));
	if (reAllocation == NULL) return 0;
	free(pAPM->allAirports); // release the memory
	pAPM->allAirports = reAllocation;
	pAPM->arrPsclSize = enlargmentFactor;
	return 1;
}



void printAllAirports(const AirportManager* airportDB)
{
#ifdef _USE_GENERAL_VOID_FUNCTIONS

	generalArrayFunction(airportDB->allAirports, airportDB->allAirportsCount, sizeof(Airport),
		printPortDetails_Void);

#else


	// V1 - working well 
	for (int i = 0; i < airportDB->allAirportsCount; i++)
	{
		printPortDetails(airportDB->allAirports[i]);
	}
#endif // _USE_GENERAL_VOID_FUNCTIONS
}



Airport* findAirportByIATA(const AirportManager* airportDB, const char* inIATA) {
	Airport* pAirport = (airportDB->allAirports); // point to first airport in array 
	if (airportDB == NULL) return NULL;
	char* correntAirport;
	//run over all flights in database
	for (int i = 0; i < airportDB->allAirportsCount; i++, pAirport++) { // go to next airport
		correntAirport = pAirport->IATAcode;
		if (strcmp(correntAirport, inIATA) == 0)
			return pAirport;
	}

	return NULL;
}

int writeManagerToFile(const AirportManager* airportDB) {
	FILE* f = fopen("airport_authority.txt", "w");

	if (f == NULL) {
		printf("Failed opening file.\n");
		return 0;
	}
	fprintf(f, "%d\n", airportDB->allAirportsCount);
	for (int i = 0; i < airportDB->allAirportsCount; i++)
	{
		writeAirportToFile(f, &(airportDB->allAirports[i]));
	}
	fclose(f);
	return 1;
	//fprintf(f,"%s,%d,%1f\n",)
}

int readManagerFromFile(FILE* f, AirportManager* airportDB) {
	if (!f) return 0;
	int airportsToAdd = 0, correntAirports = airportDB->allAirportsCount;
	fscanf(f, "%d\n",&airportsToAdd); // TODO check & 
	if (airportsToAdd == 0) 
		return 1; // didn't add, nothing to add.
	airportDB->allAirportsCount = correntAirports + airportsToAdd;
	Airport* temp = (Airport*)realloc(airportDB->allAirports, (airportDB->allAirportsCount * sizeof(Airport)));
	if (!temp) return 0;
	airportDB->allAirports = temp;


	for (int i = correntAirports; i <= airportDB->allAirportsCount; i++)
	{
		readAirportFromFile(f, &(airportDB->allAirports[i]));
	}
	return 1;

	 // WORKING  
	//if (!f) return 0;
	//fscanf(f, "%d\n", &airportDB->allAirportsCount); // TODO check & 
	//airportDB->allAirports = (Airport*)malloc(sizeof(Airport) * airportDB->allAirportsCount);
	//for (int i = 0; i < airportDB->allAirportsCount; i++)
	//{
	//	readAirportFromFile(f, &(airportDB->allAirports[i]));
	//}
	//return 1;


	//int airportsToAdd = 0, totalAirports = airportDB->allAirportsCount;
	//if (!f) return 0;
	//fscanf(f, "%d\n", &airportsToAdd); // TODO check & 
	//totalAirports += airportsToAdd;
	//Airport* temp = (Airport*)realloc(airportDB->allAirports, (totalAirports * sizeof(Airport)));
	//if (!temp)
	//	return 0;
	//airportDB->allAirports = temp;
	//for (int i = 0; i < airportsToAdd; i++)
	//{
	//	readAirportFromFile(f, &(airportDB->allAirports[i]));
	//}
	//return 1;



}





void freeDB(AirportManager* airportDB) {

	//run over all flights in database
	for (int i = 0; i < airportDB->allAirportsCount; i++) { // go to next airport
		printPortDetails(airportDB->allAirports[i]);
		freeAirport(&airportDB->allAirports[i]);
	}
	free(airportDB->allAirports);

}
