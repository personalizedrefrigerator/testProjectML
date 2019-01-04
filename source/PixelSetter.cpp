#include "PixelSetter.h"
#include <cstring>

void PixelSetter::clear(unsigned char clearValue)
{
	char * data = getDataPtr();
	std::memset(data, clearValue, getDataLength());
}
