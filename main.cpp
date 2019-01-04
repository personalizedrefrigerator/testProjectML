#include <iostream>
#include "PixelWindow.h"
#include "CUDAColorGrapherRenderer.h"
#include "NeuralNetworkRenderer.h"
#include <chrono>
#include "Matrix.h"

int main(int argsLength, char * argc[])
{
	testMatricies();
	PixelWindow mainWindow = PixelWindow();
	mainWindow.create(500, 700);
	BaseRenderer * renderer = new NeuralNetworkRenderer();//new CUDAColorGrapherRenderer();//
	mainWindow.setRenderer(renderer);
	mainWindow.startEventListeningLoop();
	//mainWindow.startRenderingLoop(0);
	delete renderer;

	return 0;
}
