#include "Hud.h"

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	mT_Font.loadFromFile("fonts/Roboto-Light.ttf");

	// Paused
	mT_Start.setFont(mT_Font);
	mT_Start.setCharacterSize(100);
	mT_Start.setFillColor(Color::Black);
	mT_Start.setString("Press Enter when ready!");

	// Position the text
	FloatRect textRect = mT_Start.getLocalBounds();

	mT_Start.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	mT_Start.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	// Time
	mT_Time.setFont(mT_Font);
	mT_Time.setCharacterSize(75);
	mT_Time.setFillColor(Color::Green);
	mT_Time.setPosition(resolution.x - 150, 0);
	mT_Time.setString("------");

	// Score
	mT_Score.setFont(mT_Font);
	mT_Score.setCharacterSize(75);
	mT_Score.setFillColor(Color::Green);
	mT_Score.setPosition(25, 0);
	mT_Score.setString("1");

	// Health
	mT_Health.setFont(mT_Font);
	mT_Health.setCharacterSize(75);
	mT_Health.setFillColor(Color::Green);
	mT_Health.setPosition(25, resolution.y-100);
	mT_Health.setString("1");

	// bullet
	m_clipSize.setFont(mT_Font);
	m_clipSize.setCharacterSize(75);
	m_clipSize.setFillColor(Color::Green);
	m_clipSize.setPosition(resolution.x-100, resolution.y - 100);
	m_clipSize.setString("1");
}

Text Hud::getMessage()
{
	return mT_Start;
}

Text Hud::getScore()
{
	return mT_Score;
}

Text Hud::getTime()
{
	return mT_Time;
}

Text Hud::getHealth()
{
	return mT_Health;
}

Text Hud::getBullet()
{
	return m_clipSize;
}


void Hud::setScore(String text)
{
	mT_Score.setString(text);
}

void Hud::setTime(String text)
{
	mT_Time.setString(text);
}

void Hud::setHealth(String text)
{
	mT_Health.setString(text);
}

void Hud::setBullet(String text)
{
	m_clipSize.setString(text);
}