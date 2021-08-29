#include "Ship.h"
#define _USE_MATH_DEFINES
#include <math.h>

Ship::Ship()
	:SpaceObj()
{
	nSize = 50;

	arms[0].x = 0; arms[0].y = -50;
	arms[1].x = -30; arms[1].y = 30;
	arms[2].x = 30; arms[2].y = 30;

	pos = sf::Vector2f(512,364);

	triangle = sf::VertexArray(sf::Triangles, 3);

	triangle[0].position = sf::Vector2f(512.f, 314.f);//czubek
	triangle[1].position = sf::Vector2f(484.f, 394.f);//lewy
	triangle[2].position = sf::Vector2f(544.f, 394.f);//prawy

	velocity = sf::Vector2f(0,0);

	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;

}

void Ship::draw(sf::RenderWindow& window)
{
	window.draw(triangle);
}

void Ship::rotate(bool left)
{
	//float theta = 5 * M_PI / 180;

	/*bool left = false;
	bool right = false;*/

	float angle = 4;


	if (left)
	{
		transform(arms[0], -angle);
		triangle[0].position = pos + arms[0];

		transform(arms[1], -angle);
		triangle[1].position = pos + arms[1];

		transform(arms[2], -angle);
		triangle[2].position = pos + arms[2];
	}
	else
	{

		transform(arms[0], angle);
		triangle[0].position = pos + arms[0];

		transform(arms[1], angle);
		triangle[1].position = pos + arms[1];

		transform(arms[2], angle);
		triangle[2].position = pos + arms[2];

	}
}

void Ship::transform(sf::Vector2f& vector, float angle)
{
	float theta = angle * M_PI / 180;
	float rot_mat[2][2];



	rot_mat[0][0] = cos(theta); rot_mat[0][1] = -sin(theta);
	rot_mat[1][0] = sin(theta); rot_mat[1][1] = cos(theta);



	float vec_x=vector.x;
	float vec_y=vector.y;

	vector.x = vec_x * rot_mat[0][0] + vec_y * rot_mat[0][1];
	vector.y = vec_x * rot_mat[1][0] + vec_y * rot_mat[1][1];
}

void Ship::move()
{
		if (velocity.x!=0 || velocity.y!=0)
		{
			pos += velocity;

			triangle[0].position = pos + arms[0];
			triangle[1].position = pos + arms[1];
			triangle[2].position = pos + arms[2];
		}

		if(accel>0)
		accel-=0.1f;
}

void Ship::thrust()
{
	if(accel<3)
		accel+=0.05f;

	velocity += sf::Vector2f(arms[0].x / 10 * accel, arms[0].y / 10* accel);
}

std::vector<sf::Vector2f> Ship::getVertPosVec()
{
	std::vector<sf::Vector2f> temp;

	for (int i = 0; i < 3; i++)
	{
			temp.push_back(triangle[i].position);
	}
	return temp;
}
