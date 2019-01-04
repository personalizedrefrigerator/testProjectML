#pragma once

#include "TextDrawer.h"

#include "PixelSetter.h"
#include "BaseRenderer.h"
#include "TextDrawer.h"
#include "TransformedPixelSetter.h"
#include "CUDAColorGrapherRenderer.h"
#include "TextEditor.h"
#include "NeuralNetwork.h"
#include "Grapher.h"
#include <string>

class NeuralNetworkRenderer : public BaseRenderer
{
private:
	TextDrawer textRenderer = TextDrawer();
	TextEditor textEdit;
	Grapher progressGraph {1000};
	Grapher progressGraph2 {100};
	Grapher progressGraph3 {100};
	//CUDAColorGrapherRenderer subRenderer;
	TransformedPixelSetter * scaledPixelSetter = nullptr;
	NeuralNetwork2::NeuralNetwork network = {3, 25, 1};
	unsigned int count = 0;

public:
	NeuralNetworkRenderer();
	void render(PixelSetter* pixelSetter, int width, int height);
	~NeuralNetworkRenderer() { if(scaledPixelSetter != nullptr) { delete scaledPixelSetter; } };
};
