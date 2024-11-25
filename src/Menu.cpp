#include "Menu.h"

Menu::Menu(float width, float height) {
	game.create(VideoMode(800, 600), "Snake Game");
	mainFont.loadFromFile("../Data/Game Shark.otf");
	backgroundMenu.loadFromFile("../Data/bgbg.png");
	bg.setTexture(backgroundMenu);

	setupText(&mainMenuText[0], mainFont, "Play", 30, Color::White);
	setupText(&mainMenuText[1], mainFont, "Setting", 30, Color::White);
	setupText(&mainMenuText[2], mainFont, "Instruction", 30, Color::White);
	setupText(&mainMenuText[3], mainFont, "Exit", 30, Color::White);


	for (int i = 0; i < 4; i++) {
		mainMenuTextBounds[i] = mainMenuText[i].getLocalBounds();
		mainMenuTextBounds[i].width += 10;
		mainMenuTextBounds[i].height += 10;
		mainMenuTextBounds[i].top = 150 + 100*i;
		mainMenuTextBounds[i].left = width / 2 - mainMenuTextBounds[i].width / 2;
		mainMenuText[i].setPosition(Vector2f(mainMenuTextBounds[i].left, mainMenuTextBounds[i].top));
		mainMenuText[i].setOutlineColor(Color::Black);
		mainMenuText[i].setOutlineThickness(2);
	}

}

void Menu::DrawMenu() {
	for (int i = 0; i < Max_menu; i++) {
		game.draw(mainMenuText[i]);
	}
}

void Menu::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) {
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(colour);

}


void Menu::runMenu() {
	int pagenum = 100;
	Setting setting(game, pagenum);

	while (pagenum == 100) {
		while (game.isOpen()) {
			Event event;
			while (game.pollEvent(event)) {

				if (event.type == Event::Closed) {
					game.close();
					break;
				}
				//select 
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Button::Left) {
						Vector2i mousePosition = Mouse::getPosition(game);
						if (mainMenuTextBounds[0].contains(Vector2f(mousePosition))) {
							pagenum = 0;
						}
						if (mainMenuTextBounds[1].contains(Vector2f(mousePosition))) {
							pagenum = 1;
						}
						if (mainMenuTextBounds[2].contains(Vector2f(mousePosition))) {
							pagenum = 2;
						}
						if (mainMenuTextBounds[3].contains(Vector2f(mousePosition))) {
							pagenum = -1;
							break;
						}
					}
				}
				if (event.type == Event::MouseMoved) {
					Vector2i mouseMovePosition = Mouse::getPosition(game);
					bool touch = false;

					//mouse move 
					for (int i = 0; i < Max_menu; ++i) {
						if (mainMenuTextBounds[i].contains(Vector2f(mouseMovePosition))) {
							mainMenuText[i].setFillColor(Color{ 255,204,0 });
							mainMenuText[i].setCharacterSize(38);
							mainMenuText[i].setOutlineThickness(5);
							touch = true;
						}
						else {
							mainMenuText[i].setFillColor(Color::White);
							mainMenuText[i].setCharacterSize(30);
							mainMenuText[i].setOutlineThickness(2);
						}
					}

					if (!touch) {
						for (int i = 0; i < Max_menu; ++i) {
							mainMenuText[i].setFillColor(Color::White);
							mainMenuText[i].setCharacterSize(30);
							mainMenuText[i].setOutlineThickness(2);
						}
					}
				}
			}
			game.clear();
			if (pagenum != 100) {
				break;
			}
			game.draw(bg);
			DrawMenu();
			game.display();
		}
		if (pagenum == -1) {
			game.close();
		}
		if (pagenum == 0) {
			Engine engine(game, pagenum, setting);
			engine.Play();
		}
		if (pagenum == 1) {
			setting.Speed();
		}
		if (pagenum == 2) {
			Instruction instruction(game,pagenum);
			instruction.Show();
		}

	}
}


