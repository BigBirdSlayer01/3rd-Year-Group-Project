#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	int tempScore = 0;
	
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
		
		

		int num1 = resolution.y / 2;
		int randNum = rand() % num1;

		if (enemy[currentEnemy].getTimeSpawn() > 4 || enemy[currentEnemy].isAlive() == false)
		{
			currentEnemy++;
			enemy[currentEnemy].spawn(resolution.x, randNum, resolution.y / 2);

		}
		if (currentEnemy > 19)
		{
			currentEnemy = 0;
		}

		m_TimeRemaining += dtAsSeconds;
	}

	
	// Time to update the HUD?
	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		std::stringstream ssTime;
		std::stringstream ssScore;
		std::stringstream ssHealth;
		std::stringstream ssBullets;
		

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text

		ssScore << "Score:" << user.getScore(); //Add a score function when the game is done
		m_Hud.setScore(ssScore.str());

		ssHealth << "Health:" << user.getHealth();
		m_Hud.setHealth(ssHealth.str());

		/*ssBullets << bulletsInClip << "/" << clipsize;
		m_Hud.setBullet(ssBullets.str());*/

		m_FramesSinceLastHUDUpdate = 0;
	}



	for (int i = 0; i < 100; i++)
	{
		
		for (int j = 0; j < currentEnemy + 1; j++)
		{
			if (bullets[i].isBulletActive() && enemy[j].isAlive())
			{
				if (bullets[i].getBulletPosition().intersects(enemy[j].getPosition()))
				{
					bullets[i].stopBullet();

					enemy[j].hit();
					user.setScore(5);
					
					

				}
			}
		}
	}
}