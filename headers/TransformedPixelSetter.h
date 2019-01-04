#pragma once

#include "PixelSetterWrapper.h"
#include "Matrix.h"
#include "Color.h"

class TransformedPixelSetter : public PixelSetterWrapper
{
public:
	Matrix<double, 2, 2> transformMatrix;
	double translateX = 0.0, translateY = 0.0;

	TransformedPixelSetter(PixelSetter * wrapAround) : PixelSetterWrapper(wrapAround) { transformMatrix.toIdentity(); };

	void setAt(int x, int y) override;
	Color getAt(int x, int y) const;
};
