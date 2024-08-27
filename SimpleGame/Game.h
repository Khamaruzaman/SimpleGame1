#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

/*
	Wrapper class
*/

class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Game logic
	unsigned point;
	unsigned health;
	bool gameOver;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnimies;
	bool mouseHold;

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	// Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Private functions
	void initVariables();
	void initFonts();
	void initText();
	void initWindow();
	void initEnemy();

public:
	// Constuctors / Distructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running();

	// Functions
	void pollEvents();
	void spawnEnemy();

	void updateMousePosition();
	void updateEnemy();
	void updateText();
	void update();

	void renderEnemy(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void render();
};

