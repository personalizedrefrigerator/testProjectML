#pragma once

#include "PixelSetter.h"
#include "BaseRenderer.h"
#include "TextDrawer.h"
#include "InvertedPixelSetter.h"

class CUDAColorGrapherRenderer : public BaseRenderer
{
public:
	void render(PixelSetter* pixelSetter, int width, int height);
	virtual ~CUDAColorGrapherRenderer();
private:
	float zoom = 0.1f;
	TextDrawer textRenderer = TextDrawer();
	InvertedPixelSetter * invertedPixelSetter = nullptr;

	long lastTimeSinceEpoch = 0;
};
