#include "Engine.h"

void Engine::draw()
{
	//cleats the window
	window.clear();
	//sets the view
	window.setView(mainView);
	//draws sprites
	window.draw(backgroundSprite);
	window.draw(floorSprite);
	//if obstacles or pickups are spawned draw them
	if (bObstacle.isSpawned())
	{
		window.draw(bObstacle.getSprite());
	}

	if (hPickup.isSpawned())
	{
		window.draw(hPickup.getSprite());
	}

	//draw bullet if active
	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isBulletActive())
		{
			window.draw(bullets[i].getShape());
		}
	}
	//draws player
	if (inPlane != true) {
		window.draw(user.getSprite());
		window.draw(user.getArmSprite());
	}
	else {
		window.draw(user.getSprite());
	}
	//draws active enemys
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
	//draws HUD if playing
	if (state != State::PLAYING)
	{
		window.draw(m_Hud.getMessage());
		window.draw(menuSprite);
		window.draw(menuText);
		window.setMouseCursorVisible(true);
	}
	//if game is not playing draw menu
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
	//draw pause text if paused
	if (state == State::PAUSED)
	{
		window.draw(pauseText);
	}



	//displays the window
	window.display();
}