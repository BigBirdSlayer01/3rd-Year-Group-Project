#ifndef	PLAYERARMS_H
#define PLAYERARMS_H
#include <SFML/Graphics.hpp>

using namespace sf;
//The PlayerArms class is composed within the Player class, as part of the object
class PlayerArms
{
public:
	//update arms of player
	bool update(Vector2f newPosition, Vector2f newTargetCoords, Vector2f resolution);
	//spawn player's arms (when player spawns)
	void spawn(Vector2f arm_Position);
	Sprite getArmSprite(); //return teh sprite of teh arms
private:
	float m_startY; //arms staring Y position
	float screenHeight;//height of desktop screen
	float armSizeRatio;//size of arms relative to teh screen heigh
	Vector2f arm_Position;//current position of arms
	Vector2f targetCoords;//coordinates of the target/crosshair
	//for sprite
	Sprite m_Sprite;
	//texture
	Texture m_texture;
};

#endif