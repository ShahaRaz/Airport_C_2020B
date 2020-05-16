#include "Program.h"
#define NUMBER_OF_ELEMENTS 5
// WE ONLY DEAL WITH ONE COMPANY
void main() {
	//testStringUtils();
	
	//move to add_data_to_DB
	AirportManager airportDB = *(InitDataBase());
	//int addFlightToAirLine(AirLine * a1, const Flight * f1)
	char* airlineName = "ours";
	AirLine ourAirLine = *(AutomaticllyCreateAirline(airlineName, 5));
	Airport	portsArr[NUMBER_OF_ELEMENTS];
	char name[][12] = { "BEN GURION" , "JOHN KENNEDY" , "PAGADIAN" , "IBIZA" , "PHUKET INT" };
	char city[][20] = { "Tel Aviv" , "New York" , "LEGAZPI", "IBIZA" , "PHUKET Thailand" };
	char IATAcode[][NUMBER_OF_ELEMENTS] = { "TLV" , "JFK" , "LGP" , "IBZ" , "HKT" };
	float latitude[NUMBER_OF_ELEMENTS] = { 32.009, 40.64, 7.828 , 38.873 , 8.113 };
	float longtitude[NUMBER_OF_ELEMENTS] = { 34.877, -73.779, 123.46 ,1.373 , 98.317 };

	Flight flightsArr[NUMBER_OF_ELEMENTS];

	int hrsofTakeOff[] = { 1, 2, 3, 4, 5 };
	float flightSpeed[] = { 600,600,600,600,600 };
	char datesOfTakeOff[][11] = { "04/11/1995" , "18/03/2002" , "05/03/2001" , "01/01/2001" , "02/02/2002" };

	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
		portsArr[i] = *(AutoaddNewAirport(name[i], city[i], IATAcode[i], latitude[i], longtitude[i]));
		addAirportToAirportManager(&airportDB, portsArr[i]); // maybe remove & 
	}


	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
		flightsArr[i] = *(automaticllyCreateNewFlight(IATAcode[i], IATAcode[((NUMBER_OF_ELEMENTS-1) - i)],
			datesOfTakeOff[i], hrsofTakeOff[i], flightSpeed[i],&airportDB));
		if(addFlightToAirLine(&ourAirLine, &flightsArr[i])==-1) freeAll(&airportDB,&ourAirLine);
	}
	//for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
	//	addFlightToAirLine(&ourAirLine, &flightsArr[i]);
	//}
	//for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
	//	addFlightToAirLine(&ourAirLine, &flightsArr[i]);
	//}

	
	
	printAirlineDetails(&ourAirLine);
	

	//add_data_to_DB(&AirportDBase);

	printAllAirports(&airportDB);

	startMenu(&airportDB,&ourAirLine);

	freeDB(&airportDB);
}

void add_data_to_DB(AirportManager *AirportDB) { // doesnt work well for some reason.
	printf("fix me");
	//Airport	portsArr[5];
	//char name[][10] = { "BenGuryun" , "JFK" , "NYC" , "Chakie" , "palmokov" };
	//char city[][20] = { "Tel Aviv" , "New York" , "New York city", "Brazila" , "Palma de" };
	//char IATAcode[][5] = { "TLV" , "JFK" , "RPG" , "JDK" , "PDM" };
	//float latitude[5] = { 5.3, 3.5, 2.4 , 4.2 , 5.5556 };
	//float longtitude[5] = { 6.3, 5.5, 6.4 , 5.2 , 8.5556 };

	//for (int i = 0; i < 5; i++) {
	//	portsArr[i] = *(AutoaddNewAirport(name[i], city[i], IATAcode[i], latitude[i], longtitude[i]));
	//	addAirportToProg(&AirportDB, portsArr[i]); // maybe remove & 
	//}

	////____________________________________________
	//Flight flightsArr[5];
	//flightsArr[0]=automaticllyAddNewFlight()

}

void startMenu(AirportManager *airportDB, AirLine *ourAirLine) {
	int flag = 0;
	char userInput;
	do {
		printsStartMenu();
		userInput = getchar();
		flushall();
		switch (userInput) {
		case '1':
			pAddFlightToCompany(airportDB,ourAirLine);
			break;
		case '2':
			pAddAirportToDataBase(airportDB);
			break;
		case '3':
			pPrintAirlineDetails(ourAirLine);
			break;
		case '4':
			pPrintEntireDataBase(airportDB, ourAirLine);
			flushall();
			break;
		case '5':
			pPrintNumOfFlights(airportDB,ourAirLine);
			break;
		case '6':
			printf("GoodBye!\n");
			freeAll(airportDB, ourAirLine);
			// FREE ALL DATA
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
	printf("5. print number of flights from A to B in company X \n");
	printf("6. exit the program\n");
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
	Airport* addedAirport  = ManuallyaddNewAirport();
	if (findAirportByIATA(airportDB, addedAirport->IATAcode) != NULL) { // there is an exisiting airport with this IATA in database;
		printf("airport already in DB.\n");
		return 0;
	}
	addAirportToAirportManager(airportDB, *addedAirport);
	getchar(); // bug fix, clean buffer
	return 1;
}
void pPrintAirlineDetails(const AirLine* ourAirLine)  { //3 // check if needs airportDB

	printAirlineDetails(ourAirLine);
	getchar(); // bug fix, clean buffer

}

void pPrintEntireDataBase(const AirportManager* airportDB) { //4 
	printAllAirports(airportDB);
	getchar(); // bug fix, clean buffer
}



void pPrintNumOfFlights(const AirportManager* airportDB,  const AirLine* ourAirLine) { //5 
	char *depIATA, *arrIATA;

	printf("insert IATA of departure airport:\n");
	depIATA = setIATAofFlight(airportDB);
	printf("IATA of arrivial airport:\n");
	arrIATA = setIATAofFlight(airportDB);

	int count = countCompanyFlightsFromAtoB(ourAirLine, depIATA, arrIATA);
	printf("company %s has %d flights from %s to %s", ourAirLine->name, count, depIATA, arrIATA);
	getchar(); // bug fix, clean buffer
//	countCompanyFlightsFromAtoB(const AirLine * a1, char* flyFromA, char* flyToB)

}



void freeAll(AirportManager* airportDB, AirLine* ourAirLine) {
	freeDB(airportDB);
	freeAirline(ourAirLine);
	}





void testStringUtils() {
//	tst String utils 

char tst[] = "  twoSpaces    4spaces 1space 1 1 1 5spacesHead     ";
puts(tst);
remove_spaces(tst, tst); // fix 
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

//void openfile() {
//	FILE* f = fopen(<file name>, <open parameters>);
//	if (f == NULL) {
//		PRINT(failed opening the file.Exiting program);
//		return
//	}
//}
