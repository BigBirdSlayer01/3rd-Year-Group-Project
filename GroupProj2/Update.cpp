#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	// Where is the mouse pointer
	mouseScreenPosition = Mouse::getPosition();

	mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

	resolution.x = resolution.x + user.getSpeed();

	//updates the frame
	if (state == State::PLAYING)
	{
		// Time to update the HUD?
		// Increment the number of frames since the last HUD calculation
		
		m_FramesSinceLastHUDUpdate++;

		// Update the HUD every m_TargetFramesPerHUDUpdate frames
		if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
		{
			// Update game HUD text
			std::stringstream ssTime;
			std::stringstream ssScore;

			// Update the time text
			ssTime << (int)m_TimeRemaining;
			m_Hud.setTime(ssTime.str());

			// Update the level text
			ssScore << "Score:"; //Add a score function when the game is done
			m_Hud.setScore(ssScore.str());

			m_FramesSinceLastHUDUpdate = 0;
		}
		/*
		BaleObstacle(1).update(dtAsSeconds);
		FenceObstacle(2).update(dtAsSeconds);*/
		
		
		//update bullets
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isBulletActive())
			{
				bullets[i].updateBullet(dtAsSeconds);
			}
		}
		/*
		for (int i = 0; i < 19; i++)
		{
			if (obstacle[i].isSpawned())
			{
				obstacle[i].update(dtAsSeconds);
			}
		}*/

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

		int num1 = resolution.y / 2;
		int randNum = rand() % num1;

		if (enemy[currentEnemy].getTimeSpawn() > 4 || enemy[currentEnemy].isAlive() == false)
		{
			currentEnemy++;
			enemy[currentEnemy].spawn(resolution.x, randNum, resolution.y / 2);

		}
		if (currentEnemy >= 99)
		{
			currentEnemy = 0;
		}

		/*
		if (obstacle[currentObstacle].isSpawned() == false)
		{
			currentObstacle++;
			obstacle[currentObstacle].spawn();

		}
		if (currentObstacle > 19)
		{
			currentObstacle = 0;
		}*/
		m_TimeRemaining += dtAsSeconds;
	}	
}