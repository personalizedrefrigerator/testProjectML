/*
 * X11PixelSetter.cpp
 *
 *  Created on: Jun 29, 2018
 */

#include "X11PixelSetter.h"

// Set the data array. This MUST be called.
void X11PixelSetter::setData(char* data, int length, int width, int height)
{
	this->data = data;
	this->dataLength = length;
	this->width = width;
	this->height = height;
}

// Set a pixel at the specified location.
void X11PixelSetter::setAt(int x, int y)
{
	if(x >= 0 && y >= 0 && x < width && y < height && x*4 + 2 + y*width*4 < dataLength)
	{
		data[x*4 + y*width*4] = colorB;
		data[x*4 + 1 + y*width*4] = colorG;
		data[x*4 + 2 + y*width*4] = colorR;
	}
}

// Get a pixel's color.
Color X11PixelSetter::getAt(int x, int y) const
{
	Color result = Color(0, 0, 0);
	if(x >= 0 && y >= 0 && x < width && y < height && x*4 + 2 + y*width*4 < dataLength)
	{
		// These colors are in the BGR format.
		result.blue = data[x*4 + y*width*4];
		result.green = data[x*4 + 1 + y*width*4];
		result.red = data[x*4 + 2 + y*width*4];
	}

	return result;
}

// Get a pointer to the data.
char * X11PixelSetter::getDataPtr() const
{
	return data;
}

// Get the length of the data.
long X11PixelSetter::getDataLength() const
{
	return dataLength;
}

// setColor is inline, so defined in the header file.
