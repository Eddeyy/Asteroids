#include "Asteroid.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "Game.h"

Asteroid::Asteroid()
	:SpaceObj()
{

}

Asteroid::Asteroid(float posx, float posy,sf::Vector2f velocity , int size)
	:SpaceObj()
{

	Asteroid::velocity = velocity;
	nSize = size;
	

	float radius = nSize * 12.45;

	pos.x = posx;
	pos.y = posy;

	boundaries = sf::VertexArray(sf::TriangleFan, 12); //Creating the boundaries 

	boundaries[0] = sf::Vector2f(pos.x, pos.y);

	rSpeed = 4/(rand() % 4 + 1);

	for (int i = 1; i < 11; i++) //Ploting the circle for the boundaries
	{ 
		boundaries[i] =  pos + sf::Vector2f((radius + (rand() % nSize*4)- nSize * 4) * sin(36.f * i * M_PI / 180), (radius + (rand() % nSize * 4)- nSize * 4) * cos(36.f * i * M_PI / 180));
		std::cout << radius * sin(36.f * i * M_PI / 180) << " -II- " << radius * cos(36.f * i * M_PI / 180) << std::endl;
	}

	for(int i = 0 ; i<12; i++)
		boundaries[i].color = sf::Color(160, 160, 160, 255);

	for (int i = 0; i < 10; i++)
	{
		arms[i] = boundaries[i + 1].position - pos;
	}

	boundaries[11] = boundaries[1];

	velocity = sf::Vector2f(2.5, -1);
}

void Asteroid::move()
{
	rotate(true);

	if (velocity.x != 0 || velocity.y != 0)
	{
		pos += velocity;
		boundaries[0].position = pos;

		for (int i = 1; i < 11 ; i++)
		{
			boundaries[i].position = pos + arms[i - 1];
		}
		boundaries[11] = boundaries[1];
	}
}


void Asteroid::rotate(bool left) 
{

	float angle = rSpeed;


	if (left)
	{

		for (auto& a : arms)
		{
			transform(a, -angle);
		}

		for (int i = 1; i < 11; i++)
		{
			boundaries[i].position = pos + arms[i - 1];
		}
		boundaries[11] = boundaries[1];
	}
	else
	{

		for (auto a : arms)
		{
			transform(a, angle);
		}

		for (int i = 1; i < 11; i++)
		{
			boundaries[i].position = pos + arms[i - 1];
		}
		boundaries[11] = boundaries[1];

	}
}

void Asteroid::transform(sf::Vector2f& vector, float angle)
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

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(boundaries);
}

void Asteroid::thrust(){}