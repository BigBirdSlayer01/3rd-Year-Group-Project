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

public:
	Hud();
	Text getMessage();
	Text getScore();
	Text getTime();

	void setScore(String text);
	void setTime(String text);
};