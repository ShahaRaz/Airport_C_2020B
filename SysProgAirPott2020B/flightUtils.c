#include "flightUtils.h"

//Airport* pNuAirport = NULL;
//pNuAirport = (Airport*)malloc(sizeof(Airport));

float CalcfligthTime(Flight* flight1) {
	// calc in mintes, convert to hr/min and to string the in end
	Flight* f1 = flight1;
	float distance = calcDistanceBetweenAirports(*(f1->flyFrom), *(f1->flyTo));
	float inMinutes = ((distance *60)/ (f1->fligthVelocity));
	int timeInHrs = inMinutes / 60;
	int timeInMinutes = (int)inMinutes % 60;
	 // test if working well... 

}


int checkFlight_DestenationFit(Flight* f1, char* flyFrom, char* flyTo) {
	if (!strcmp(f1->flyTo->IATAcode, flyTo)) return 0;
	if (!strcmp(f1->flyFrom->IATAcode, flyFrom)) return 0;
	// TODO double check pointers and stuff
	return 1;
}

int countFlightsFromAtoB(Flight** arrOfpFlights, char* flyFromA, char* flyToB) {
	//returns how manny flights from the flights-pointers-array are from A to B
	Flight* ptr = arrOfpFlights; // pointing to first flight in array
	int counter = 0;
	
	for (int i = 0; ptr != NULL; i++) {
		counter=counter+(checkFlight_DestenationFit(ptr,flyFromA,flyToB));
		ptr = arrOfpFlights[i+1]; // point to next object
	}
	return counter;

	//___DELETE IF ALL WORKS WELL
	//while (ptr != NULL) // has next flight
	//{
	//	ptr = ptr + sizeof(Flight); // point to next object
	//}

}





















Flight* createNewFlight() {
	Flight* pF = NULL;
	pF = (Airport*)malloc(sizeof(Airport));
	if (pF == NULL) return NULL;
	// continue later
}