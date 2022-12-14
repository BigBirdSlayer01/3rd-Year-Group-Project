#include "Engine.h"

void Engine::draw()
{
	window.clear();
	window.setView(mainView);
	window.draw(backgroundSprite);
	window.draw(user.getSprite());
	window.draw(enemy.getSprite());
	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isBulletActive())
		{
			window.draw(bullets[i].getShape());

		}
	}
	// Draw the HUD
// Switch to m_HudView
	window.setView(m_HudView);
	window.draw(m_Hud.getScore());
	window.draw(m_Hud.getTime());
	if (state != State::PLAYING)
	{
		window.draw(m_Hud.getMessage());
	}
	window.draw(spriteCrosshair);
	window.display();
}