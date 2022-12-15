#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{
private:
	// The sprite that represents this Obstacle
	Sprite m_Sprite;

	// The arena it exists in
	IntRect m_Arena;

	// What type of Obstacle is this? 
	// 1 = bale, 2 = trough
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	Obstacle();

	// Prepare a new Obstacle
	void setArena(IntRect arena);

	//Spawn an Obstacle
	void spawn();

	void setType();

	// Check the position of a Obstacle, used for checking collisions
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the Obstacle update itself each frame
	void update(float elapsedTime);

	// Is this Obstacle currently spawned?
	bool isSpawned();
};
