#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	//updates the frame
	if (state == State::PLAYING)
	{
		// Where is the mouse pointer
		mouseScreenPosition = Mouse::getPosition();

		mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);



		//update bullets
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isBulletActive())
			{
				bullets[i].updateBullet(dtAsSeconds);
			}
		}

		//checks for enemy/bullet collision
		
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isBulletActive() && enemy[1].isAlive())
			{
				if (bullets[i].getBulletPosition().intersects(enemy[1].getPosition()))
				{
					bullets[i].stopBullet();

					enemy[1].hit();

				}
			}
		}
	}
}