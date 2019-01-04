/*
 * CUDAColorGrapherRenderer.cpp
 *
 *  Created on: Jun 29, 2018
 */

#include "CUDAColorGrapherRenderer.h"
#include <chrono>
#include "TextDrawer.h"
#include <sstream>

__global__ void fillPixels(char * pixelData, int width, int height, float tX, float tY, float zoomX, float zoomY, float time)
{
	int index = blockDim.x * blockIdx.x + threadIdx.x;
	int dataX = index % width;
	int dataY = index / width;
	float x = (dataX + tX) * zoomX;
	float y = (dataY + tY) * zoomY;

	if(dataX + dataY*width*4 + 2 < width * height * 4)
	{
		pixelData[dataY*width*4 + dataX*4 + 2] = (sinf(tanf(x*y - x) * cosf(x/(sinf(time/10 + y))) - tanf(y))/((sin(x*x*y-y*tan(time/100))+5)/6) + 1) * 256 / 2;
		pixelData[dataY*width*4 + dataX*4] = 0.5 * ((cosf(x/(y+sin(time/5))) + tanf(sin(time/50 - x) * y / (x+1))) / 2 + 1)*256;
		pixelData[dataY*width*4 + dataX*4 + 1] = 0.5 * (sinf(x*y + tanf(x*x*x - y*y) + cosf(tanf(x/(x+y+sinf(time/2.0)))*cosf(time))) + 1)*256;
	}
}

void CUDAColorGrapherRenderer::render(PixelSetter* pixelSetter, int width, int height)
{
	if(width * height == 0)
	{
		return;
	}

	if(invertedPixelSetter == nullptr)
	{
		invertedPixelSetter = new InvertedPixelSetter(pixelSetter);

		// Multiply the values of red, green, and blue to make text more visible.
		invertedPixelSetter->multiplyRed = 1.0f;
		invertedPixelSetter->multiplyGreen = 0.0f;
		invertedPixelSetter->multiplyBlue = 1.0f;
	}

	invertedPixelSetter->setPixelSetter(pixelSetter);

	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration durationSinceEpoch = startTime.time_since_epoch();
	long time = std::chrono::duration_cast<std::chrono::microseconds>(durationSinceEpoch).count();
	//long startTimeSinceEpoch = time; // Explicitly store the starting time.

	time /= 1000; // Convert time to milliseconds.

	long tX = -width/2;
	long tY = -height/2 + sin(time / 5000.0) * 250;
	zoom = (tan(time / 10000.0) + 1) / 100.0;
	float xZoom = zoom * cos(sin(time/1000.0/6.28)/2);

	char * pixelData = pixelSetter->getDataPtr();

	size_t length = width * height * sizeof(float);

	char * devicePixelData;
	cudaMalloc(&devicePixelData, length);

	int threadsPerBlock = 256;
	int blocksPerGrid = width * height / threadsPerBlock;
	fillPixels<<<blocksPerGrid, threadsPerBlock>>>(devicePixelData, width, height, tX, tY, xZoom, zoom, time/1000.0f);

	cudaDeviceSynchronize();

	cudaMemcpy(pixelData, devicePixelData, length, cudaMemcpyDeviceToHost);

	cudaFree(devicePixelData);

	// Find the elapsed time.
	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	long endTimeSinceEpoch = (std::chrono::duration_cast<std::chrono::microseconds>(endTime.time_since_epoch())).count();
	double millisecondDelta = (endTimeSinceEpoch - lastTimeSinceEpoch) / 1000.0;
	lastTimeSinceEpoch = endTimeSinceEpoch;

	// Calculate the frames per second.
	float framesPerSecond = millisecondDelta;

	if(millisecondDelta != 0)
	{
		framesPerSecond = 1 / (millisecondDelta / 1000.0);
	}

	// Display it.
	std::stringstream outputText;
	outputText << "FPS: " << framesPerSecond << ", size: ";
	outputText << "(" << width << ", " << height << ")";

	pixelSetter->setColor(200, 200, 0);
	textRenderer.draw(outputText.str(), 0, 0, *invertedPixelSetter, 2, 2);
}

CUDAColorGrapherRenderer::~CUDAColorGrapherRenderer()
{
	// Deconstruct all variables
	if(invertedPixelSetter != nullptr)
	{
		delete invertedPixelSetter;
	}
}

