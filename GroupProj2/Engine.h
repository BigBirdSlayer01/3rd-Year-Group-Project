#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Obstacle.h"

using namespace sf;

class Engine
{
private:
	enum class State { PAUSED, GAME_OVER, PLAYING };

	State state;

	//gets resolution
	Vector2f resolution;

	RenderWindow window;

	View mainView;

	//clock for timing things
	Clock clock;

	//total game time - could be used for high score
	Time totalGameTime;

	//both mouse position vectors required
	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	//background texture
	Texture backgroundTexture;

	Sprite backgroundSprite;

	//decalres gravity
	const int Gravity = 600;

	int startx = 150;
	int starty = 1000;

	Player user;
	Enemy enemy[20];

	Sprite spriteCrosshair;
	Texture textureCrosshair;

	float newX = 0.f;
	float newY = 0.f;

	Bullet bullets[100];

	Time lastFired;

	//std::vector<Enemy*> EnemyVector;

	int currentBullet;
	int clipsize;
	int bulletsInClip;
	float fireRate;

	void draw();
	void update(float dtAsSeconds);
	void input();



public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};
