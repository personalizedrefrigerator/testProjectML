#pragma once

#include "PixelSetter.h"
#include "TextDrawer.h"

#include <string>
#include <unordered_map>
#include <functional>

class TextEditor
{
public:
	TextEditor() : content(""), lastKeyCode(0) {};
	void handleKeyChange(int keyCode);
	void render(PixelSetter& display, int x, int y, int maxWidth);
	std::string& getContent() { return content; };
	void setTextSize(unsigned int pxWidth, unsigned int pxHeight);
	void setNewLineCallback(std::function<void(std::string&)> callback);

private:
	TextDrawer textRenderer = TextDrawer();
	char shift(char character);
	std::unordered_map<char, char> shiftMap = {{'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
			{'/', '?'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
			{',', '<'}, {'.', '>'}, {'\\', '|'}, {';', ':'}, {'\'', '"'}, {'-', '_'}, {'=', '+'},
			{'[', '{'}, {']', '}'}, {'`', '~'}};
	std::string content;
	int lastKeyCode;
	int fromEnd = 0;
	unsigned int pixelWidth = 1, pixelHeight = 2;
	std::function<void(std::string&)> newLineCallback;
	bool hasNewLineCallback = false;
};
