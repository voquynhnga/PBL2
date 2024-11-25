#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Point {
private:
    Vector2f pos;
    RectangleShape point;
    Vector2f size;
public:
    Point();
    Point(Vector2f startPos);
    Vector2f getPos();
    void setPos(Vector2f newPos);
    RectangleShape getShape();
    void update();
    void setTexture(Texture* texture);
    void setSize(Vector2f size);
    void setRotation(float angle);
};

