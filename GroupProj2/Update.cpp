#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	
	//updates the frame
	if (state == State::PLAYING)
	{
		resolution.x = resolution.x + user.getSpeed();

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
			for (int j = 0; j < currentEnemy+1; j++)
			{
				if (bullets[i].isBulletActive() && enemy[j].isAlive())
				{
					if (bullets[i].getBulletPosition().intersects(enemy[j].getPosition()))
					{
						bullets[i].stopBullet();

						enemy[j].hit();

					}
				}
			}
		}
		
		if (enemy[currentEnemy].isAlive() == false)
		{
			currentEnemy++;
			enemy[currentEnemy].spawn(resolution.x, resolution.y / 2);
		}
		if (currentEnemy > 19)
		{
			currentEnemy = 0;
		}

	}
}