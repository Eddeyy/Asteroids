#pragma once
#include <SFML/Graphics.hpp>
class SpaceObj
{
protected:

	sf::Vector2f pos;
	float accel;
	sf::Vector2f velocity;
	int nSize;

	sf::Texture texture;

public:


	SpaceObj();

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void rotate(bool left) = 0;
	virtual void move() = 0;
	virtual void thrust() = 0;

	virtual sf::Vector2f getPos() { return pos; };
	virtual sf::Vector2f getVec() { return pos; };
	virtual int getSize() { return nSize; };


	// This virtual method is created strictyl for the purposes of collision detection.
	// It's supposed to gather all the vertices' positions and then return them as a std::vector of sf::vector2fs
	// (Basically an std::vector of pairs of floats)

	virtual std::vector<sf::Vector2f> getVertPosVec() { std::vector<sf::Vector2f> temp; return temp; };


	virtual void setPos(float x, float y) { pos.x = x; pos.y = y; };

};

