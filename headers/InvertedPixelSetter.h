#pragma once

#include "PixelSetterWrapper.h"

class InvertedPixelSetter : public PixelSetterWrapper
{
public:
	InvertedPixelSetter(PixelSetter * pixelSetter) : PixelSetterWrapper(pixelSetter) {};
	void setAt(int x, int y);

	float multiplyRed = 1.0f,
			multiplyGreen = 1.0f,
			multiplyBlue = 1.0f;
};
