
#include "airPortUtils.h"

Airport* ManuallyaddNewAirport() {
	printf("lets add an airport\n");
	printf("please insert name\n");
	char *name = getStrExactLength();
	printf("please insert country\n");
	char *country = getStrExactLength();
	printf("please insert IATAcode\n");
	char *IATAcode = getStrExactLength();
	float latitude, longtitude;
	printf("please insert Latitude cords\n");
	scanf("%f",&latitude);
	printf("please insert Longtitude cords\n");
	scanf("%f", &longtitude);
	

	return AutoaddNewAirport(name, country, IATAcode, latitude, longtitude);

}

Airport* AutoaddNewAirport(char* name, char* country, char* IATAcode ,float latitude,float longitude) {
	Airport* pNuAirport = NULL;
	pNuAirport = (Airport*)malloc(sizeof(Airport));
	if (pNuAirport == NULL) return NULL;
	pNuAirport->name = name;

	pNuAirport->country = country;

	pNuAirport->IATAcode = IATAcode;
	if (strlen(pNuAirport->IATAcode) != IATA_CODE_LENGTH)
	{
		printf("IATA must contain 3 Digits\t extiting program\n");
		return NULL;
	}
	if (latitude < -90 || latitude>90) return NULL;
	if (longitude < -180 || longitude>180)return NULL;
	pNuAirport->latitude = latitude;
	pNuAirport->longitude = longitude;
	return pNuAirport;
}








int isAirPortsEq(const Airport *a1,const Airport *a2)
{
	if (strcmp(*a1->IATAcode, *a2->IATAcode))
		return 1;
	return 0;
}

int isAirportCodeFit(const Airport a1,const char* checkIATAcode) {
	if (strcmp(a1.IATAcode, checkIATAcode))
		return 1;
	return 0;

}

float calcDistanceBetweenAirports(const Airport a1,const  Airport a2) {
	// TODO 
	// Earth Radious is about 3950 miles
	// 
	int R = 3950; //miles of earth radius
	float dLat = deg2rad((a2.latitude) - (a1.latitude));
	float dLon = deg2rad((a2.longitude) - (a1.longitude));
	float a =
		sin(dLat / 2) * sin(dLat / 2) +
		cos(deg2rad((a1.latitude))) * cos(deg2rad((a2.latitude))) *
		sin(dLon / 2) * sin(dLon / 2);
	float c = 2 * atan2(sqrt(a), sqrt(1 - a));
	float d = R * c; // Distance in miles
	return d;

}
float deg2rad(float deg)
{
	return deg * (M_PI / 180);
}

void printPortDetails(Airport aP) {
	printf("%s,  %s,  %s,   (%f,%f)\n",aP.name,aP.country,aP.IATAcode,aP.longitude,aP.latitude);


}
