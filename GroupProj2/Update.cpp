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

		// Set the crosshair to the mouse world location
		spriteCrosshair.setPosition(mouseWorldPosition);

		// Set the crosshair to the mouse world location
		spriteCrosshair.setPosition(mouseWorldPosition);

		//update bullets
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isBulletActive())
			{
				bullets[i].updateBullet(dtAsSeconds);
			}
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

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssScore << "Score:"; //Add a score function when the game is done
		m_Hud.setScore(ssScore.str());

		m_FramesSinceLastHUDUpdate = 0;
	}
}