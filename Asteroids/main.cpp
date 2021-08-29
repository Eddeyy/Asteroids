#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(Game::width, Game::height), "Asteroids 2021 SFML");
		
	window.setFramerateLimit(60);

	sf::Event event;

	srand(time(NULL));

	Game* game = Game::createInstance();


	bool rotating_left = false;
	bool rotating_right = false;
	bool thrust = false;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}

			//     \/ \/ \/ THESE IF STATEMENTS SET UP THE FLAGS \/ \/ \/ 

			//schoot
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Spacebar\n";
					game->shoot(event);
				}
			//schoot cooldown
			if (event.type == sf::Event::KeyReleased)
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Spacebar released\n";
					game->shotReset();
				}

			//rotate left
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Left)
				{
					rotating_left = true;
				}

			//rotate right
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Right)
				{
					rotating_right = true;
				}

			//rotate left / right stop
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					rotating_left = false;
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					rotating_right = false;
				}
			}

			//thrust
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Up)
					thrust = true;

			//thrust stop
			if (event.type == sf::Event::KeyReleased)
				if (event.key.code == sf::Keyboard::Up)
					thrust = false;

		}

		// We chceck if the ship has collided with any of the asteroids
		// And if so, then restart the game


		// Here the flags are checked and the correct methods are called
		if(rotating_left)
			game->rotateShip(true);
		if (rotating_right)
			game->rotateShip(false);
		if(thrust)
			game->moveShip();


		game->updateObj();

		window.clear();
		game->drawGame(window);
		window.display();

	}

	return 0;
}