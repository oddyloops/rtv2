#ifndef LIGHT_CODES_H
#define LIGHT_CODES_H

#include "typedefs.h"

struct light_code
{
	static const byte directional = 1;
	static const byte point = 2;
	static const byte spot = 3;

};

#endif // !LIGHT_CODES_H
