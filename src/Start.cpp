#include "Start.h"
#include "Menu.h"

class LoadingBar : public Drawable {
public:
    float width, height;
    RectangleShape outline;
    RectangleShape bar;

    float totalWidth;
    float barWidth;

    LoadingBar() : width(200), height(20), totalWidth(200), barWidth(20) {
        // Set up the outline
        outline.setSize(sf::Vector2f(width, height));
        outline.setOutlineThickness(2.0f);
        outline.setPosition(300, 380);
        outline.setOutlineColor(Color::Black);

        // Set up the bar
        bar.setFillColor(Color(100, 255, 100));
        bar.setSize(sf::Vector2f(barWidth, height - 4));
        bar.setPosition(outline.getPosition() + Vector2f(2.0f, 2.0f));
    }

    void update(float progress) {
        if (progress >= 0.0f && progress <= 99.0f) {
            barWidth = (progress / 100.0f) * totalWidth;
            bar.setSize(Vector2f(barWidth, height - 4.0f));
        }
    }

    bool isComplete() {
        const float epsilon = 4.0f;
        return barWidth >= (totalWidth - epsilon);
    }

    void draw(RenderTarget& target, RenderStates states) const {
        target.draw(outline, states);
        target.draw(bar, states);
    }
};



void Start::starttheGame() {

    window.create(sf::VideoMode(800, 600), "Snake Game");
    window.setFramerateLimit(60);

    backgroundMain.loadFromFile("../Data/SNAKE GAME.png");
    Sprite bgMain(backgroundMain);

    LoadingBar B;
    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        float elapsedTime = clock.getElapsedTime().asSeconds();
        float progress = (elapsedTime / 3.0f) * 100.0f; 
        B.update(progress);
        window.draw(bgMain);
        window.draw(B);
        window.display();
        if (B.isComplete()) {
            break;
        }
    }
    window.close();
    Menu menu(800, 600);
    menu.runMenu();  
}

