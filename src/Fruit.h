#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Fruit {
public:
    Texture tx_apple;
    RectangleShape sprite;
public:
    Fruit();
    void setPos(Vector2f newPos);
    RectangleShape getSprite();
};

