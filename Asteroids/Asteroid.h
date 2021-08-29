#pragma once
#include "SpaceObj.h"
class Asteroid :
    public SpaceObj
{
    sf::VertexArray boundaries;
    sf::Vector2f arms[10];

    float rSpeed;

public:

    Asteroid();
    Asteroid(float posx, float posy, sf::Vector2f velocity, int size);


    void transform(sf::Vector2f& vector, float angle);

    void draw(sf::RenderWindow& window) override;
    void rotate(bool left) override;
    void move() override;
    void thrust() override;

};

