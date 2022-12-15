#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font mT_Font;
	Text mT_Start;
	Text mT_Time;
	Text mT_Score;
	Text mT_Health;
	Text m_clipSize;

public:
	Hud();
	Text getMessage();
	Text getScore();
	Text getTime();
	Text getHealth();
	Text getBullet();

	void setScore(String text);
	void setTime(String text);
	void setHealth(String text);
	void setBullet(String text);
};