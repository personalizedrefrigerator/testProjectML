#pragma once
#include "BaseRenderer.h"

class EmptyRenderer : public BaseRenderer
{
	void render(PixelSetter* pixelSetter, int screenWidth, int screenHeight) {};
	virtual ~EmptyRenderer();
};
