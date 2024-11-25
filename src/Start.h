#pragma once
#include <SFML/Graphics.hpp>
#include"Menu.h"

using namespace sf;
using namespace std;

class Start
{
public:
	RenderWindow window;
	Texture backgroundMain;
	Sprite bgMain;

public:
	void starttheGame();
};

