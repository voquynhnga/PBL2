#pragma once
#include <SFML/Graphics.hpp>
#include "Setting.h"
#include"Engine.h"
#include "Instruction.h"

using namespace std;
using namespace sf;

#define Max_menu 4

class Menu {
public:
	FloatRect mainMenuTextBounds[Max_menu];
	RenderWindow game;

	Text mainMenuText[Max_menu];
	Font mainFont;

	Texture backgroundMenu;
	Sprite bg;

	Menu(float width, float height);
	
	void DrawMenu();
	void runMenu();
	void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);

};

