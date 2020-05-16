#include "flightUtils.h"

//Airport* pNuAirport = NULL;
//pNuAirport = (Airport*)malloc(sizeof(Airport));

float CalcfligthTime(const Flight* flight1) {
	// calc in mintes, convert to hr/min and to string the in end
	Flight* f1 = flight1;
	float distance = calcDistanceBetweenAirports(*(f1->flyFrom), *(f1->flyTo));
	float inMinutes = ((distance *60)/ (f1->fligthVelocity));
	int timeInHrs = inMinutes / 60;
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

int countFlightsFromAtoB(Flight** arrOfpFlights, char* flyFromA, char* flyToB) {
	//returns how manny flights from the flights-pointers-array are from A to B
	Flight* ptr = arrOfpFlights; // pointing to first flight in array
	int counter = 0;
	
	for (int i = 0; ptr != NULL ; i++) {
		counter=counter+(isFlightFromAtoB(ptr,flyFromA,flyToB));
		ptr++;
		//ptr = arrOfpFlights[i+1]; // point to next object
	}
	return counter;

	//___DELETE IF ALL WORKS WELL
	//while (ptr != NULL) // has next flight
	//{
	//	ptr = ptr + sizeof(Flight); // point to next object
	//}
}  

Flight* manuallyCreateNewFlight(const AirportManager* airportDB) {
	char* depIATA, * arrIATA, * dateOfTakeOff;
	int hourOfTakeOff,flag=0;
	float flightVelocity;
	printf("insert IATA of departure airport:\n");
	depIATA = setIATAofFlight(airportDB);
	printf("IATA of arrivial airport:\n");
	arrIATA= setIATAofFlight(airportDB);
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
	return automaticllyCreateNewFlight(depIATA, arrIATA, dateOfTakeOff, hourOfTakeOff, flightVelocity,airportDB); 
}


char* setIATAofFlight(const AirportManager* airportDB) {
	char* userChoise;
	do {
		printf("_______ALL AVAILBLE AIRPORTS_______\n");
		printAllAirports(airportDB);
		printf("Insert IATA of wanted airport (_pickMe_)\n");
		userChoise = getIATA();
	} while (findAirportByIATA(airportDB,userChoise)==NULL);
	return userChoise;

}


Flight* automaticllyCreateNewFlight(char* depIATA, char* arrIATA, 
	char* dateOfTakeOff, int hourOfTakeOff, float flightVelocity, const AirportManager* airportDB){
	Flight* f1;
	f1 = (Airport*)malloc(sizeof(struct airports)	);
	if (f1 == NULL)
		return NULL;
	else {
		f1->fligthVelocity = flightVelocity;
		f1->dateOfTakeoff = dateOfTakeOff;
		f1->flyFrom = findAirportByIATA(airportDB , depIATA); // func in airportManagerUtils
		f1->flyTo = findAirportByIATA(airportDB, arrIATA);
		f1->hourOfTakeoff = hourOfTakeOff;
	}
	return f1;
}



void printFlightDetails(Flight* f1) {
	
	float distance = calcDistanceBetweenAirports(*f1->flyFrom, *f1->flyTo);
	float inMinutes = CalcfligthTime(f1);

	int timeInHrs = inMinutes / 60;
	int timeInMinutes = (int)inMinutes % 60;

	printf("%s -> %s,  (%s / %d:00),  %.2f MPH, %.2f Miles , [%.2d:%.2d] total \n", f1->flyFrom->IATAcode, f1->flyTo->IATAcode,
		f1->dateOfTakeoff, f1->hourOfTakeoff, f1->fligthVelocity, distance , timeInHrs, timeInMinutes);
	putchar('\n');

}	
//TODO 



//Freeflight
void freeFlight(Flight* f1) {
	//free(f1);
}

void freeFlightsptrArray(Flight** pfligthArr) {
	Flight* f1 = (Flight*)pfligthArr;
	while (f1 != NULL) {
		freeFlight(f1);
		f1++;
	}

}
