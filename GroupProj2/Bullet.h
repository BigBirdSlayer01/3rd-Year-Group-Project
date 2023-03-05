#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
public:

	//constructor
	Bullet();

	//stop the bullet
	void stopBullet();

	//method to check if bullet is active
	bool isBulletActive();

	//shoots bullet
	void shootBullet(float startX, float startY, float xTarget, float yTarget);

	//finds where bullet is
	FloatRect getBulletPosition();

	//update bullet every frame
	void updateBullet(float elapsedTime);


	//seen in example dont know if needed
	//returns shape of bullet
	RectangleShape getShape();


	//protected methods some may be switched to private later
protected:

	/*for sprite
	Sprite m_Sprite;
	//texture
	Texture m_texture;*/

	//position of bullet
	Vector2f m_BulletPosition;

	//is bullet active
	bool m_BulletActive = false;

	//bullet speed
	float m_BulletSpeed = 700.0f;

	//X and Y for BulletPosition
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Where is this bullet headed to?
	float m_XTarget;
	float m_YTarget;

	//min and max values
	//used so bullet doesnt keep going off screen taking up memory
	float m_BulletMaxX;
	float m_BulletMinX;
	float m_BulletMaxY;
	float m_BulletMinY;

	RectangleShape m_BulletShape;





};