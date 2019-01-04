#pragma once

#include "PixelSetter.h"

class X11PixelSetter : public PixelSetter
{
private:
	int width = 0,
		height = 0;
	char* data = nullptr;
	int dataLength = 0;

	// Color values.
	int colorR = 0,
			colorG = 0,
			colorB = 0;
public:
	void setAt(int x, int y) override;
	Color getAt(int x, int y) const override;
	inline void setColor(int r, int g, int b) override { colorR = r; colorG = g; colorB = b; };
	void setData(char* dataArray, int length, int width, int height);
	char * getDataPtr() const override;
	long getDataLength() const override;
};
