#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"

#define _USE_MATH_DEFINES
#include <math.h>

Game* Game::instance;

std::vector<SpaceObj*> Game::spaceObjects;
std::vector<Bullet*> Game::bullets;

std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> Game::rnd;

Game::Game()
{
	restartGame();
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

void Game::addAsteroid(sf::Vector2f velocity, unsigned int size, float x, float y)
{
	spaceObjects.push_back(new Asteroid(x, y, velocity, size));
}

void Game::spawnNewAst()
{
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

void Game::transform(sf::Vector2f& vector, float angle)
{
	float theta = angle * M_PI / 180;
	float rot_mat[2][2];



	rot_mat[0][0] = cos(theta); rot_mat[0][1] = -sin(theta);
	rot_mat[1][0] = sin(theta); rot_mat[1][1] = cos(theta);



	float vec_x = vector.x;
	float vec_y = vector.y;

	vector.x = vec_x * rot_mat[0][0] + vec_y * rot_mat[0][1];
	vector.y = vec_x * rot_mat[1][0] + vec_y * rot_mat[1][1];
}

void Game::restartGame()
{
	spaceObjects.clear();
	addShip();

	nextRound();
}

void Game::bulletCol()
{
	bool deleted = false;
	
	do 
	{
		deleted = false;
		for (int i = 1; i < spaceObjects.size(); i++)
		{
			auto it = bullets.begin();
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

	if (spaceObjects[it]->getSize() > 6)
	{
		SpaceObj* ast = spaceObjects[it];

		float astVelVal = sqrt(ast->getVec().x * ast->getVec().x + ast->getVec().y * ast->getVec().y);

		sf::Vector2f vel(astVelVal * (rand()% static_cast<int>(astVelVal)/2 + 1), 0);
		transform(vel, rand() % 361);
		addAsteroid(sf::Vector2f(vel.x, vel.y), ast->getSize() - 2, ast->getPos().x, ast->getPos().y);


		vel = sf::Vector2f(astVelVal * (rand() % static_cast<int>(astVelVal)/2 + 1), 0);
		transform(vel, rand() % 361);
		addAsteroid(sf::Vector2f(vel.x, vel.y), ast->getSize() - 2, ast->getPos().x, ast->getPos().y);
	}

	auto iterator = spaceObjects.begin();

	delete spaceObjects[it];
	while (it--)
	{
		iterator++;
	}

	spaceObjects.erase(iterator);
}

void Game::nextRound()
{
	if (spaceObjects.size() == 1)
	{
		float sPosx = spaceObjects[0]->getPos().x;
		float sPosy = spaceObjects[0]->getPos().y;

		const int d = 6;

		sf::Vector2f spVec = spaceObjects[0]->getVec();
		transform(spVec, 90);

		sf::Vector2f spVelVec = spaceObjects[0]->getVec();;
		transform(spVelVec, 25 + rand() % 130);
		
		addAsteroid(sf::Vector2f(spVelVec.x/(rand() % 20 + 20), spVelVec.y/ (rand() % 20 + 20)), 10, sPosx + spVec.x*d, sPosy + spVec.y*d);

		spVelVec = spaceObjects[0]->getVec();;
		transform(spVelVec, -25 - rand() % 130);

		addAsteroid(sf::Vector2f(spVelVec.x/ (rand() % 20 + 20), spVelVec.y/ (rand() % 20 + 20)), 10, sPosx - spVec.x*d, sPosy - spVec.y*d);
	}
}