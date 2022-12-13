#include "Player.h"
//#include <SFML/Sprite.hpp>

void Player::Spawn(Vector2f startPosition, float gravity)
{
	//setting start y position
	m_startY = startPosition.y;
	//total height of screen = (startY / 6) * 10
	const float screenHeight = (m_startY / 6) * 10;
	//float - ratio for player sprite - sprite image height should be half of screen height
	const float playerSizeRatio = (screenHeight / 5) / 128;//image height - 128pixels

	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

	m_Sprite.setScale(playerSizeRatio, playerSizeRatio);

	m_texture.loadFromFile("graphics/Farmer.png");

	m_Sprite.setTexture(m_texture);

	m_JumpDuration = .67;

	m_Speed = 0.2f;
}

void Player::update(float elapsedTime)
{
	m_Position.x += m_Speed;

	//for jump will have to change to suit game speed
	if (m_IsJumping)
	{
		m_JumpTime += elapsedTime;

		if (m_JumpTime < m_JumpDuration)
		{
			m_Position.y -= 250 * 2 * elapsedTime;
		}
		else if(m_JumpTime > m_JumpDuration)
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}

	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	if (m_Position.y > m_startY)
	{
		m_Position.y = m_startY;
		m_IsFalling = false;
	}

	// Update the rect for all body parts
	FloatRect pos = getPosition();

	//not final used values from thomas was late temporarily
	//bottom of player
	m_Bottom.left = pos.left + 51;
	m_Bottom.top = pos.top + pos.height - 33; //bottom of player - 32 (bottom of feet) - 1
	m_Bottom.width = 24; //24 pixels
	m_Bottom.height = 1;

	//Top of player
	m_Top.left = pos.left + 51;
	m_Top.top = pos.top + 32;
	m_Top.width = 24; //24 pixels wide
	m_Top.height = 1;

	//Right of player
	m_Right.left = pos.left + pos.width - 53; //right of player sprite - 52 (player right position) - 1
	m_Right.top = pos.top + 32;
	m_Right.width = 1;
	m_Right.height = pos.height - 64 - 2; //roughly half the size of image - 2

	//Left of player
	m_Left.left = pos.left + 50;
	m_Left.top = pos.top + 33; //32 (top of player) + 1 (buffer)
	m_Left.width = 1;
	m_Left.height = pos.height - 64 - 2; //roughly half the size of image - 2


	// Move the sprite into position
	m_Sprite.setPosition(m_Position);

	if (isHit == true)//if player has been hit - call hit function
	{
		hit();
	}
}

//handles player input
bool Player::input()
{
	//sets jumped to false
	m_JustJumped = false;
	if (sf::Joystick::isConnected(0))
	{
		unsigned int buttonCount = sf::Joystick::getButtonCount(0);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		//makes sure player is not falling for the jump
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_JumpTime = 0;
			m_JustJumped = true;
			m_spacePressed = true;
		}
	}
	
	if (sf::Joystick::isButtonPressed(0, 0))
	{
		//makes sure player is not falling for the jump
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_JumpTime = 0;
			m_JustJumped = true;
			m_spacePressed = true;
		}
		
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}
	

	return m_JustJumped;
}


//various get methods required
FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return Vector2f
	(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

FloatRect Player::getBottom()
{
	return m_Bottom;
}

FloatRect Player::getTop()
{
	return m_Top;
}

FloatRect Player::getLeft()
{
	return m_Left;
}

FloatRect Player::getRight()
{
	return m_Right;
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

//will stop player fall
void Player::stopFall(float position)
{
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

// Stop a jump early in case of collision
void Player::stopJump()
{
	m_IsJumping = false;
	m_IsFalling = true;
}

//will hopefully be used to set player position and stop from falling off map
int Player::getX()
{
	int x = m_Position.x;

	return x;
}
int Player::getY()
{
	int y = m_Position.y;

	return y;
}

void Player::setX(int x)
{
	m_Position.x = x;
}
void Player::setY(int y)
{
	m_Position.y = y;
}

float Player::getSpeed()
{
	return m_Speed;
}

//detect collisions - used to check if player collides with 'enemyBlock' rect
bool Player::detectCollisions(FloatRect enemyBlock)
{
	if (
		m_Right.intersects(enemyBlock) ||
		m_Top.intersects(enemyBlock) ||
		m_Bottom.intersects(enemyBlock) ||
		m_Left.intersects(enemyBlock)
		)
	{
		isHit = true;
		return true;
	}
	return false;
}

void Player::hit()
{
	if (flashCount % 4 == 0) //every 4 frames - change sprite image
	{
		if (isFlashing)
		{
			m_texture.loadFromFile("graphics/Farmer_flash.png");
			isFlashing = false;
		}
		else
		{
			m_texture.loadFromFile("graphics/Farmer.png");
			isFlashing = true;
		}
		//after 10 flashes, reset sprite image to default and boolean values to false
		if (flashCount % 40 == 0)
		{
			isHit = false;
			isFlashing = false;
			m_texture.loadFromFile("graphics/Farmer.png");
		}
		m_Sprite.setTexture(m_texture);
	}
	flashCount++;
}