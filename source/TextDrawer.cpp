#include "TextDrawer.h"
#include <iostream>

TextDrawer::TextDrawer()
{
	for(unsigned int letterIndex = 0; letterIndex < charactersNumber; letterIndex++)
	{
		indicies.emplace(characters[letterIndex][0].at(0), letterIndex);
	}
}

void TextDrawer::setCursorLocation(int location)
{
	cursorLocation = location;
}

unsigned int TextDrawer::draw(std::string textArg, int x, int y,
		PixelSetter &pixelSetter, unsigned int pxWidth, unsigned int pxHeight)
{
	const unsigned long length = textArg.length();

	const char* text = textArg.c_str();
	int originalX = x;
	unsigned int maxX = 0;

	for (unsigned int letter = 0; letter < length; letter++)
	{
		if (text[letter] == '\n')
		{
			y += charHeight*pxHeight + pxHeight;
			x = originalX;
			continue;
		}

		if(letter == cursorLocation)
		{
			drawCursor(x - charWidth / 2, y, pxWidth, pxHeight, pixelSetter);
		}

		drawLetter(text[letter], x, y, pxWidth, pxHeight, pixelSetter);
		x += charWidth*pxWidth+pxWidth;

		if(x > maxX)
		{
			maxX = x;
		}
	}
	//delete text;

	return maxX;
};

void TextDrawer::drawLetter(char letter, int startX, int startY, unsigned int pixelW,
		unsigned int pixelH, PixelSetter & pixelSetter)
{
	unsigned int i = indicies[letter];
	unsigned int y;
	for (unsigned int x = 0; x < charWidth; x++)
	{
		for (y = 0; y < charHeight; y++)
		{
			// If the pixel is on,
			if (characters[i][y + 1][x] == '1')
			{
				pixelSetter.drawRect(x*pixelW + (startX), y*pixelH + startY, pixelW, pixelH, pixelSetter);
			}
		}
	}
};


unsigned int TextDrawer::drawWrapped(std::string text, int x, int y,
		PixelSetter & pixelSetter, unsigned int pixelWidth, unsigned int pixelHeight, unsigned int maxWidth)
{
	int lineX = x;
	const int leftX = x;
	int maxX = leftX + maxWidth;
	int wordStartX = x;

	int lineHeight = (pixelHeight + 1) * charHeight;

	unsigned int textSize = text.size();
	std::string word = "";

	char currentChar;

	unsigned int otherIndex, wordSize, wordTotalWidth;
	int wordX;
	const int deltaX = charWidth * (pixelWidth + 1);
	int line = 1;
	int extra = 0;

	wordSize = 0;
	bool wrap = false;
	bool truncateWrap = false;

	for(unsigned int index = 0; index < textSize; index++)
	{
		currentChar = text[index];

		if(currentChar != ' ' && currentChar != '\n')
		{
			word += currentChar;
			wordSize++;
			lineX += deltaX;
		}

		wordTotalWidth = wordSize * (deltaX + 1);

		if(lineX + deltaX >= maxX && wordTotalWidth < maxX)
		{
			y += lineHeight;
			lineX = leftX;
			wordStartX = leftX;
		}

		if(wordTotalWidth >= maxX)
		{
			wrap = true;
			truncateWrap = true;
		}
		else if(index == textSize - 1)
		{
			wrap = true;
		}
		else if(currentChar == '\n')
		{
			wrap = true;
		}
		else
		{
			wrap = false;
		}

		if(currentChar == ' ' || wrap)
		{
			wordX = wordStartX;
			wordSize = word.size();
			for(otherIndex = 0; otherIndex < wordSize; otherIndex++)
			{
				extra = (index < textSize - 1 && !truncateWrap) ? 0 : 1;
				if(index - wordSize + otherIndex + extra == cursorLocation)
				{
					drawCursor(wordX - deltaX / 4, y, pixelWidth, pixelHeight, pixelSetter);
				}

				if(word[otherIndex] != ' ' && word[otherIndex] != '\n')
				{
					drawLetter(word[otherIndex], wordX, y, pixelWidth, pixelHeight, pixelSetter);
				}
				else
				{
					break;
				}

				wordX += deltaX;
			}

			wordX += deltaX;

			word.clear();
			wordSize = 0;
			wordStartX = wordX;
			lineX = wordX;

			if(index == cursorLocation && index < textSize - 1)
			{
				drawCursor(lineX - deltaX, y, pixelWidth, pixelHeight, pixelSetter);
			}
			else if(index == textSize - 1 && index + 1 == cursorLocation)
			{
				drawCursor(lineX - deltaX, y, pixelWidth, pixelHeight, pixelSetter);
			}

			truncateWrap = false;
		}

		if(currentChar == '\n')
		{
			y += lineHeight;
			lineX = leftX;
			wordStartX = lineX;
		}
	}

	return y;
}

void TextDrawer::drawCursor(int x, int y, unsigned int pixelWidth, unsigned int pixelHeight, PixelSetter& pixelSetter) const
{
	pixelSetter.drawRect(x, y - pixelHeight / 2, pixelWidth, pixelHeight * (charHeight + 2), pixelSetter);
}
