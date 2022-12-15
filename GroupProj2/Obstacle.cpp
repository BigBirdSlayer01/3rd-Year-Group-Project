#include "Obstacle.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Obstacle::Obstacle()
{
	// Store the type of this Obstacle
	srand(time(0));
	m_Type = (rand() % 2);
	
	// Associate the texture with the sprite
	if (m_Type == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/obs_Bale.png"));

	}
	else if (m_Type == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/obs_Trough.png"));
	}
	//Change origin when a texture actually exists for these obstacles
	m_Sprite.setOrigin(25, 25);
}

void Obstacle::setArena(IntRect arena)
{
	// Copy the details of the arena to the Obstacle's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;
	spawn();
}

void Obstacle::spawn()
{
	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	m_Sprite.setPosition(500, 975);
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

void Obstacle::update(float elapsedTime)
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
		//setType();
		// spawn the Obstacle and reset the timer
		spawn();
	}

}

//This function generates a random number to change the type.
void Obstacle::setType() {
	
}