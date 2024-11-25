#include "Engine.h"

const Time Engine::TimePerFrame = milliseconds(1.f / 60.f);

Engine::Engine(RenderWindow& game, int& pagenum, Setting& setting) : game(game), pagenum(pagenum), setting(setting) {
    game.setFramerateLimit(FPS);
    startGame();

    maxLevels = 4;
    name = setting.getName();
    if (name == "") {
        name = "no_name";
    }

    tx3.loadFromFile("../Data/bg_end.png");
    tx2.loadFromFile("../Data/bg_game.png");
    tx1.loadFromFile("../Data/s.png");

    bgEnd.setTexture(tx3);
    bgGame.setTexture(tx2);

    eat_sound.loadFromFile("../Data/apple-2.wav");
    sfx.setBuffer(eat_sound);

    gameover_sound.loadFromFile("../Data/dead_sound.ogg");
    sfx1.setBuffer(gameover_sound);

    mainFont.loadFromFile("../Data/Game Shark.otf");
    minorFont.loadFromFile("../Data/DANKI.otf");

    // Player name
    setupText(&titleText, mainFont, name, 25, Color::White);
    centerText(titleText, 800, -7);

    // Current Level Text
    setupText(&currentLevelText, mainFont, "Level 1", 25, Color::White);
    currentLevelText.setPosition(Vector2f(15, -7));

    // Score Text
    setupText(&scoreText, mainFont, to_string(scoreThisLevel), 25, Color::White);
    scoreText.setPosition(Vector2f(800 - scoreText.getGlobalBounds().width - 15, -7));

    // Game Over Text
    setupOutlinedText(gameOverText, minorFont, "GAME OVER", 72, Color::Cyan);
    centerText(gameOverText, 800, 50);

    // Game Win Text
    setupOutlinedText(gameWinText, minorFont, "YOU WIN", 72, Color::Cyan);
    centerText(gameWinText, 800, 50);

    // Score End Text
    setupText(&score_end, mainFont, "", 28, Color::Yellow);
    //centerText(score_end, 800, 100);

    //TOP RANKING
    setupOutlinedText(topRankingText, minorFont, "Top ranking", 32, Color(100, 255, 100), Color::Black);
    centerText(topRankingText, 800, 430);
    topRankingBounds = topRankingText.getLocalBounds();
    topRankingBounds.left = 800 / 2 - (topRankingBounds.width) / 2;
    topRankingBounds.top = 430;

    //TRY AGAIN
    setupOutlinedText(tryAgainText, minorFont, "Try again", 32, Color(100, 255, 100), Color::Black);
    centerText(tryAgainText, 800, 360);
    tryAgainBounds = tryAgainText.getLocalBounds();
    tryAgainBounds.left = 800 / 2 - (tryAgainBounds.width) / 2;
    tryAgainBounds.top = 360;

    //EXIT
    setupOutlinedText(exitText, minorFont, "Exit", 32, Color(100, 255, 100), Color::Black);
    centerText(exitText, 800, 500);
    exitBounds = exitText.getLocalBounds();
    exitBounds.left = 800 / 2 - exitBounds.width / 2;
    exitBounds.top = 500;
}


void Engine::startGame() {
    speed = setting.getInputSpeed();
    SnakeDir = Direction::DOWN;
    cPoint = 0;
    delay_time = Time::Zero;
    wallSection.clear();
    directQueue.clear();
    scoreThisLevel = 0;
    scoreTotal = 0;
    currentLevel = 1;
    loadLevel(currentLevel);
    createSnake();
    appearFruit();
    currentState = GameState::RUN;
    lastState = currentState;
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    scoreText.setString(to_string(scoreThisLevel));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
}

void Engine::createSnake() {
    snake.clear();

    snake.emplace_back(Vector2f(100, 100));
    snake.emplace_back(Vector2f(100, 80));
    snake.emplace_back(Vector2f(100, 60));
}

void Engine::addSnake() {
    Vector2f newPointpos = snake[snake.size() - 1].getPos();
    snake.emplace_back(newPointpos);
}

void Engine::appearFruit() {
    Vector2f Fruitresolution = Vector2f(800 / 20 - 2, 600 / 20 - 2);
    Vector2f newlocation;
    bool badlocation = false;
    srand(time(nullptr));

    do {
        badlocation = false;
        //create random fruit
        newlocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)Fruitresolution.x) * 20);
        newlocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)Fruitresolution.y) * 20);

        // o trong than ran
        for (auto& s : snake) {
            if (s.getShape().getGlobalBounds().intersects(Rect<float>(newlocation.x, newlocation.y, 20, 20))) {
                badlocation = true;
                break;
            }

        }

        //Check in the wall
        for (auto& w : wallSection) {
            if (w.getShape().getGlobalBounds().intersects(Rect<float>(newlocation.x, newlocation.y, 20, 20))) {
                badlocation = true;
                break;
            }
        }

    } while (badlocation);
    fruit.setPos(newlocation);
}

void Engine::togglePause() {
    if (currentState == GameState::RUN) {
        lastState = currentState;
        currentState = GameState::PAUSED;
    }
    else if (currentState == GameState::PAUSED) {
        currentState = lastState;
    }
}


void Engine::checkLevelFiles() {
    ifstream levelsManifest("../Data/levels.txt");
    ifstream testFile;
    for (string manifestLine; getline(levelsManifest, manifestLine);) {
        testFile.open("../Data/levels/" + manifestLine);
        if (testFile.is_open()) {
            levels.emplace_back("../Data/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

void Engine::beginNextLevel() {
    currentLevel += 1;
    wallSection.clear();
    directQueue.clear();
    speed += 1;
    SnakeDir = Direction::DOWN;
    cPoint = 0;
    scoreThisLevel = 0;

    loadLevel(currentLevel);
    appearFruit();
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    FloatRect scoreTextBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(Vector2f(800 - scoreTextBounds.width - 15, -7));
}

void Engine::loadLevel(int levelNumber) {
    levels.push_back("../Data/levels/level1.txt");
    levels.push_back("../Data/levels/level2.txt");
    levels.push_back("../Data/levels/level3.txt");

    unsigned int num = levelNumber - 1;
    string levelFile = levels[num];
    ifstream level(levelFile);
    string line;
    snake.clear();
    Vector2f newHead;
    vector<Vector2f> newSnakeBody;
    if (level.is_open()) {

        for (int y = 0; y < 30; y++) {
            getline(level, line);
            for (int x = 0; x < 40; x++) {
                if (line[x] == 'x') {
                    wallSection.emplace_back(Wall(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
                }
            }
        }
    }
    level.close(); 
    createSnake();
}


void Engine::saveScore() {
    loadScore(Topscore); // them tiep vao file Highscore
    highscore.push_back(Player(name, scoreTotal));

    sort(highscore.begin(), highscore.end(), [](const Player& a, const Player& b) {
        return a.scoreP > b.scoreP;
        });

    if (highscore.size() > 10) {
      highscore.resize(10);
    }

    ofstream file("../Data/Highscore.txt");
    if (file.is_open()) {
        for (const auto& entry : highscore) {
            file << entry.nameP << " " << entry.scoreP << "\n";
        }
    }
}

void  Engine::loadScore(RenderWindow& Topscore) {
    ifstream file("../Data/Highscore.txt");
    if (file.is_open()) {
        string playerName;
        int playerScore;

        while (file >> playerName >> playerScore) {
            highscore.push_back(Player(playerName, playerScore));
        }
        file.close();
        for (int i = 0; i < 3; i++) {
            const auto& player = highscore;
            setupText(&topText[i], mainFont, player[i].getName() + " " + to_string(player[i].getScore()), 22, Color{ 255,204,0 });
            FloatRect topTextBounds = topText[i].getLocalBounds();
            topText[i].setPosition(600 / 2 - topTextBounds.width / 2,150 + 70 * i);

        }
    }
}

void Engine::topRanking() {
    RenderWindow Topscore;
    Topscore.create(VideoMode(600, 450), "TOP RANKING", Style::Default);
    tx2.loadFromFile("../Data/bg_top.png");
    bgTop.setTexture(tx2);

    while (Topscore.isOpen()) {
        Event event;
        while (Topscore.pollEvent(event)) {
            if (event.type == Event::Closed) {
                Topscore.close();
                break;
            }
        }
        loadScore(Topscore);
        Topscore.draw(bgTop);
        Topscore.draw(topText[0]);
        Topscore.draw(topText[1]);
        Topscore.draw(topText[2]);

        Topscore.display();
    }

}

void Engine::setupText(Text* textItem, const Font& font, const String& value, int size, Color colour) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(colour);

}


void Engine::Play() {
    Clock clock;
 
    while (game.isOpen()) {
        Time dt = clock.restart();
\
        if (currentState == GameState::PAUSED || currentState == GameState::GAMEOVER || currentState == GameState::GAMEWIN) {
            //pause roi an pause tiep se tiep tuc
            Input();
            //ve gameover screen
            if (currentState == GameState::GAMEOVER || currentState == GameState::GAMEWIN) {
                score_end.setString("Your score is: " + to_string(scoreTotal));
                centerText(score_end, 800, 150);
                Draw();

            }
            sleep(milliseconds(2));
            continue;
        }
        delay_time += dt;
        Input();
        Update();
        Draw();
    }
}

void Engine::centerText(Text& text, float screenWidth, float offsetY) {
    FloatRect textBounds = text.getGlobalBounds();
    text.setPosition(Vector2f(screenWidth / 2 - textBounds.width / 2, offsetY));
}

void Engine::setupOutlinedText(Text& text, Font& font, const string& content, unsigned int size, Color fillColor, Color outlineColor, float outlineThickness) {
    setupText(&text, font, content, size, fillColor);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
}

string Engine::getName() {
    return name;
}