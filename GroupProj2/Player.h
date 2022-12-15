#ifndef	PLAYER_H
#define PLAYER_H
//#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "PlayerArms.h"


using namespace sf;

class Player //: public GameObject
{
public:

	//gets the center position of the player
	Vector2f getCenter();
	//gets the overall position of the player
	FloatRect getPosition();

	//spawns player
	void Spawn(Vector2f position, float gravity, Vector2f resolution);
	//for user input
	bool input();

	//get diff part of sprite
	FloatRect getTop();
	FloatRect getBottom();
	FloatRect getLeft();
	FloatRect getRight();

	//rectsource for sprite animation
	IntRect rectSpriteSource;
	//animation timer
	float animationTimer;

	//for use in main
	Sprite getSprite();
	Sprite getArmSprite();

	//will stop player from falling
	void stopFall(float position);

	//stop jump
	void stopJump();

	void update(float elapsedTime, Vector2f targetCoords);//update player

	int getX();
	int getY();

	int getHealth();
	void setHealth(int newHealth);

	int getScore();
	void setScore(int scoreUp);

	void setY(int y);
	void setX(int x);

	float getSpeed();
	bool detectCollisions(FloatRect enemyBlock);

	// background speed
	float m_Speed = 0.2f;

protected:
	PlayerArms* arms = new PlayerArms();
	//starting Y position of player
	float m_startY;
	//checks if space is pressed for jump
	bool m_spacePressed;
	//for sprite
	Sprite m_Sprite;
	//texture
	Texture m_texture;
	//health
	int m_health;
	//max health will use this for powerups
	int max_health;
	// How long does a jump last
	float m_JumpDuration = 0.35;
	// is the player going up or down
	bool m_IsJumping;
	bool m_IsFalling;
	//length of time jump has lasted
	float m_JumpTime;
	//so player cant double jump
	bool m_JustJumped = false;
	//has player been hit
	bool isHit = false;
	//flashing count - used to check if flash sprite should be used
	int flashCount = 0;
	bool isFlashing = false; //is the user currently flashing
	//resolution size saved for PlayerArms
	Vector2f m_resolution;
	//screenHeight variable
	float screenHeight;
	//playerSizeRatio - stores ratio of player to screen res
	float playerSizeRatio;

	//possible private will leave as protected for now can chaange later
	// Gravity will effect jump
	float m_Gravity;

	//Score variable
	int m_Score;
	//player position
	Vector2f m_Position;
	//Used for collision detection
	FloatRect m_Bottom;
	FloatRect m_Top;
	FloatRect m_Right;
	FloatRect m_Left;
	void hit();


};
#endif