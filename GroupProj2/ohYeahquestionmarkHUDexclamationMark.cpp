#include "Hud.h"

//Default constructor for the HUD
Hud::Hud()
{
	//setting the variable for the resolution
	Vector2u resolution;
	//taking in the resolution so the HUD can be dynamic
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font from the files
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

	// Time, These are all the same. The Fontm character size, colour and position on screen are set 
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
	mT_Health.setPosition(25, resolution.y - 100);
	mT_Health.setString("1");

	// bullet
	m_clipSize.setFont(mT_Font);
	m_clipSize.setCharacterSize(75);
	m_clipSize.setFillColor(Color::Green);
	m_clipSize.setPosition(resolution.x - 100, resolution.y - 100);
	m_clipSize.setString("1");
}

//This will return the Start message created above
Text Hud::getMessage()
{
	return mT_Start;
}

//This returns the Score text
Text Hud::getScore()
{
	return mT_Score;
}

//this returns the Text for the timer
Text Hud::getTime()
{
	return mT_Time;
}

//This returns the score for health
Text Hud::getHealth()
{
	return mT_Health;
}

//This returns the text for the clip size and current bullets in clip
Text Hud::getBullet()
{
	return m_clipSize;
}

//this sets the hud element to the string passed into it
void Hud::setScore(String text)
{
	mT_Score.setString(text);
}

//this sets the time hud element to the string passed into it
void Hud::setTime(String text)
{
	mT_Time.setString(text);
}

//this sets the hud text element to the string passed into it
void Hud::setHealth(String text)
{
	mT_Health.setString(text);
}

//this sets the bullet text to the string passed into it
void Hud::setBullet(String text)
{
	m_clipSize.setString(text);
}

//this sets the location for all text elements of the hud to a spot on the screen
void Hud::setSpotonView()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	mT_Time.setPosition(resolution.x - 150, 0);
	mT_Score.setPosition(25, 0);
	mT_Health.setPosition(25, resolution.y - 100);
	m_clipSize.setPosition(resolution.x - 150, resolution.y - 100);
}
