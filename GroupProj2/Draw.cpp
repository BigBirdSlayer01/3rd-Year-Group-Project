#include "Engine.h"

void Engine::draw()
{
	window.clear();
	window.setView(mainView);
	window.draw(backgroundSprite);
	window.draw(user.getSprite());
	if (enemy.isAlive())
	{
		window.draw(enemy.getSprite());
	}
	
	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isBulletActive())
		{
			window.draw(bullets[i].getShape());

		}
	}
	window.draw(spriteCrosshair);
	window.display();
}