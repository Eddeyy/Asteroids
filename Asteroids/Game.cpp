#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"

Game* Game::instance;

std::vector<SpaceObj*> Game::spaceObjects;
std::vector<Bullet*> Game::bullets;

std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> Game::rnd;

Game::Game()
{
	addShip();
	addAsteroid(sf::Vector2f(2, 0.5), 5);
}

Game* Game::createInstance()
{
	if (instance == nullptr)
	{
		instance = new Game;
		return instance;
	}
	else
		return nullptr;

}

void Game::addShip()
{
	spaceObjects.push_back(new Ship);
}

void Game::addAsteroid(sf::Vector2f velocity, unsigned int size)
{
	spaceObjects.push_back(new Asteroid(156, 512, velocity, 12));

	spaceObjects.push_back(new Asteroid(800, 103, sf::Vector2f(-0.7, 1.23), 7));
}

void Game::drawGame(sf::RenderWindow& window)
{
	for (auto b : bullets)
		b->draw(window);

	for (auto o : spaceObjects)
		o->draw(window);
}
void Game::addBullets(sf::Vector2f origin, sf::Vector2f velocity)
{
	bullets.push_back(new Bullet(origin, velocity));
}

void Game::shoot(sf::Event event)
{
		if (!shootCooldown)
		{
			addBullets(spaceObjects[0]->getPos(), spaceObjects[0]->getVec());
			shootCooldown = true;
		}
}

void Game::clearBullets()
{
	auto it = bullets.begin();

	if (bullets.size())
	{
		for (auto b : bullets)
		{
 			if (b->getPos().x < 0 || b->getPos().y < 0 || b->getPos().x > width || b->getPos().y > height)
			{
				delete b;
				bullets.erase(it);
				return;
			}
			if(it!=bullets.end())
				it++;
		}
	}
}

void Game::wrapCoords()
{
	for (auto s : spaceObjects)
	{
		if (s->getPos().x < -100)					// when flying off to the LEFT
			s->setPos(1024, s->getPos().y);

		if (s->getPos().y < -100)					// when flying off to the TOP
			s->setPos(s->getPos().x, 768);

		if (s->getPos().x > 1104)						// when flying off to the RIGHT
			s->setPos(0, s->getPos().y);

		if (s->getPos().y > 868)							// when flying off to the BOTTOM
			s->setPos(s->getPos().x, 0);
	}

}

bool Game::isShipCollided()
{
	// Very basic collision system.
	// Game simply checks if the distance of the ship's vertices to the asteroids centre
	// is smaller than the radius of said asteroid.

	std::vector<sf::Vector2f> sVertices = spaceObjects[0]->getVertPosVec();

	for (int i = 1; i < spaceObjects.size(); i++)
	{

		for (auto v : sVertices)
		{
			sf::Vector2f dVec = v - spaceObjects[i]->getPos();;

			if (sqrt(dVec.x * dVec.x + dVec.y * dVec.y) < spaceObjects[i]->getSize() * 12.45 - 30)
				return true;
		}
	}

	return false;
}

void Game::restartGame()
{
	spaceObjects.clear();
	addShip();
	addAsteroid(sf::Vector2f(2, 0.5), 5);
}

void Game::bulletCol()
{
	bool deleted = false;
	
	do 
	{
		auto it = bullets.begin();

		for (int i = 1; i < spaceObjects.size(); i++)
		{
			for (auto b : bullets)
			{
				sf::Vector2f dVec = b->getPos() - spaceObjects[i]->getPos();

				if (sqrt(dVec.x * dVec.x + dVec.y * dVec.y) < spaceObjects[i]->getSize() * 12.45 - 30)
				{
					destAst(i);
					delete b;
					bullets.erase(it);
					deleted = true;
					break;
				}
				if (it != bullets.end())
					it++;
			}
			if (deleted)
				break;
		}
	} while (deleted);
}

void Game::destAst(int it)
{
	auto iterator = spaceObjects.begin();

	while (it)
	{
		iterator++;
		it--;
	}

	delete spaceObjects[it];
	spaceObjects.erase(iterator);
}