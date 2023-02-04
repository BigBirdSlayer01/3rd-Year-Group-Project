#include "Pickup.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


Pickup::Pickup()
{
	m_SecondsToLive = 20;
	m_SecondsToWait = 10;
}


//The spawn function for the Pickup
void Pickup::spawn(Vector2f resolution)
{
	//seeding the rand function so its not the same spawning every time
	srand(time(0));
	//The type is rand mod 3 + 1 to generate in the range of 1-3
	m_Type = (rand() % 3 + 1);
	//m_Type = 3;

	//if the M_Type is 1 then a bullet pickup will be spawned
	if (m_Type == 1)
	{
		m_Texture.loadFromFile("graphics/Bullets.png");
		rectSpriteSource = IntRect(0, 0, 63, 48);

	}
	//if the M-type is 2 then a health pickup will be spawned
	else if (m_Type == 2)
	{
		m_Texture.loadFromFile("graphics/HealthPickup.png");
		rectSpriteSource = IntRect(0, 0, 108, 48);
	}

	//if the m_type is 3 then a crop duster pickup will be spawned
	else if (m_Type == 3)
	{
		m_Texture.loadFromFile("graphics/crop_duster.png");
		rectSpriteSource = IntRect(0, 0, 128, 128);

	}
	//Setting the sprite and all respective things needed for it in the following code
	m_Sprite = Sprite(m_Texture, rectSpriteSource);
	m_Sprite.setPosition(m_Position);
	m_Sprite.setOrigin(
		rectSpriteSource.left + rectSpriteSource.width / 2,
		rectSpriteSource.top + rectSpriteSource.height / 2);
	// Not currently spawned
	//m_Spawned = false;

	//as the spawn function is called the second since spawn is set to 0 and M_spawned is set to true
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	//set pickup's position

	m_Position.x = resolution.x; //the pickup will be spawned slightly off the screen by getting the resolution and then adding 40 pixels to it
	m_Position.x += 40;
	m_Position.y = resolution.y*0.68; //0.6% down on screen - same as floor - Changed to .68, this spawns it barely off the floor

	m_Sprite.setPosition(m_Position);
}

//this function returns the pickups coordinates, used to see if the player has collided with it
FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

//this is used to return the sprite for the function in the draw.cpp file
Sprite Pickup::getSprite()
{
	return m_Sprite;
}

//this function returns if the obstacle is spawned or not
bool Pickup::isSpawned()
{
	return m_Spawned;
}

//this will update the pickup
void Pickup::update(float elapsedTime, Vector2f res)
{
	//if m_spawned is true then the seconds since spawn will be increased
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	//otherwise the seconds since despawn will be increased
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}


	// If the pickup has been spawned for longer than it should be then it is removed
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Delete the pickip
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// Check if the pickup should be spawned by the seconds since despawn
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// if this condition is met and a pickup should be spawned, then we call the spawn function and pass in the current resolution to spawn it correctly

		spawn(res);
	}
}

//If the player collides with the pickup then it should be removed and then seconds since despawn should be set to 0
void Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}

//this function returns the type of the pickup, this allows the engine to check what it should do when the player hits it
int Pickup::getType()
{
	return m_Type;
}
