#include "Obstacle.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Engine.h"


//setting up the default contructor for the Obstacle
Obstacle::Obstacle()
{
	//seeding the rand function
	srand(time(0));
	//randomly generate a type for the obstacle
	m_Type = (rand() % 2 +1);

	//this line was used for debugging 
	//m_Type = 2;

	// Establish the type for the Obstacle and assign the correct sprite

	//if m_type is 1 then spawn a haybale
	if (m_Type == 1)
	{
		m_Texture.loadFromFile("graphics/HayBale.png");
		rectSpriteSource = IntRect(0, 0, 76, 60);

	}

	//if the m_type is 2 then spawn a fence
	else if (m_Type == 2)
	{
		m_Texture.loadFromFile("graphics/Fence.png");
		rectSpriteSource = IntRect(0, 0, 76, 60);
	}

	//assigning the position and Sprite and Origin for the obstacle
	m_Sprite = Sprite(m_Texture, rectSpriteSource);
	m_Sprite.setPosition(m_Position);
	m_Sprite.setOrigin(
		rectSpriteSource.left + rectSpriteSource.width / 2,
		rectSpriteSource.top + rectSpriteSource.height / 2);

	//instantiating the seconds to live and wait 
	m_SecondsToLive = 20;
	m_SecondsToWait = 7;
}

//this function spawns the Obstacle, the resolution is passed into it 
void Obstacle::spawn(Vector2f resolution)
{
	// Not currently spawned
	//m_Spawned = false;

	//if the obstacle is spawned then seconds since spawn is set to 0 and m_spawned is set to true
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	//set the position for the obstacl to spawn, it should be barely off the ground and also touching the ground
	m_Position.x = resolution.x;
	m_Position.x += 40;
	m_Position.y = resolution.y * 0.672;

	m_Sprite.setPosition(m_Position);
}

//this function will return the Obstacles position which allows us to check if the player has hit it
FloatRect Obstacle::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

//This returns the sprite of the obstacle, used in draw.cpp
Sprite Obstacle::getSprite()
{
	return m_Sprite;
}

//This function will return if the Obstacle is spawned 
bool Obstacle::isSpawned()
{
	return m_Spawned;
}

//this function will update the obstacle based on the time and current resolution, passed onto the spawn function
void Obstacle::update(float elapsedTime, Vector2f resolution)
{
	//if the obstacle is spawned then seconds since spawn will increase
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	//if the obstacle is not spawned then seconds since despawn should increase
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}


	// If the obstacle has been out for too long then it should be despawned by this function
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Set spawned to false and seconds since despawn to 0 till another obstacle is spawned
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// This checks if another obstacle should be spawned if it has been longer than the time to wait
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		//call the spawn function, pass in the resolution so the obstacle can spawn correctly

		spawn(resolution);
	}
}

//If the player hits the obstacle then it should be despawned
void Obstacle::hit()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}
