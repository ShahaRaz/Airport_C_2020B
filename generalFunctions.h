#ifndef __generalFunHelpers
#define __generalFunHelpers

void generalArrayFunction(void* array, int numOfElements,
	int sizeOfElement, void (*func)(void*));
#include "flightUtils.h"
void liftOff(Flight* f, ...);
#endif // !__generalFunHelpers





