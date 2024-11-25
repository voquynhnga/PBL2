#include "Fruit.h"

Fruit::Fruit() {
    Vector2f startPos(400, 300);
    sprite.setSize(Vector2f(20, 20));
    sprite.setPosition(startPos);
    tx_apple.loadFromFile("../Data/apple.png");
    sprite.setTexture(&tx_apple);

}

void Fruit::setPos(sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}
RectangleShape Fruit::getSprite() {
    return sprite;
}