#include "Program.h"

#define NUMBER_OF_TEST_ELEMENTS 5
// WE ONLY DEAL WITH ONE COMPANY
void main() {

	//		tests();

	AirportManager airportDB = *(InitDataBase());
	AirLine ourAirLine = *(AutomaticllyCreateAirline("ours", 5));
	Flight* flightsArr = { 0 };

//	add_data_to_DB(&airportDB, &ourAirLine, flightsArr);

	addDataFromFiles(&airportDB, &ourAirLine, "airport_authority.txt", "company.bin", flightsArr);


	printAllAirports(&airportDB);
	printAirlineDetails(&ourAirLine);


	startMenu(&airportDB, &ourAirLine);

	//end program

	saveDataToFile(&airportDB, &ourAirLine);
	printf("GoodBye!\n");
	freeAll(&airportDB, &ourAirLine);



}
void saveDataToFile(AirportManager* airportDB, AirLine* ourAirLine) { // TODO WRITE ME AND CREATE ReadFromFile
	writeManagerToFile(airportDB);
	writeAirlineToBinaryFile(ourAirLine);
}

void addDataFromFiles(AirportManager* airportDB, AirLine* ourAirLine, char* airportDBFileName, char* CompanyBinaryfileName, Flight* flightsArr) {
	FILE* fTxt = fopen(airportDBFileName, "r");
	readManagerFromFile(fTxt, airportDB);
	fclose(fTxt);

	FILE* fBinary = fopen(CompanyBinaryfileName, "rb");
	readAirlineFromBinaryFile(ourAirLine, fBinary, flightsArr, airportDB);
	fclose(fBinary);

}
void add_data_to_DB(AirportManager* airportDB, AirLine* ourAirLine, Flight flightsArr[]) { // doesnt work well for some reason.
	Airport portsArr[NUMBER_OF_TEST_ELEMENTS];
	flightsArr = (Flight*)malloc(sizeof(Flight) * NUMBER_OF_TEST_ELEMENTS);

	//int addFlightToAirLine(AirLine * a1, const Flight * f1)
	char name[][20] = { "BEN GURION" , "JOHN KENNEDY" , "PAGADIAN" , "IBIZA AirPort" , "PHUKET Airport" };
	char city[][20] = { "Tel Aviv" , "New York" , "LEGAZPI", "IBIZA" , "PHUKET Thailand" };
	char IATAcode[][NUMBER_OF_TEST_ELEMENTS] = { "TLV" , "JFK" , "LGP" , "IBZ" , "HKT" };
	float latitude[NUMBER_OF_TEST_ELEMENTS] = { 32.009f, 40.64f, 7.828f , 38.873f , 8.113f };
	float longtitude[NUMBER_OF_TEST_ELEMENTS] = { 34.877f, -73.779f, 123.46f ,1.373f , 98.317f };



	int hrsofTakeOff[] = { 8, 2, 5, 4, 5 };
	float flightSpeed[] = { 600,600,600,600,600 };
	char datesOfTakeOff[][11] = { "04/11/1995" , "18/03/2002" , "05/03/2001" , "01/01/2001" , "02/02/2002" };

	for (int i = 0; i < NUMBER_OF_TEST_ELEMENTS; i++) {
		(AutoaddNewAirport(name[i], city[i], IATAcode[i], latitude[i], longtitude[i], &portsArr[i]));
		addAirportToAirportManager(airportDB, portsArr[i]); // maybe remove & 
	}


	for (int i = 0; i < NUMBER_OF_TEST_ELEMENTS; i++) {
		flightsArr[i] = *(automaticllyCreateNewFlight(IATAcode[i], IATAcode[((NUMBER_OF_TEST_ELEMENTS - 1) - i)],
			datesOfTakeOff[i], hrsofTakeOff[i], flightSpeed[i], airportDB));
		addCopyOflightToAirLine(ourAirLine, &flightsArr[i]);

	}

	liftOff(&flightsArr[0], &flightsArr[1], &flightsArr[2], &flightsArr[3], NULL); // TODO - put me in a function that demonstrates me
	free(flightsArr);


}


void startMenu(AirportManager* airportDB, AirLine* ourAirLine) {
	int flag = 0;
	char userInput;
	do {
		printsStartMenu();
		userInput = getCharNOnewLine();
		switch (userInput) {
		case '1':
			pAddFlightToCompany(airportDB, ourAirLine); // p - Stands for program .... 
			ourAirLine->orderBy = 0; // not sorted after adding
			break;
		case '2':
			pAddAirportToDataBase(airportDB);
			break;
		case '3':
			pPrintAirlineDetails(ourAirLine);
			break;
		case '4':
			pPrintEntireDataBase(airportDB);
			break;
		case '5':
			pPrintNumOfFlights(airportDB, ourAirLine);
			break;
		case '6':
			pSortFlightsInAirline(ourAirLine);
			break;
		case '7':
			pSearchFlightByOrder(ourAirLine);
			break;
		case '8':
			/*	saveDataToFile(airportDB, ourAirLine);
				freeAll(airportDB, ourAirLine);*/ // doin that in main
				// FREE ALL DATA
			printf("GoodBye!\n");
			flag = 1;
			break;
		case '\n':
			putchar('\n');
			break;
		default:
			printf("WRONG INPUT\n");


		}
	} while (flag != 1);
}



void printsStartMenu() {
	printf("___________________\n");
	printf("1. add flight to a company\n");
	printf("2. add airport to program's Airport Manager\n");
	printf("3. print company's details\n");
	printf("4. print Airport Manager DataBase\n");
	printf("5. print number of flights from A to B in company X\n");
	printf("6. sort flights by attribute\n");
	printf("7. search flight by attribute\n");;
	printf("8. exit the program\n");
}

// _________________________________ DATA LOCATIONS ______________
// all airports are under AirPortManager
// all flights arn't saved in a specific place. 
// flights hold as pointers that the airline Company holds in it's array
// the comapny has an array of pointers to it's flights.

void pAddFlightToCompany(AirportManager* airportDB, AirLine* ourAirLine) {//1 
	Flight* f1 = manuallyCreateNewFlight(airportDB);
	addFlightToAirLine(ourAirLine, f1);
	printFlightDetails(f1);
}


int pAddAirportToDataBase(AirportManager* airportDB) { // 2
	Airport* addedAirport = NULL;
	ManuallyaddNewAirport(addedAirport);
	if (addedAirport == NULL) return 0;
	if (findAirportByIATA(airportDB, addedAirport->IATAcode) != NULL) { // there is an exisiting airport with this IATA in database;
		printf("airport already in DB.\n");
		return 0;
	}
	addAirportToAirportManager(airportDB, *addedAirport);
	return 1;

}
void pPrintAirlineDetails(const AirLine* ourAirLine) { //3 // check if needs airportDB

	printAirlineDetails(ourAirLine);

}

void pPrintEntireDataBase(const AirportManager* airportDB) { //4 
	printAllAirports(airportDB);
}



void pPrintNumOfFlights(const AirportManager* airportDB, AirLine* ourAirLine) { //5 
	char* depIATA, * arrIATA;

	printf("insert IATA of departure airport:\n");
	depIATA = setIATAofFlight(airportDB);
	printf("IATA of arrivial airport:\n");
	arrIATA = setIATAofFlight(airportDB);
	int count;
	count = countFlightsFromAtoB(ourAirLine->allFlights, depIATA, arrIATA);
	puts(ourAirLine->name);
	printf("has %d flights from %s to %s", count, depIATA, arrIATA);

}

void pSortFlightsInAirline(AirLine* ourAirLine) {
	sortFlights(ourAirLine);
}

void pSearchFlightByOrder(AirLine* ourAirLine) {
	Flight* found = findFlightInArray(ourAirLine);
	if (found == NULL)
		printf("Flight doesn't Exist!\n");
	else
		printFlightDetails(found);
}




void freeAll(AirportManager* airportDB, AirLine* ourAirLine) {
	freeDB(airportDB);
	freeAirline(ourAirLine);

}




void tests() {
	//testStringUtils();
	testArrayList();
}

void testStringUtils() {
	//	tst String utils 

	char tst[] = "  twoSpaces    4spaces 1space 1 1 1 5spacesHead     ";
	puts(tst);
	removeSpaces(tst);
	puts(tst);
	capitalizeFirstLetter(tst);
	puts(tst);

	char* tstDate;
	tstDate = getDate();
	puts(tstDate);



	char* tstIATA;
	tstIATA = getIATA();
	puts(tstIATA);
}

void testArrayList() {
	int tst1 = 1;
	int tst2 = 2;
	int tst3 = 3;
	int tst4 = 4;
	//int tst5 = 5;

	void* t1 = &tst1;
	void* t2 = &tst2;
	void* t3 = &tst3;
	void* t4 = &tst4;
	//	void* t5=  &tst5;

	arraylist* list = arraylist_create();
	arraylist_add(list, t1);
	arraylist_add(list, t2);

	arraylist_add(list, t3);

	arraylist_add(list, t4);


	printf("\n%d\n", *(int*)arraylist_get(list, 0));
	printf("%d\n", *(int*)arraylist_get(list, 0));

	printf("%d\n", *(int*)arraylist_get(list, 3));




	//manually get elements 
	printf("%d\n", *(int*)list->body[0]);
	printf("%d\n", *(int*)list->body[2]);

	printf("%d\n", *(int*)list->body[3]);

	arraylist_destroy(list);

}



///////////////////////////////////////___

// write and read of txt and binary files

// qsort in airline 

// generalArrayFunction in generalFunctions.c 


