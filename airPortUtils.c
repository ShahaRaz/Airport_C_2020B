#include "airPortUtils.h"
#pragma warning(disable:4244) // float loss of data to double 
#pragma warning(disable:4013) // assuming extern returning int

void ManuallyaddNewAirport(Airport* pNuAirport) {
	printf("lets add an airport\n");
	printf("please insert name\n");
	char* name = getStrExactLength();
	printf("please insert country\n");
	char* country = getStrExactLength();
	printf("please insert IATAcode\n");
	char* IATAcode = getIATA();
	float latitude, longtitude;
	printf("please insert Latitude cords\n");
	scanf("%f", &latitude);
	printf("please insert Longtitude cords\n");
	scanf("%f", &longtitude);


	AutoaddNewAirport(name, country, IATAcode, latitude, longtitude, pNuAirport);

}

int AutoaddNewAirport(char* name, char* country, char* IATAcode, float latitude, float longitude, Airport* pNuAirport) {
	if (pNuAirport == NULL)
	{
		pNuAirport = (Airport*)malloc(sizeof(Airport) * 1);
	}

	if (pNuAirport == NULL)
		return 0;

	//copyString(name, pNuAirport->name);
	pNuAirport->name = _strdup(name);
	//copyString(country, pNuAirport->country);
	pNuAirport->country = _strdup(country);

	//copyString(IATAcode, pNuAirport->IATAcode );
	pNuAirport->IATAcode = _strdup(IATAcode);

	if (strlen(pNuAirport->IATAcode) != IATA_CODE_LENGTH)
	{
		printf("IATA must contain 3 Digits\t extiting program\n");
		return 0;
	}
	if (latitude < -90 || latitude>90) return 0;
	if (longitude < -180 || longitude>180)return 0;
	pNuAirport->latitude = latitude;
	pNuAirport->longitude = longitude;
	return 1;
}


int isAirPortsEq(const Airport* a1, const Airport* a2)
{
	if (strcmp(a1->IATAcode, a2->IATAcode)) // deleted * from before a1 and a2 for error correction
		return 1;
	return 0;
}

int isAirportCodeFit(const Airport a1, const char* checkIATAcode) {
	if (strcmp(a1.IATAcode, checkIATAcode) == 0)
		return 1;
	return 0;

}



float calcDistanceBetweenAirports(const Airport a1, const  Airport a2) {
	float R = 3958.7f; //miles of earth radius
	float dLat = deg2rad((a2.latitude) - (a1.latitude));
	float dLon = deg2rad((a2.longitude) - (a1.longitude));

	float nLat1 = deg2rad(a1.latitude);
	float nLat2 = deg2rad(a2.latitude);

	// apply formulae 
	float a = pow(sin(dLat / 2), 2) +
		pow(sin(dLon / 2), 2) *
		cos(nLat1) * cos(nLat2);
	//float rad = 6371f;
	float c = 2 * asin(sqrt(a));
	return R * c;
}

float deg2rad(float deg)
{
	return deg * (M_PI / 180);
}

void printPortDetails_Void(const void* port) {
	Airport aP = *(Airport*)port;
	printPortDetails(aP);
	//printf("%-20s  %-14s (%.3f,%.3f)   %-5s  \n", aP.name
	//	, aP.country, aP.longitude, aP.latitude, aP.IATAcode);
}

void printPortDetails(const Airport aP) {
	printf("%-20s  %-14s (%.3f,%.3f)   %-5s  \n", aP.name
		, aP.country, aP.longitude, aP.latitude, aP.IATAcode);
}



void writeAirportToFile(FILE* f, const Airport* a1) {
	fputs(a1->name, f);
	fprintf(f, "\n"); // isn't there a better way?
	fputs(a1->country, f);
	fprintf(f, "\n"); // isn't there a better way?
	fputs(a1->IATAcode, f);
	fprintf(f, "\n"); // isn't there a better way?
	fprintf(f, "%f %f\n", a1->latitude, a1->longitude);
}

void readAirportFromFile(FILE* f, Airport* a1)
{
	a1->name = getStrExactLengthFromFile(f); // drops the courser inside
	a1->country = getStrExactLengthFromFile(f);
	a1->IATAcode = getStrExactLengthFromFile(f);
	fscanf(f, "%f %f\n", &a1->latitude, &a1->longitude); // \n drop courser for next scan.
}


void freeAirport(Airport* a1) {
	if (a1 == NULL)
		return;
	free(a1->name);
	free(a1->country);
	free(a1->IATAcode);
	//free(a1); freeing when free entire array (After finishing free all airports^^)
}