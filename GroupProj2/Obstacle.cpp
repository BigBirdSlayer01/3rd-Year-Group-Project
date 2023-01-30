#include "Obstacle.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


Obstacle::Obstacle()
{

	m_Type = 1;

	// Associate the texture with the sprite
	if (m_Type == 1)
	{
		m_Texture.loadFromFile("graphics/HayBale.png");
		rectSpriteSource = IntRect(0, 0, 76, 60);

	}
	else if (m_Type == 2)
	{
		m_Texture.loadFromFile("graphics/Fence.png");
		rectSpriteSource = IntRect(0, 0, 76, 60);
	}
	m_Sprite = Sprite(m_Texture, rectSpriteSource);
	m_Sprite.setPosition(m_Position);
	m_Sprite.setOrigin(
		rectSpriteSource.left + rectSpriteSource.width / 2,
		rectSpriteSource.top + rectSpriteSource.height / 2);

	m_SecondsToLive = 200;
	m_SecondsToWait = 5;
}

void Obstacle::spawn(int xRes)
{
	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	//set enemy's position
	m_Position.x = xRes;
	m_Position.x += 40;
	m_Position.y = 730;

	m_Sprite.setPosition(m_Position);
}

FloatRect Obstacle::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Obstacle::getSprite()
{
	return m_Sprite;
}

bool Obstacle::isSpawned()
{
	return m_Spawned;
}

void Obstacle::update(float elapsedTime, int xRes)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}


	// Do we need to hide a Obstacle?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Revove the Obstacle and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a Obstacle
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the Obstacle and reset the timer

		spawn(xRes);
	}
}

//If the player hits the box, remove it
void Obstacle::hit()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}
