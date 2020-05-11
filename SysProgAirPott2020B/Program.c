#include "Program.h"

void main() {
	AirportManager AirportDB = *(InitDataBase());
	Airport	portsArr[5];
	char name[][10] = { "BenGuryun" , "JFK" , "NYC" , "Chakie" , "palmokov" };
	char city[][20] = { "Tel Aviv" , "New York" , "New York city", "Brazila" , "Palma de" };
	char IATAcode[][5] = { "TLV" , "JFK" , "RPG" , "JDK" , "PDM" };
	float latitude[5]  = { 5.3, 3.5, 2.4 , 4.2 , 5.5556 };
	float longtitude[5] = { 6.3, 5.5, 6.4 , 5.2 , 8.5556 };

	for (int i = 0; i < 5; i++) {
		portsArr[i] = *(AutoaddNewAirport(name[i], city[i], IATAcode[i], latitude[i], longtitude[i]));
		addAirportToProg(&AirportDB, portsArr[i]);
	}
	printAllFlights(&AirportDB);

	
	startMenu();

	freeDB(&AirportDB);
}

void startMenu() {
	printStartMenu();
	int flag = 0;
	char userInput;
	do {
		userInput = getchar();
		switch (userInput) {
		case '1':
			printf("yes!1\n");
			pAddFlightToCompany();
			break;
		case '2':
			printf("yes!1\n");
			pAddAirportToDataBase();
			break;
		case '3':
			printf("yes!1\n");
			pPrintAirlineDetails();
			break;
		case '4':
			printf("yes!1\n");
			pPrintEntireDataBase();
			break;
		case '5':
			printf("yes!1\n");
			pPrintNumOfFlights();
			break;
		case '6':
			printf("GoodBye!\n");
			// FREE ALL DATA
			flag = 1;
			break;
		default:
			print("WRONG INPUT\n");


		}
	} while (flag != 1);
}



void printStartMenu() {
	printf("___________________\n");
	printf("1. add flight to a company\n");
	printf("2. add airport to program's Airport Manager\n");
	printf("3. print company's details\n");
	printf("4. print Airport Manager DataBase\n");
	printf("5. print number of flights from A to B in company X \n");
	printf("6. exit the program\n");
}

void pAddFlightToCompany() {



}


void pAddAirportToDataBase() {



}
void pPrintAirlineDetails() {


}
void pAddFlightToCompany() {



}
void pPrintEntireDataBase() {



}
void pPrintNumOfFlights() {



}

























// NOTE! __________
// all enteties must implement:
// get from user
// print to screen
// free memory 





//void openfile() {
//	FILE* f = fopen(<file name>, <open parameters>);
//	if (f == NULL) {
//		PRINT(failed opening the file.Exiting program);
//		return
//	}
//}