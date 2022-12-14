#ifndef	PLAYERARMS_H
#define PLAYERARMS_H
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayerArms
{
public:
	bool update(Vector2f newPosition, Vector2f newTargetCoords, Vector2f resolution);
	void spawn(Vector2f arm_Position);
	Sprite getArmSprite();
private:
	float m_startY;
	float screenHeight;
	float armSizeRatio;
	Vector2f arm_Position;
	Vector2f targetCoords;
	//for sprite
	Sprite m_Sprite;
	//texture
	Texture m_texture;
};

#endif