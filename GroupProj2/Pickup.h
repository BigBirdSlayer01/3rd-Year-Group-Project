#pragma once
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	//Start value for health Pickups
	const int HEALTH_START_VALUE = 3;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	// The sprite that represents this Pickup
	Sprite m_Sprite;

	// The arena it exists in
	IntRect m_Arena;

	// How much is this Pickup worth?
	int m_Value;

	// What type of Pickup is this? 
	// 1 = health, 2 = ammo, 3 = bale, 4 = plane
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	Pickup(int type);

	// Prepare a new Pickup
	void setArena(IntRect arena);

	void spawn();

	// Check the position of a Pickup
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the Pickup update itself each frame
	void update(float elapsedTime);

	// Is this Pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the Pickup
	int gotIt();

	// Upgrade the value of each Pickup
	void upgrade();

};
