#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<random>
#include<fstream>

#include "Vector.h"
#include "Deque.h"
#include "Menu.h"
#include "Point.h"
#include "Fruit.h"
#include "Wall.h"
#include "Setting.h"

using namespace std;
using namespace sf;



class Engine 
{
private:
    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    Time delay_time;

    RenderWindow& game;
    RenderWindow Topscore;
    int& pagenum;
    Setting& setting;
 

    vector <Player> highscore;
    Vector<Point> snake;
    Deque<int> directQueue; // queue cho phim nhan
    Vector<Wall> wallSection;
    vector<string> levels;




    float width;
    float height;


    int SnakeDir;
    int speed;
    string name;

    int cPoint; //count point
    long long int scoreThisLevel;
    long long int scoreTotal;


    Fruit fruit;
    int currentState;
    int lastState;

    int currentLevel;
    int maxLevels;

    //Text
    Font mainFont;
    Font minorFont;
    Text titleText;
    Text currentLevelText;
    Text scoreText;
    Text gameOverText;
    Text tryAgainText;
    Text topRankingText;
    Text score_end;
    Text gameWinText;
    Text exitText;
    Text topText[3];

    FloatRect tryAgainBounds;
    FloatRect topRankingBounds;
    FloatRect exitBounds;
    RectangleShape textShape1;
    RectangleShape textShape2;
    RectangleShape textShape3;
    RectangleShape snakeHead;

    Texture tx1;
    Texture tx2;
    Texture tx3;
    Texture tx4;


    Sprite bgEnd;
    Sprite bgGame;
    Sprite bgTop;

    //Sound
    SoundBuffer eat_sound;
    Sound sfx;

    SoundBuffer gameover_sound;
    Sound sfx1;
    const unsigned int targetScore = 50; 



public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { RUN, PAUSED, GAMEOVER, GAMEWIN };
    Engine(RenderWindow& game, int& pagenum, Setting& setting);
    void Input();
    void Update();
    void Draw();

    void setupText(Text* textItem, const Font& font, const String& value, int size, Color colour);
    void centerText(Text& text, float screenwidth, float offsetY = 0);
    void setupOutlinedText(Text& text, Font& font, const std::string& content, unsigned int size, Color fillColor, Color outlineColor = Color::Black, float outlineThickness = 2);
    void addDir(int newDir);
    void createSnake();
    void addSnake();
    void appearFruit();
    void checkLevelFiles();
    void loadLevel(int levelNumber);
    void beginNextLevel();
    void  saveScore();
    void loadScore(RenderWindow& Topscore);
    string getName();
    void topRanking();
    void startGame();
    void togglePause();
	void Play();

};

