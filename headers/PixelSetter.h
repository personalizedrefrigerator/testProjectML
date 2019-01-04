#pragma once

#include "Color.h"

class PixelSetter
{
public:
	virtual void setAt(int x, int y) = 0;
	virtual Color getAt(int x, int y) const = 0;
	virtual void setColor(int r, int g, int b) = 0;
	virtual char * getDataPtr() const = 0;
	virtual long getDataLength() const = 0;
	void clear(unsigned char clearValue);
	inline void drawRect(int x, int y, int w, int h, PixelSetter& pixelSetter);
	virtual ~PixelSetter() {};
};

void PixelSetter::drawRect(int startX, int startY, int width, int height, PixelSetter& drawer)
{
	int y;
	int maxX = startX + width;
	int maxY = startY + height;

	for(int x = startX; x < maxX; x++)
	{
		for(y = startY; y < maxY; y++)
		{
			drawer.setAt(x, y);
		}
	}
}
