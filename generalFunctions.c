#include "generalFunctions.h"
#include <stdarg.h>
#ifdef _USE_GENERAL_VOID_FUNCTIONS
void generalArrayFunction(void* array, int numOfElements,
	int sizeOfElement,void (*func)(void*)) { // pointers to functions.
	// functions will getr an array, number of elements , size of each element in bytes,
	//and pointer to function : void f(void* element);
	// needs to 1.  be used for printing airports from airportManager
	// 2. free the array of flights in airline company

	for (size_t i = 0; i < numOfElements; i++)
	{
		func((char*)array + i * sizeOfElement);
		// (char*) cause its the smallest memory we deal with
		//jump over the elements in the array using i*sizeOfElement 
	}
} // iterate over array and apply function of type [ void f(void* element) ]
#endif // _USE_GENERAL_VOID_FUNCTIONS



//Variadic function exce
void liftOff(Flight* f, ...) {
	if (f == NULL) return;
	va_list flightsArr;
	Flight* temp;

	va_start(flightsArr, f);
	temp = f;
	while(temp!=NULL)
	{
		printFlightDetails(temp);
		temp = va_arg(flightsArr, Flight*); // gets the next element in arr
		
	}
	va_end(flightsArr);
}

