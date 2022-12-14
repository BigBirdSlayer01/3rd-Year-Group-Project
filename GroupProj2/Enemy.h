#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	//start speed of enemy
	const float ENEMY_SPEED = 50;
	//start enemy health
	const float ENEMY_HEALTH = 5;

	//position of enemy
	Vector2f m_Position;
	//sprite for enemy
	Sprite m_Sprite;
	//texture for enemy
	Texture m_Texture;
	//rectsource for sprite animation
	IntRect rectSpriteSource;
	//animation timer
	float animationTimer;

	//current speed of enemy
	float m_Speed;
	//current health of enemy
	float m_Health;
	//is enemy alive? True if yes
	bool m_Alive;

public:
	//called when bullet hits enemy
	bool hit();//will return true when enemy is dead
	//return value of m_Alive (is the enemy alive)
	bool isAlive();
	//spawn enemy
	void spawn(float startX, float startY);
	//rectangular position of enemy in the world
	FloatRect getPosition();
	//get the sprite of the enemy - return a copy of the sprite
	Sprite getSprite();
	//update the enemy for the current frame
	void update(float elapsedTime, Vector2f playerLocation);
};