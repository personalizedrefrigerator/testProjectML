/*
 * InvertedPixelSetter.cpp
 *
 *  Created on: Jul 1, 2018
 */

#include "InvertedPixelSetter.h"
#include <math.h>

void InvertedPixelSetter::setAt(int x, int y)
{
	Color newColor = getAt(x, y);
	newColor.red = (255 - newColor.red) * multiplyRed;
	newColor.green = (255 - newColor.green) * multiplyGreen;
	newColor.blue = (255 - newColor.blue) * multiplyBlue;

	setColor(newColor.red, newColor.green, newColor.blue);
	PixelSetterWrapper::setAt(x, y);
}
