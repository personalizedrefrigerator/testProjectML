#pragma once

#include "PixelSetter.h"

// A wrapper around another PixelSetter.

class PixelSetterWrapper : public PixelSetter
{
private:
	PixelSetter * givenPixelSetter; // PixelSetterWrapper is NOT responsible for deleting givenPixelSetter.
public:
	PixelSetterWrapper(PixelSetter * wrapAround) : givenPixelSetter(wrapAround) {};
	virtual void setAt(int x, int y) override;
	virtual Color getAt(int x, int y) const override;
	virtual void setColor(int r, int g, int b) override;
	virtual char * getDataPtr() const override;
	virtual long getDataLength() const override;

	// Warning: setPixelSetter does NOT delete givenPixelSetter!
	bool setPixelSetter(PixelSetter * newPixelSetter); // Returns true on success.
};
