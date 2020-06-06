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

	return AutomaticllyCreateAirline(cName, cNumOfPlanes);
}

AirLine* AutomaticllyCreateAirline(char* cName, int cNumOfPlanes) {
	AirLine* pAL = NULL;
	pAL = (AirLine*)malloc(sizeof(AirLine));
	if (pAL == NULL) return NULL;
	pAL->name = cName;
	pAL->lastIndexFilledInFlightsPtrArray = -1;
	pAL->numOfPlanes = cNumOfPlanes;
	pAL->allFlights = arraylist_create();
	//pAL->FlightArrCapacity = INITIAL_FLIGHTS_SIZE;
	pAL->orderBy = 0; // mark not sorted
	return pAL;
}


void addFlightToAirLine(AirLine* a1, const Flight* f1) {
	arraylist_add(a1->allFlights, (void*)f1);
	a1->lastIndexFilledInFlightsPtrArray++;
	a1->orderBy = 0; // mark not sorted

}

void addCopyOflightToAirLine(AirLine* a1, const Flight* f1) {
	Flight* newFlight = (Flight*)malloc(sizeof(Flight)); // allocates space inside copyFlight
	if (!newFlight) return;
	copyFlight(f1, newFlight);

	arraylist_add(a1->allFlights, (void*)newFlight);
	a1->lastIndexFilledInFlightsPtrArray++;
	a1->orderBy = 0; // mark not sorted
}

int countCompanyFlightsFromAtoB(const AirLine* a1, char* flyFromA, char* flyToB) {
	int retVal = countFlightsFromAtoB(a1->allFlights, flyFromA, flyToB);
	if (retVal == -1)
		return 0;
	return retVal;
}

void printAirlineDetails(const AirLine* ourAirLine) {
	arraylist* flightsPtrArr = ourAirLine->allFlights;

	if (arraylist_size(flightsPtrArr) == 0)
	{
		return;
	}
	Flight* ptrToFlight;
	for (size_t i = 0; i < arraylist_size(flightsPtrArr); i++) {
		ptrToFlight = (Flight*)arraylist_get(flightsPtrArr, i);
		printFlightDetails(ptrToFlight);
	}
}

void writeAirlineToBinaryFile(const AirLine* a1) {//if send NULL -> create new file 
	FILE* f1 = fopen("company.bin", "wb");
	// W-> num of planes
	fwrite(&a1->numOfPlanes, sizeof(int), 1, f1);
	// W-> name
	int len1;
	len1 = strlen(a1->name) + 1;// +1 for '\0'
	fwrite(&len1, sizeof(int), 1, f1); // W-> length of name (for allocation purposes when reading later)
	fwrite(a1->name, sizeof(char), len1, f1);
	//W-> number of flights 
	int numOfFlights = a1->lastIndexFilledInFlightsPtrArray + 1;
	fwrite(&numOfFlights, sizeof(int), 1, f1);
	// W-> sorting ENUM
	int enumValue = (int)a1->orderBy; // casting to int (maybe shoudln't? TODO..
	fwrite(&enumValue, sizeof(int), 1, f1);
	Flight* tFlightPtr = NULL;
	//write all flights
	for (int i = 0; i < numOfFlights; i++)
	{
		tFlightPtr = (Flight*)arraylist_get(a1->allFlights, i);
		writeFlightToBinaryFile(tFlightPtr, f1);
	}
	// see how made the sorts, only then know how to write
	//TODO

	fclose(f1); // else - the function opend the file, needs to close it
}
////// ________________________________________________________________________
void readAirlineFromBinaryFile(AirLine* a1, FILE* f1, Flight* flightsArray, AirportManager* airportDB) {

	if (!f1)
		return;
	// read num of planes 
	fread(&a1->numOfPlanes, sizeof(int), 1, f1);
	// read name 
	int len1;
	fread(&len1, sizeof(int), 1, f1);
	a1->name = (char*)malloc(sizeof(char) * len1);
	fread(a1->name, len1, 1, f1);
	//read number of flighs
	int flightsToAdd = 0;
	fread(&flightsToAdd, sizeof(int), 1, f1);
	// read sorting enum
	fread(&a1->orderBy, sizeof(int), 1, f1);

	flightsArray = (Flight*)malloc(sizeof(Flight) * flightsToAdd);

	if (flightsArray == NULL)
		return;
	for (int i = 0; i < flightsToAdd; i++)
	{
		readFlightFromBinaryFile(f1, &flightsArray[i], airportDB);
		addFlightToAirLine(a1, &flightsArray[i]);
	}

}

void sortFlights(AirLine* a1) {
	// void* ===== Flight*
	int flag = 0;
	char userInput;
#	ifdef _USE_GENERAL_VOID_FUNCTIONS
	generalArrayFunction(a1->allFlights->body, a1->lastIndexFilledInFlightsPtrArray + 1, sizeof(Flight*),
		printFlightDetails_void);
#endif
	// Matching data types and pointers for qsort calls
	//Keta dohe lifaneha: 
	Flight* flightsArr = (Flight*)a1->allFlights->body; // from void** ---> Flight*
	void* flightsArr_withCostume = (void*)flightsArr; // Flight* ---> void*
	int arrSize = a1->lastIndexFilledInFlightsPtrArray + 1;
	//______________________

	do {
		printsSortMenu();
		userInput = getCharNOnewLine();
		switch (userInput) {
		case '1':
			qsort(flightsArr_withCostume, arrSize, sizeof(Flight*), compareHour);
			a1->orderBy = 1;
			break;
		case '2':
			qsort(flightsArr_withCostume, arrSize, sizeof(Flight*), compareDate);
			a1->orderBy = 2;
			break;
		case '3':
			qsort(flightsArr_withCostume, arrSize, sizeof(Flight*), compareSpeed);
			a1->orderBy = 3;
		default:
			printf("bad input, insert again\n");
		}
	} while (userInput != '3' && userInput != '2' && userInput != '1');

}
void printsSortMenu() {
	printf("Choose sort catagory:\n");
	printf("1. sort by Hour:\n");
	printf("2. sort by Date:\n");
	printf("3. sort by Speed:\n");
}
//comperators
int compareHour(const void* hr1, const  void* hr2) {
	Flight* f2 = *(Flight**)hr2;
	Flight* f1 = *(Flight**)hr1;


	const int n1 = f1->hourOfTakeoff;
	const int n2 = f2->hourOfTakeoff;

	if (n1 < n2) return -1;
	else if (n1 > n2) return 1;
	else return 0;
}

int compareDate(const void* date1, const  void* date2)
{
	Flight* f1 = *(Flight**)date1;
	Flight* f2 = *(Flight**)date2;
	int year1, month1, day1, year2, month2, day2;
	DateToInt(f1->dateOfTakeoff, &day1, &month1, &year1);
	DateToInt(f2->dateOfTakeoff, &day2, &month2, &year2);
	if (year1 < year2)
		return -1;
	else if (year1 > year2)
		return 1;
	else
	{ // same year
		if (month1 < month2)
			return -1;
		else if (month1 > month2)
			return 1;
		else
		{ // same month

			if (day1 < day2)
				return -1;
			else if (day1 > day2)
				return 1;
			else return 0; // same date
		}
	}
}

int compareSpeed(const void* speed1, const  void* speed2)
{
	Flight* f1 = *(Flight**)speed1;
	Flight* f2 = *(Flight**)speed2;

	float n1, n2;
	n1 = f1->fligthVelocity;
	n2 = f2->fligthVelocity;
	if (n1 < n2) return -1;
	else if (n1 > n2) return 1;
	else return 0;
}

Flight* findFlightInArray(const AirLine* a1) {
	if (a1->orderBy == 0)
		return NULL; // array is not sorted 

	// void* ====> Flight* 
	// Matching data types and pointers for qsort calls
	Flight* flightsArr = (Flight*)a1->allFlights->body; // from void** ---> Flight*
	void* flightsArr_withCostume = (void*)flightsArr; // Flight* ---> void*
	int arrSize = a1->lastIndexFilledInFlightsPtrArray + 1;
	//______________________

	void* demoWithCostume = NULL;
	Flight* found = NULL;
	void* result = NULL;
	//  if not allocating here, wouldn't be able to read later
	Flight* demoFlight = (Flight*)malloc(sizeof(Flight) * 1);
	int sortedBy = a1->orderBy;
	switch (sortedBy) {
	case 1:
		createDemoFlight_Hour(demoFlight);
		demoWithCostume = (void*)demoFlight;
		result = bsearch(&demoWithCostume, flightsArr_withCostume, arrSize, sizeof(Flight*), compareHour);
		break;
	case 2:
		createDemoFlight_Date(demoFlight);
		demoWithCostume = (void*)demoFlight;
		result = bsearch(&demoWithCostume, flightsArr_withCostume, arrSize, sizeof(Flight*), compareDate);
		break;
	case 3:
		createDemoFlight_Speed(demoFlight);
		demoWithCostume = (void*)demoFlight;
		result = bsearch(&demoWithCostume, flightsArr_withCostume, arrSize, sizeof(Flight*), compareSpeed);
	}
	free(demoFlight);
	if (result != NULL)
		found = *(Flight**)result;
	return found;
}

void createDemoFlight_Hour(Flight* f1) {
	int hourOfTakeOff = 0;
	while (1) {
		printf("insert time of takeOff [00-23]:\n");
		scanf("%d", &hourOfTakeOff);

		if (hourOfTakeOff >= 0 && hourOfTakeOff <= 23) {
			makeFictitiousFlight("01/01/1900", hourOfTakeOff, 000, f1);
			return;
		}
	}
}
void createDemoFlight_Date(Flight* f1) {
	char* date = getDate();
	makeFictitiousFlight(date, 0, 000, f1);
}
void createDemoFlight_Speed(Flight* f1) {
	float fSpeed;
	printf("insert flight's speed:\n");
	scanf("%f", &fSpeed);
	makeFictitiousFlight("01/01/1900", 0, fSpeed, f1);
}


void freeAirline(AirLine* a1) {

#ifdef _USE_GENERAL_VOID_FUNCTIONS

	generalArrayFunction(a1->allFlights->body, (a1->lastIndexFilledInFlightsPtrArray + 1),
		sizeof(Flight*), freeFlight_Void);


#else
	// v1 - Works well (changing to generic function) 
	while (a1->allFlights->size > 0) {
		freeFlight((Flight*)arraylist_pop(a1->allFlights));
	}
	arraylist_destroy(a1->allFlights);

#endif // _USE_GENERAL_VOID_FUNCTIONS

}
