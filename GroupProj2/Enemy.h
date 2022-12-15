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

	//current speed of enemy
	float m_Speed;
	//current health of enemy
	float m_Health;
	//is enemy alive? True if yes
	bool m_Alive;

	//time since the enemy was spawned
	float m_SecondsSinceSpawn;

public:
	//called when bullet hits enemy
	bool hit();//will return true when enemy is dead
	//return value of m_Alive (is the enemy alive)
	bool isAlive();

	float getTimeSpawn();

	void setPosition(int x, int y);

	void setAlive(bool new1);

	void setHealth(float health);

	//gets Centre
	Vector2f getCenter();

	//spawn enemy
	void spawn(float startX, float startY, float scale);
	//rectangular position of enemy in the world
	FloatRect getPosition();
	//get the sprite of the enemy - return a copy of the sprite
	Sprite getSprite();
	//update the enemy for the current frame
	void update(float elapsedTime, Vector2f playerLocation);
};