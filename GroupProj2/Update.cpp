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
			m_Hud.setSpotonView();

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

			ssBullets << bulletsInClip << "/" << clipsize;
			m_Hud.setBullet(ssBullets.str());

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
			for (auto it = begin(enemyVector); it != end(enemyVector); ++it)
			{
				if (bullets[i].isBulletActive() && (*it)->isAlive())
				{
					if (bullets[i].getBulletPosition().intersects((*it)->getPosition()))
					{
						bullets[i].stopBullet();

						(*it)->hit();
					}
				}
			}
		}

		int num1 = resolution.y / 2;
		int randNum = rand() % num1;

		if (totalGameTime.asMilliseconds() - EnemyLastSpawned.asMilliseconds() > 4000)
		{
			//for (auto it = begin(enemyVector); it != end(enemyVector); ++it)
			//{
			Enemy* enemy1 = new Enemy;
			(*enemy1).spawn(resolution.x, randNum, resolution.y / 2);
			enemyVector.push_back(enemy1);
			currentEnemy++;
			EnemyLastSpawned = totalGameTime;
			//}
		}

		auto itr = enemyVector.begin();
		while (itr != enemyVector.end())
		{
			bool isHere = (*itr)->isAlive();
			if (!isHere)
			{
				itr = enemyVector.erase(itr);
				if (itr != enemyVector.begin())
				{
					itr = std::prev(itr);
					continue;
				}
			}
			else
			{
				++itr;
			}
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