#include "Grapher.h"

Grapher::Grapher(unsigned int maxPoints)
{
	data.resize(maxPoints);
}

void Grapher::addPoint(double y)
{
	unsigned int dataSize = data.size();
	for(unsigned int pointIndex = 1; pointIndex < dataSize; pointIndex++)
	{
		data[pointIndex - 1] = data[pointIndex];
	}

	data[dataSize - 1] = y;
}

void Grapher::setBarLocation(double y)
{
	barY = y;
}

void Grapher::setMaxY(double y)
{
	maxY = y;
}

void Grapher::setColors(Color newPointColor, Color newBarColor)
{
	pointColor = newPointColor;
	barColor = newBarColor;
}

void Grapher::render(PixelSetter& givenPixelSetter, int x, int y, unsigned int width, unsigned int height) const
{
	unsigned int dataSize = data.size();


	givenPixelSetter.setColor(barColor.red, barColor.green, barColor.blue);

	givenPixelSetter.drawRect(x, y, width, padding + 1, givenPixelSetter);


	int lastY = y, lastX = x;
	int currentY, currentX;
	int deltaY;
	double currentData;

	for(unsigned int pointIndex = 0; pointIndex < dataSize; pointIndex++)
	{

		givenPixelSetter.setColor(pointColor.red, pointColor.green, pointColor.blue);

		currentData = -data[pointIndex];

		if(currentData > maxY)
		{
			currentData = maxY;
		}
		else if(currentData < -maxY)
		{
			currentData = -maxY;
		}

		currentY = currentData * height / maxY + y;
		currentX = pointIndex * width / dataSize + x;

		deltaY = currentY - lastY;

		if(deltaY < 0)
		{
			deltaY *= -1;
		}
		else if(deltaY == 0)
		{
			deltaY = 1;
		}

		givenPixelSetter.drawRect(lastX, lastY, currentX - lastX + padding, deltaY + padding, givenPixelSetter);

		lastY = currentY;
		lastX = currentX;
	}
}
