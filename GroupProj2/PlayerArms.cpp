#include "PlayerArms.h"

void PlayerArms::spawn(Vector2f arm_Position)
{
	this->arm_Position = arm_Position;

	//setting start y position
	m_startY = arm_Position.y;
	//total height of screen = (startY / 7) * 10
	screenHeight = (m_startY / 7) * 10;
	//float - ratio for arms sprite - sprite image height should be relative to screen height
	armSizeRatio = (screenHeight / 5) / 128;//image height - 128pixels

	// Move the sprite in to position
	m_Sprite.setOrigin(64, 64);//set origin to centre
	m_Sprite.setPosition(arm_Position);
	m_Sprite.setScale(armSizeRatio, armSizeRatio);
	m_texture.loadFromFile("graphics/player_arms.png"); //set texture for sprite
	m_Sprite.setTexture(m_texture); //apply texture

}

bool PlayerArms::update(Vector2f new_Position, Vector2f newTargetCoords, Vector2f resolution)
{
	//update position values of playerArms
	arm_Position = new_Position;
	arm_Position.y -= arm_Position.y * 0.01;//move up slightly for correct placement
	targetCoords = newTargetCoords;

	m_Sprite.setPosition(arm_Position);

	float angle = (atan2(targetCoords.y - arm_Position.y,
		targetCoords.x - arm_Position.x)
		* 180) / 3.141;
	m_Sprite.setRotation(angle);
	if ((angle > 90) || (angle<-90))
	{
		m_Sprite.setScale(armSizeRatio, -armSizeRatio);
		return false;
	}
	else
	{
		m_Sprite.setScale(armSizeRatio, armSizeRatio);
		return true;
	}
}

Sprite PlayerArms::getArmSprite()
{
	return m_Sprite;
}