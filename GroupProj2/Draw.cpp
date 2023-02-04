#include "Engine.h"

void Engine::draw()
{
	window.clear();
	window.setView(mainView);
	window.draw(backgroundSprite);
	window.draw(floorSprite);
	if (bObstacle.isSpawned())
	{
		window.draw(bObstacle.getSprite());
	}

	if (hPickup.isSpawned())
	{
		window.draw(hPickup.getSprite());
	}

	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isBulletActive())
		{
			window.draw(bullets[i].getShape());
		}
	}
	if (inPlane != true) {
		window.draw(user.getSprite());
		window.draw(user.getArmSprite());
	}
	else {
		window.draw(user.getSprite());
	}
	
	for (auto it = begin(enemyVector); it != end(enemyVector); ++it)
	{
		if ((*it)->isAlive())
		{
			window.draw((*it)->getSprite());
		}
	}
	// Draw the HUD
	// Switch to m_HudView
	window.draw(spriteCrosshair);
	window.setView(m_HudView);
	window.draw(m_Hud.getScore());
	window.draw(m_Hud.getTime());
	window.draw(m_Hud.getHealth());
	window.draw(m_Hud.getBullet());
	if (state != State::PLAYING)
	{
		window.draw(m_Hud.getMessage());
		window.draw(menuSprite);
		window.draw(menuText);
		window.setMouseCursorVisible(true);
	}
	if (state == State::GAME_OVER)
	{
		window.draw(menuText);
		window.draw(gamestate_btn->getShape());
		window.draw(gamestate_btn->getText());
		window.draw(highButton->getShape());
		window.draw(highButton->getText());
		window.draw(quitButton->getShape());
		window.draw(quitButton->getText());
	}
	if (state == State::PAUSED)
	{
		window.draw(pauseText);
	}



	//displays the window
	window.display();
}