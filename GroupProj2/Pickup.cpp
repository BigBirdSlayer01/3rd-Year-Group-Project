#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup(int type)
{
	// Store the type of this Pickup
	m_Type = type;

	// Associate the texture with the sprite
	if (m_Type == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_Pickup.png"));
	}
	else if (m_Type == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/ammo_Pickup.png"));
	}
	//Change these also when a sprite exists for these
	m_Sprite.setOrigin(25, 25);
}

void Pickup::setArena(IntRect arena)
{
	// Copy the details of the arena to the Pickup's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Pickup::spawn()
{
	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	m_Sprite.setPosition(500, 1000);
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

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::update(float elapsedTime)
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
		spawn();
	}

}

void Pickup::upgrade()
{
	if (m_Type == 1)
	{
		m_Value += (HEALTH_START_VALUE * .5);
	}
	else if (m_Type == 2)
	{
		m_Value += (AMMO_START_VALUE * .5);
	}

	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (START_WAIT_TIME / 10);
}