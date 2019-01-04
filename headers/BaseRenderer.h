#pragma once

#include "PixelSetter.h"

struct KeyInfo
{
	int lastKey = 0;
	bool handledKey = true;
};

class BaseRenderer
{
protected:
	KeyInfo keyData;

public:
	virtual void render(PixelSetter* pixelSetter, int width, int height) = 0;
	virtual void setKeyInfo(KeyInfo information) { keyData = information; };
	virtual ~BaseRenderer() {};
};
