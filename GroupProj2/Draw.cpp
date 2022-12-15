#include "Engine.h"

void Engine::draw()
{
	window.clear();
	window.setView(mainView);
	window.draw(backgroundSprite);
	window.draw(user.getSprite());
	
	for (auto it = begin(enemyVector); it != end(enemyVector); ++it)
	{
		if ((*it)->isAlive())
		{
			window.draw((*it)->getSprite());
		}
	}
	/*
	for (int i = 0; i < 19; i++)
	{
		if (obstacle[i].isSpawned())
		{
			window.draw(obstacle[i].getSprite());
		}
	}*/
	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isBulletActive())
		{
			window.draw(bullets[i].getShape());
		}
	}

	// Draw the HUD
	// Switch to m_HudView
	
	if (state != State::PLAYING)
	{
		window.draw(m_Hud.getMessage());
	}

	window.draw(spriteCrosshair);
	window.setView(m_HudView);
	window.draw(m_Hud.getScore());
	window.draw(m_Hud.getTime());
	// Draw the particle system
	
	window.display();
}