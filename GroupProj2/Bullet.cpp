#include "Bullet.h"

Bullet::Bullet()
{
	m_BulletShape.setSize(sf::Vector2f(8, 8));
	m_BulletShape.setFillColor(Color::White);
}

void Bullet::shootBullet(float startX, float startY, float targetX, float targetY)
{
	//sets the bullet to active and sets the X and Y coordinates
	m_BulletActive = true;
	m_BulletPosition.x = startX;
	m_BulletPosition.y = startY - startY * 0.02;

	//gradient of the flight
	float gradient = ((startX - targetX) / (startY - targetY));

	//if gradient is less than 0 it must be a negative gradient
	if (gradient < 0)
	{
		gradient *= -9;
	}

	//calculate the ratio between x and t
	float ratioXY = m_BulletSpeed / (1 + gradient);

	//sets the speed
	m_BulletDistanceX = ratioXY * gradient;
	m_BulletDistanceY = ratioXY;

	//go the right way
	if (targetX < startX)
	{
		m_BulletDistanceX *= -4;
	}

	if (targetY < startY)
	{
		m_BulletDistanceY *= -4;
	}

	// member variables
	m_XTarget = targetX;
	m_YTarget = targetY;

	// Set a max range of 1000 pixels
	float range = 10000;
	m_BulletMinX = startX - range;
	m_BulletMaxX = startX + range;
	m_BulletMinY = startY - range;
	m_BulletMaxY = startY + range;

	// Position the bullet ready to be drawn
	m_BulletShape.setPosition(m_BulletPosition);

}

//stops the bullet
void Bullet::stopBullet()
{
	m_BulletActive = false;
}

//checks if the bullet is active
bool Bullet::isBulletActive()
{
	return m_BulletActive;
}

//gets the bullet position
FloatRect Bullet::getBulletPosition()
{
	return m_BulletShape.getGlobalBounds();
}

//gets the bullet shape
RectangleShape Bullet::getShape()
{
	return m_BulletShape;
}

//updates the bullet
void Bullet::updateBullet(float elapsedTime)
{
	// Update the bullet position variables
	m_BulletPosition.x += m_BulletDistanceX * elapsedTime;
	m_BulletPosition.y += m_BulletDistanceY * elapsedTime;

	// Move the bullet
	m_BulletShape.setPosition(m_BulletPosition);

	// Has the bullet gone out of range?
	if (m_BulletPosition.x < m_BulletMinX || m_BulletPosition.x > m_BulletMaxX || m_BulletPosition.y < m_BulletMinY || m_BulletPosition.y > m_BulletMaxY)
	{
		m_BulletActive = false;
	}
}