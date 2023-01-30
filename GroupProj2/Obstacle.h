#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{

private:


	// Public prototypes go here
public:

	Obstacle();
	// The sprite that represents this Obstacle
	Sprite m_Sprite;

	//texture for obstacle
	Texture m_Texture;

	//rectsource for sprite animation
	IntRect rectSpriteSource;
	// The arena it exists in
	IntRect m_Arena;

	//Making a vector for position
	Vector2f m_Position;

	// What type of Obstacle is this? 
	// 1 = bale, 2 = trough
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	//Spawn an Obstacle
	void spawn(int xRes);

	// Check the position of a Obstacle, used for checking collisions
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the Obstacle update itself each frame
	void update(float elapsedTime, int xRes);

	// Is this Obstacle currently spawned?
	bool isSpawned();

	//The player hits the Obstacle
	void hit();
};
