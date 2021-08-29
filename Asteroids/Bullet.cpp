#include "Bullet.h"
#include <iostream>



Bullet::Bullet(sf::Vector2f origin, sf::Vector2f velocity)
{
	std::cout << "BULLET\n";
	texture.create(5, 5);
	sf::Uint8* pixels = new sf::Uint8[5 * 5 * 4];

	for (register int i = 0; i < 5 * 5 * 4; i += 4) {
		pixels[i] = 255; // obviously, assign the values you need here to form your color
		pixels[i + 1] = 255;
		pixels[i + 2] = 255;
		pixels[i + 3] = 255;
	}
	texture.update(pixels);
	sprite.setTexture(texture);
	sprite.setPosition(origin);
	this->velocity = velocity;
	accel = 3;
	pos = origin;
	delete[] pixels;
}

Bullet::~Bullet()
{

	std::cout << ">>BULLET ERASED\n";
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Bullet::rotate(bool left)
{
	sprite.rotate(10);
}

void Bullet::move()
{
	if (accel)
	{
		pos += sf::Vector2f(velocity.x/10 * accel, velocity.y/10*accel);
		sprite.move(sf::Vector2f(velocity.x / 10 * accel, velocity.y / 10 * accel));
	}
	sprite.rotate(1);
}

void Bullet::thrust()
{
}

