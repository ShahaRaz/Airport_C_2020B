#include "flightUtils.h"


//Airport* pNuAirport = NULL;
//pNuAirport = (Airport*)malloc(sizeof(Airport));

float CalcfligthTime(const Flight* flight1) {
	// calc in mintes, convert to hr/min and to string the in end
	const Flight* f1 = flight1;
	float distance = calcDistanceBetweenAirports(*(f1->flyFrom), *(f1->flyTo));
	float inMinutes = ((distance * 60) / (f1->fligthVelocity));
	int timeInHrs = (int)inMinutes / 60;
	int timeInMinutes = (int)inMinutes % 60;
	// test if working well... 
	return inMinutes;
}

//printFlightTime(const float distance,const float speed) {
//	float inMinutes = ((distance * 60) / (speed));
//	int timeInHrs = inMinutes / 60;
//	int timeInMinutes = (int)inMinutes % 60;
//	printf("%.2d:%.2d", timeInHrs, timeInMinutes);
//}

int isFlightFromAtoB(Flight* f1, char* flyFrom, char* flyTo) {
	if (strcmp(f1->flyTo->IATAcode, flyTo) != 0) return 0;
	if (strcmp(f1->flyFrom->IATAcode, flyFrom) != 0) return 0;
	// TODO double check pointers and stuff
	return 1;
}

int countFlightsFromAtoB(arraylist* flightsPtrArr, char* flyFromA, char* flyToB) {
	if (arraylist_size(flightsPtrArr) == 0)
		return -1;
	Flight* ptrToFlight;
	int counter = 0;
	for (size_t i = 0; i < arraylist_size(flightsPtrArr); i++) {
		ptrToFlight = (Flight*)arraylist_get(flightsPtrArr, i);
		counter = counter + (isFlightFromAtoB(ptrToFlight, flyFromA, flyToB));
	}
	return counter;
}

Flight* manuallyCreateNewFlight(const AirportManager* airportDB) {
	char* depIATA, * arrIATA, * dateOfTakeOff;
	int hourOfTakeOff, flag = 0;
	float flightVelocity;
	printf("insert IATA of departure airport:\n");
	depIATA = setIATAofFlight(airportDB);
	printf("IATA of arrivial airport:\n");
	arrIATA = setIATAofFlight(airportDB);
	printf("insert departure date: \t");
	dateOfTakeOff = getDate();
	while (flag == 0) {
		printf("insert time of takeOff [00-23]:\n");
		scanf("%d", &hourOfTakeOff);
		if (hourOfTakeOff >= 0 && hourOfTakeOff <= 23) flag = 1;
	} // input control
	getchar(); // clean buffer after int 
	printf("insert flight velocity:\t");
	scanf("%f", &flightVelocity);

	//adding, and returning the flight added
	return automaticllyCreateNewFlight(depIATA, arrIATA, dateOfTakeOff, hourOfTakeOff, flightVelocity, airportDB);
}


char* setIATAofFlight(const AirportManager* airportDB) {
	char* userChoise;
	do {
		printf("_______ALL AVAILBLE AIRPORTS_______\n");
		printAllAirports(airportDB);
		printf("Insert IATA of wanted airport (_pickMe_)\n");
		userChoise = getIATA();
	} while (findAirportByIATA(airportDB, userChoise) == NULL);
	return userChoise;

}


Flight* automaticllyCreateNewFlight(char* depIATA, char* arrIATA,
	char* dateOfTakeOff, int hourOfTakeOff, float flightVelocity, const AirportManager* airportDB) {
	Flight* f1;
	f1 = (Flight*)malloc(sizeof(Flight) * 1);
	if (f1 == NULL)
		return NULL;
	else {
		f1->fligthVelocity = flightVelocity;
		//copyString(dateOfTakeOff, f1->dateOfTakeoff);
		f1->dateOfTakeoff = _strdup(dateOfTakeOff);

		f1->flyFrom = findAirportByIATA(airportDB, depIATA); // func in airportManagerUtils
		f1->flyTo = findAirportByIATA(airportDB, arrIATA);
		f1->hourOfTakeoff = hourOfTakeOff;
	}
	return f1;
}

void makeFictitiousFlight( // made for bSearch 
	char* dateOfTakeOff, int hourOfTakeOff, float flightVelocity, Flight* f1) {
	if (f1 == NULL)
		return;
	else {
		f1->fligthVelocity = flightVelocity;
		f1->dateOfTakeoff = _strdup(dateOfTakeOff);
		f1->flyFrom = NULL;
		f1->flyTo = NULL;
		f1->hourOfTakeoff = hourOfTakeOff;
	}
	return;
}





void printFlightDetails(Flight* f1) {
	double distance = calcDistanceBetweenAirports(*f1->flyFrom, *f1->flyTo);
	float inMinutes = CalcfligthTime(f1);

	int timeInHrs = (int)inMinutes / 60;
	int timeInMinutes = (int)inMinutes % 60;

	printf("%s -> %s,  (%s / %d:00),  %.2f MPH, %.2f Miles , [%.2d:%.2d] total \n", f1->flyFrom->IATAcode, f1->flyTo->IATAcode,
		f1->dateOfTakeoff, f1->hourOfTakeoff, f1->fligthVelocity, distance, timeInHrs, timeInMinutes);

}

void printFlightDetails_void(void* f1)
{
	Flight* fTemp = (Flight*)f1;
	printFlightDetails(f1);

}

void copyFlight(const Flight* src, Flight* dest)
{
	dest->dateOfTakeoff = _strdup(src->dateOfTakeoff);
	dest->fligthVelocity = (float)src->fligthVelocity;
	dest->flyFrom = (Airport*)src->flyFrom; // pointer
	dest->flyTo = (Airport*)src->flyTo;
	dest->hourOfTakeoff = (int)src->hourOfTakeoff;
}




void writeFlightToBinaryFile(Flight* flight1, FILE* file1) { // 1 is used to emphasize that it isnt a saved word
	if (!file1)  // if didn't recive a file pointer
		return;
	int days, months, years, tempStrLen;
	//W-> source ITAT
	tempStrLen = strlen(flight1->flyFrom->IATAcode) + 1;
	fwrite(&tempStrLen, sizeof(int), 1, file1); // say how manny bytes the next string(array of chars) will consume
	fwrite(flight1->flyFrom->IATAcode, sizeof(char), tempStrLen, file1);
	//W-> Dest ITAT
	tempStrLen = strlen(flight1->flyTo->IATAcode) + 1;
	fwrite(&tempStrLen, sizeof(int), 1, file1);
	fwrite(flight1->flyTo->IATAcode, sizeof(char), tempStrLen, file1);	
	//W-> hrOfTakeOff
	fwrite(&flight1->hourOfTakeoff, sizeof(int), 1, file1);
	//W-> Date in ints
	if (DateToInt(flight1->dateOfTakeoff, &days, &months, &years) == 0)
		return;
	fwrite(&days, sizeof(int), 1, file1);
	fwrite(&months, sizeof(int), 1, file1);
	fwrite(&years, sizeof(int), 1, file1);
	//W-> Speed
	fwrite(&flight1->fligthVelocity, sizeof(float), 1, file1);

}

void readFlightFromBinaryFile(FILE* file1, Flight* flight1, AirportManager* airportDB) {

	if (!file1) { // if didn't recive a file pointer
		printf("file not found");
		return;
	}
	//flight1 = (Flight*)malloc(sizeof(Flight) * 1);
	int IATAlen = 0;
	char* tempIATACodeFrom, * tempIATACodeTo;
	//R->source IATA
	fread(&IATAlen, sizeof(int), 1, file1);
	tempIATACodeFrom = (char*)malloc(sizeof(char) * IATAlen);
	fread(tempIATACodeFrom, sizeof(char), IATAlen, file1);  ////// ___ TODO PROBLEM HERE
	/*Airport* temp = findAirportByIATA(airportDB, tempIATACodeFrom);*/
	flight1->flyFrom = findAirportByIATA(airportDB, tempIATACodeFrom); /// ________________ let 
	//R-> dest IATA
	fread(&IATAlen, sizeof(int), 1, file1);
	tempIATACodeTo = (char*)malloc(sizeof(char) * IATAlen);
	fread(tempIATACodeTo, sizeof(char), IATAlen, file1);//R->dest IATA
	flight1->flyTo = findAirportByIATA(airportDB, tempIATACodeTo); /// ________________ 
	// R-> HourTakeOff
	fread(&flight1->hourOfTakeoff, sizeof(int), 1, file1);
	//R-> Date
	int day, month, year;
	fread(&day, sizeof(int), 1, file1);
	fread(&month, sizeof(int), 1, file1);
	fread(&year, sizeof(int), 1, file1);
	char fuckCIHateYourBugs[11];
	intsToDate(day, month, year, fuckCIHateYourBugs);
	flight1->dateOfTakeoff = _strdup(fuckCIHateYourBugs);
	// R-> Speed
	fread(&flight1->fligthVelocity, sizeof(float), 1, file1);
	




//	Flight* automaticllyCreateNewFlight(char* depIATA, char* arrIATA,
//		char* dateOfTakeOff, int hourOfTakeOff, float flightVelocity, const AirportManager * airportDB) {


}


void freeFlight_Void(void* freeMe) {
	Flight* f1 = (Flight*)freeMe;
	freeFlight(f1);
}
//Freeflight

void freeFlight(Flight* f1) {
	// airposts pointing to are freed when freeint airportDB
	free(f1->dateOfTakeoff);
	free(f1);
}


