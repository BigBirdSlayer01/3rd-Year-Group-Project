#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	//This is the font that will be used in this programme
	Font mT_Font;
	//this is the text for the start
	Text mT_Start;

	//this is the text for the timer
	Text mT_Time;
	//this is the text for the score
	Text mT_Score;
	//this is the text for the players health
	Text mT_Health;

	//this is the text for the players current clip size
	Text m_clipSize;

public:

	Hud();
	//this function will return a message, mostly used in this programme for debugging
	Text getMessage();

	//this will return the players score
	Text getScore();
	//this function will get the time
	Text getTime();
	//this function will get the players health
	Text getHealth();
	//this function will get 
	Text getBullet();

	//this function sets the score on screen to the text passed into it
	void setScore(String text);

	//this function sets the timer on the screen to the text passed into it
	void setTime(String text);

	//this function sets the players health on the screen to the text passed into it
	void setHealth(String text);

	//this function sets the current clip size and bullets in the clip on the screen to the text passed into it
	void setBullet(String text);

	//this function is called in engine to set the location for the text on screen
	void setSpotonView();
};