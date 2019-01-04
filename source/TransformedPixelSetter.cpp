#include "TransformedPixelSetter.h"
#include <utility>

Color TransformedPixelSetter::getAt(int x, int y) const
{
	std::pair<double, double> point (x, y);

	std::pair<double, double> translatedPoint = point * transformMatrix;

	unsigned int pointX = static_cast<unsigned int>(translatedPoint.first),
			pointY = static_cast<unsigned int>(translatedPoint.second);

	return PixelSetterWrapper::getAt(pointX, pointY);
}

void TransformedPixelSetter::setAt(int x, int y)
{
	std::pair<double, double> point (x, y);

	std::pair<double, double> translatedPoint = point * transformMatrix;

	unsigned int pointX = static_cast<unsigned int>(translatedPoint.first + translateX),
			pointY = static_cast<unsigned int>(translatedPoint.second + translateY);

	PixelSetterWrapper::setAt(pointX, pointY);
}
