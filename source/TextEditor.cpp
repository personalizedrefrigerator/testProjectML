/*
 * TextEditor.cpp
 *
 *  Created on: Jul 9, 2018
 */

#include "TextEditor.h"
#include <iostream>

void TextEditor::handleKeyChange(int keyCode)
{
	char characterVersion = static_cast<char>(keyCode);
	bool addToResult = true;

	int location = content.length() - fromEnd;

	// If the last character was a shift,
	if(lastKeyCode == 65506 || lastKeyCode == 65505)
	{
		characterVersion = shift(characterVersion);
	} // If enter,
	else if(keyCode == 65293)
	{
		characterVersion = '\n';

		if(hasNewLineCallback)
		{
			newLineCallback(content);

			location = content.length() - fromEnd;
			addToResult = false;
		}
	} // If backspace,
	else if(keyCode == 65288
			&& content.length() > 0 // And there is content,
			&& location > 0) // And it can be backspaced,
	{
		if(location < content.length())
		{
			content = content.substr(0, location - 1) + content.substr(location, content.length());
		}
		else
		{
			content = content.substr(0, content.length() - 1);
		}
		addToResult = false;
	} // If delete
	else if(keyCode == 65535)
	{
		if(location < content.length())
		{
			content = content.substr(0, location) + content.substr(location + 1, content.length());
			fromEnd --;
		}
		addToResult = false;
	} // If right
	else if(keyCode == 65363)
	{
		if(fromEnd > 0)
		{
			fromEnd--;
		}
		addToResult = false;
	} // If left
	else if(keyCode == 65361)
	{
		if(fromEnd < content.length())
		{
			fromEnd++;
		}
		addToResult = false;
	} // Up/down.
	else if(keyCode == 65362 || keyCode == 65364)
	{
		size_t nextNewLine = content.find('\n', location);
		size_t lastNewLine = content.rfind('\n', location - 1);
		size_t nextLastNewLine;

		if(lastNewLine == std::string::npos)
		{
			lastNewLine = 0;
		}

		nextLastNewLine = content.rfind('\n', lastNewLine - 1);

		int linePosition = location - lastNewLine;

		if(linePosition < 0)
		{
			linePosition = 0;
		}

		// Up.
		if(keyCode == 65362)
		{
			if(nextLastNewLine != std::string::npos)
			{
				if(linePosition + nextLastNewLine >= lastNewLine)
				{
					linePosition = lastNewLine - nextLastNewLine;
				}

				fromEnd = content.length() - (nextLastNewLine + linePosition);
			}
			else
			{
				fromEnd = content.length();
			}
		} // Down.
		else if(keyCode == 65364)
		{
			if(nextNewLine != std::string::npos)
			{
				size_t nextNextNewLine = content.find('\n', nextNewLine + 1);

				if(nextNextNewLine == std::string::npos)
				{
					nextNextNewLine = content.length();
				}

				if(nextNewLine + linePosition > nextNextNewLine)
				{
					linePosition = nextNextNewLine - nextNewLine;
				}

				fromEnd = content.length() - (nextNewLine + linePosition);
			}
			else
			{
				fromEnd = 0;
			}
		}

		if(fromEnd > content.length())
		{
			fromEnd = content.length();
		}

		if(fromEnd < 0)
		{
			fromEnd = 0;
		}

		addToResult = false;
	}// Otherwise, if a large keyCode,
	else if(keyCode > 300)
	{
		addToResult = false;
	}

	if(addToResult)
	{
		content = content.substr(0, location) + characterVersion + content.substr(location, content.length());
	}

	lastKeyCode = keyCode;
}

char TextEditor::shift(char given)
{
	if(shiftMap.find(given) == shiftMap.end())
	{
		unsigned int keyCode = static_cast<unsigned int>(given);
		int shiftDelta = 65 - 97;
		return static_cast<char>(keyCode + shiftDelta);
	}
	else
	{
		return shiftMap.at(given);
	}
}

void TextEditor::render(PixelSetter& display, int x, int y, int maxWidth)
{
	textRenderer.setCursorLocation(content.length() - fromEnd);
	textRenderer.drawWrapped(content, x, y, display, pixelWidth, pixelHeight, maxWidth);
}

void TextEditor::setTextSize(unsigned int pxWidth, unsigned int pxHeight)
{
	pixelWidth = pxWidth;
	pixelHeight = pxHeight;
}

void TextEditor::setNewLineCallback(std::function<void(std::string&)> callback)
{
	newLineCallback = callback;
	hasNewLineCallback = true;
}
