#include "Engine.h"

void Engine::draw()
{
	window.clear();
	window.setView(mainView);
	window.draw(backgroundSprite);
	window.draw(floorSprite);
	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isBulletActive())
		{
			window.draw(bullets[i].getShape());

		}
	}
	window.draw(user.getSprite());
	window.draw(user.getArmSprite());
	window.draw(enemy.getSprite());
	window.draw(spriteCrosshair);

	window.display();
}