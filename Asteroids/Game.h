#pragma once
#include <vector>
#include "SpaceObj.h"
#include "Bullet.h"
#include <iostream>
#include <random>
class Game final
{
	static Game* instance;

	void clearBullets();
	void addShip();
	void addAsteroid(sf::Vector2f velocity, unsigned int size, float x =0, float y=0);
	void spawnNewAst();
	void nextRound();
	bool isShipCollided();
	void bulletCol();
	void restartGame();
	void destAst(int it);


	void wrapCoords();

	void transform(sf::Vector2f& vector, float angle);

	Game();
public:
										//game data
	static const int width = 1024;
	static const int height = 768;
	static std::vector<SpaceObj*> spaceObjects;
	static std::vector<Bullet*> bullets;

	
	static std::linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647> rnd; //static random engine

	bool shootCooldown = false;

										//method for creating singleton
	static Game* createInstance();

										//deleted copying constructor, and operator=()
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

										//usable methods
	void drawGame(sf::RenderWindow& window);

	void rotateShip(bool left) { spaceObjects[0]->rotate(left); };

	void moveShip() { spaceObjects[0]->thrust(); };


	void updateObj() 
	
	{ 
		wrapCoords();

		for(auto s : spaceObjects)
			s->move();
	
		for (auto b : bullets)
			b->move();

		if (isShipCollided())
			restartGame();

		bulletCol();

		clearBullets(); 
		nextRound();
	};
	void shotReset() { shootCooldown = false; };






	void addBullets(sf::Vector2f origin, sf::Vector2f velocity);
	void shoot(sf::Event event);

};

