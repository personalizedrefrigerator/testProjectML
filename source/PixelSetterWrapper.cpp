/*
 * PixelSetterWrapper.cpp
 *
 *  Created on: Jul 1, 2018
 */

#include "PixelSetterWrapper.h"

void PixelSetterWrapper::setAt(int x, int y)
{
	givenPixelSetter->setAt(x, y);
}

Color PixelSetterWrapper::getAt(int x, int y) const
{
	return givenPixelSetter->getAt(x, y);
}

void PixelSetterWrapper::setColor(int r, int g, int b)
{
	givenPixelSetter->setColor(r, g, b);
}

char * PixelSetterWrapper::getDataPtr() const
{
	return givenPixelSetter->getDataPtr();
}

long PixelSetterWrapper::getDataLength() const
{
	return givenPixelSetter->getDataLength();
}

bool PixelSetterWrapper::setPixelSetter(PixelSetter * newPixelSetter)
{
	 if(newPixelSetter != givenPixelSetter)
	 {
		 givenPixelSetter = newPixelSetter;

		 return true;
	 }
	 else
	 {
		 return false;
	 }
}
