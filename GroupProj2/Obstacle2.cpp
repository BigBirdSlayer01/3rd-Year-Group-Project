#include "Obstacle2.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Obstacle2::Obstacle2()
{
	// Store the type of this Obstacle
	m_Type = (rand() % 1) + 1;

	// Associate the texture with the sprite
	if (m_Type == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/HayBale.png"));

	}
	else if (m_Type == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/Fence.png"));
	}
	//Change origin when a texture actually exists for these obstacles
	m_Sprite.setOrigin(25, 25);
}

void Obstacle2::spawn()
{
	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	m_Sprite.setPosition(500, 975);
}

FloatRect Obstacle2::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Obstacle2::getSprite()
{
	return m_Sprite;
}

bool Obstacle2::isSpawned()
{
	return m_Spawned;
}

void Obstacle2::update(float elapsedTime)
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
		//Randomly change the type to spice up the game
		setType();
		// spawn the Obstacle and reset the timer
		spawn();
	}

}

//This function generates a random number to change the type.
void Obstacle2::setType() {
	srand(time(0));
	m_Type = (rand() % 2);
}