#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;

	// Game logic
	this->point = 0;
	this->health = 3;
	this->gameOver = false;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnimies = 5;
	this->mouseHold = false;
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "Failed to load fonts\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(20);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("");
}

void Game::initWindow()
{
	this->videoMode.height = 480;
	this->videoMode.width = 640;
	this->window = new sf::RenderWindow(this->videoMode, "Game Demo", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(150.f, 150.f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(1.f);
}

// Constuctors / Distructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemy();

}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running()
{
	return this->window->isOpen();
}

// Functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

void Game::spawnEnemy()
{
	int col = rand() % 5;

	this->enemy.setPosition(
		static_cast<float>(rand() % (static_cast<int>(this->window->getSize().x - this->enemy.getSize().x))),
		0.f
	);

	switch (col)
	{
	case 0:
		this->enemy.setScale(sf::Vector2f(0.2f, 0.2f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 1:
		this->enemy.setScale(sf::Vector2f(0.4f, 0.4f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 2:
		this->enemy.setScale(sf::Vector2f(0.6f, 0.6f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setScale(sf::Vector2f(0.8f, 0.8f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 4:
		this->enemy.setScale(sf::Vector2f(1.f, 1.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		break;
	}
	
	this->enemies.push_back(this->enemy);

}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void Game::updateEnemy()
{

	// Enemy spawning
	if (this->enemies.size() < this->maxEnimies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	// Enemy moving
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 5.f);
		this->enemies[i].rotate(1);

		bool deleted = false;

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			deleted = true;
			this->health--;
		}

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHold == false)
		{
			this->mouseHold = true;
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->point += 20;
					else if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->point += 15;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->point += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->point += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->point += 5;
					this->enemies.erase(this->enemies.begin() + i);
					deleted = true;
				}
			}
		}
	}
	else
	{
		this->mouseHold = false;
	}
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->point << std::endl
		<< "Health: " << this->health << std::endl;

	this->uiText.setString(ss.str());
}





void Game::update()
{

	this->pollEvents();

	if (this->gameOver == false)
	{
		this->updateMousePosition();

		this->updateText();

		this->updateEnemy();
	}

	if (this->health == 0)
	{
		this->gameOver = true;

	}

}

void Game::renderEnemy(sf::RenderTarget& target)
{
	for (auto& e : enemies)
	{
		target.draw(e);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	this->window->clear();

	// Draw game
	this->renderEnemy(*this->window);

	this->renderText(*this->window);


	// Display
	this->window->display();
}
