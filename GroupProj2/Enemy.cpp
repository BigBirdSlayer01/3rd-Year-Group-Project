#include "Enemy.h"
#include <cstdlib>
#include <ctime>

using namespace std;

//enemy has been hit with bullet
bool Enemy::hit()
{
	//reduce health - currently reduces to 0 - instant kill
	m_Health -= 5;

	if (m_Health < 0)
	{
		m_Alive = false; //its dead
		//m_Texture.loadFromFile("graphics/chicken_base.png");
		//m_Sprite.setTexture(m_Texture);

		return true;
	}

	return false; //else - its not dead
}

//is teh enemy still alive - true if yes
bool Enemy::isAlive()
{
	return m_Alive;
}

//spawn enemy using starter values
void Enemy::spawn(float startX, float startY, float scale)
{
	animationTimer = 0;
	//setting enemy's texture and sprite
	m_Texture.loadFromFile("graphics/chicken_anim.png");
	rectSpriteSource = IntRect(0, 0, 128, 128);
	m_Sprite = Sprite(m_Texture, rectSpriteSource);

	m_SecondsSinceSpawn = 0;

	//set enemy's size to be dynamic with the screen resolution
	//total height of screen = startY * 2
	const float screenHeight = scale * 2;
	//ratio for enemy sprite - sprite image height should be tenth of screen height
	const float enemySizeRatio = (screenHeight / 12) / 128;//image height - 128pixels
	//set scale using ratio above
	m_Sprite.setScale(enemySizeRatio, enemySizeRatio);

	m_Speed = ENEMY_SPEED + 0.2f; //set enemy speed to start speed
	m_Health = ENEMY_HEALTH; //set enemy health to start health

	//set enemy's position
	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setPosition(m_Position);
	m_Sprite.setOrigin(
		rectSpriteSource.left + rectSpriteSource.width / 2,
		rectSpriteSource.top + rectSpriteSource.height / 2
	);

}

//return enemy's sprite position
FloatRect Enemy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

//return sprite of enemy
Sprite Enemy::getSprite()
{
	return m_Sprite;
}

void Enemy::update(float elapsedTime, Vector2f playerLocation)
{
	/* ANIMATION */
	//update animation timer
	animationTimer += elapsedTime;
	double timePerFrame = 1.0 / 6.0;
	if (animationTimer > timePerFrame) //if max time to display frame has been exceeded
	{
		//update frame stored in rectSpriteSource
		if (rectSpriteSource.left == 128)
		{
			rectSpriteSource.left = 0;
		}
		else
		{
			rectSpriteSource.left = 128;
		}
		animationTimer = 0;
	}

	//update position
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (m_Alive)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}

	//if enemy is alive
	if (isAlive())
	{
		// Update the enemy position variables
		//move left
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
		//move up or down based on player location
		if (playerY > m_Position.y)//player above enemy
		{
			m_Position.y = m_Position.y + m_Speed * elapsedTime;
		}
		if (playerY < m_Position.y)//player below enemy
		{
			m_Position.y = m_Position.y - m_Speed * elapsedTime;
		}
	}
	else
	{
		if (m_Position.y >= -200) //if its still on-screen
		{
			//enemy is dead
			//reduce x
			m_Position.x = m_Position.x - 2 * elapsedTime;
			//reduce y
			m_Position.y = m_Position.y + 500 * elapsedTime;
		}
	}



	//officially move sprite
	m_Sprite.setPosition(m_Position);

	//set enemy texture
	m_Sprite.setTextureRect(rectSpriteSource);
}

float Enemy::getTimeSpawn()
{
	return m_SecondsSinceSpawn;
}

void Enemy::setPosition(int x, int y)
{
	m_Sprite.setPosition(x, y);
}

//gets center
Vector2f Enemy::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}
//sets enemy alive status
void Enemy::setAlive(bool new1)
{
	m_Alive = new1;
}
//sets enemy health
void Enemy::setHealth(float health)
{
	m_Health = health;
}