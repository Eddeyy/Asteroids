#pragma once
#include "SpaceObj.h"
class Bullet :
    public SpaceObj
{
    sf::Sprite sprite;

    
public:

    Bullet(sf::Vector2f origin, sf::Vector2f velocity);
    ~Bullet();

    sf::Vector2f getPos() {return pos;};

    void draw(sf::RenderWindow& window) override;
    void rotate(bool left) override;
    void move() override;
    void thrust() override;
};

