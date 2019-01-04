#pragma once

#include "PixelSetter.h"
#include <vector>

class Grapher
{
private:
	std::vector<double> data;
	double barY = 0.0;
	double maxY = 1.0;
	unsigned int padding = 1;
	Color pointColor {255, 0, 0};
	Color barColor {0, 255, 0};
public:
	Grapher(unsigned int maxPoints);
	void addPoint(double y);
	void setBarLocation(double y);
	void setMaxY(double y);
	void setPixelPadding(unsigned int pixelPadding) { padding = pixelPadding; };
	void setColors(Color pointColor, Color barColor);
	std::vector<double>& getData() { return data; };
	void render(PixelSetter& givenPixelSetter, int x, int y, unsigned int width, unsigned int height) const;
};
