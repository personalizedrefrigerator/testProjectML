#pragma once

#include "PixelSetter.h"
#include "X11PixelSetter.h"
#include "BaseRenderer.h"
#include "EmptyRenderer.h"
#include <iostream>
#include <X11/Xlib.h>


class PixelWindow
{
	public:
	void create(int width, int height);
	void render();
	void setRenderer(BaseRenderer* newRenderer);
	void startEventListeningLoop();
	void startRenderingLoop(int minimumMillisecondsBetweenCallsToRender);



	~PixelWindow();

	private:
	void resetBitmapBitsAndGetNewScreenImageIfNeeded(int currentWidth, int currentHeight);
	void cleanupPointers();
	KeyInfo keyInformation;

	bool halt = false;
	Display *display;

	bool resizing = false;
	int windowWidth;
	int windowHeight;
	X11PixelSetter* pixelSetter=new X11PixelSetter();
	BaseRenderer* renderer=new EmptyRenderer();

	// X11 variables.
	Window window;
	int screen;
	XImage *screenImage;

	char* bitmapBits=nullptr;
	bool bitmapBitsDefined=false;
	int lastWindowWidth;
	int lastWindowHeight;
};

