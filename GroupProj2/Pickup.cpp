#include "Pickup.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


Pickup::Pickup()
{
	srand(time(0));
	m_SecondsToLive = 200;
	m_SecondsToWait = 10;
}

void Pickup::spawn(int xRes)
{
	srand(time(0));
	//m_Type = (rand() % 4);
	m_Type = 3;

	// Associate the texture with the sprite
	if (m_Type == 1)
	{
		m_Texture.loadFromFile("graphics/Bullets.png");
		rectSpriteSource = IntRect(0, 0, 63, 48);

	}
	else if (m_Type == 2)
	{
		m_Texture.loadFromFile("graphics/HealthPickup.png");
		rectSpriteSource = IntRect(0, 0, 108, 48);
	}

	else if (m_Type == 3)
	{
		m_Texture.loadFromFile("graphics/crop_duster.png");
		rectSpriteSource = IntRect(0, 0, 128, 128);

	}
	m_Sprite = Sprite(m_Texture, rectSpriteSource);
	m_Sprite.setPosition(m_Position);
	m_Sprite.setOrigin(
		rectSpriteSource.left + rectSpriteSource.width / 2,
		rectSpriteSource.top + rectSpriteSource.height / 2);
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

FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
	return m_Sprite;
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

void Pickup::update(float elapsedTime, int xRes)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}


	// Do we need to hide a Pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Revove the Pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a Pickup
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the Pickup and reset the timer

		spawn(xRes);
	}
}

//If the player hits the box, remove it
void Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}

int Pickup::getType()
{
	return m_Type;
}
