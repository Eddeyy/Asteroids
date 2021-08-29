#pragma once
#include "SpaceObj.h"
class Ship :
    public SpaceObj
{

    sf::VertexArray triangle;
    sf::Vector2<float> arms[3];


    void transform(sf::Vector2f& vector, float angle);


public:

    Ship();
    

    void draw(sf::RenderWindow& window) override;
    void rotate(bool left) override;
    void move() override;
    void thrust() override;

    sf::Vector2f getPos() { return triangle[0].position; };

    std::vector<sf::Vector2f> getVertPosVec() override;
   

    sf::Vector2f getVec() { return arms[0]; };

};

