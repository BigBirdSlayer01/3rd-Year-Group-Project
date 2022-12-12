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
	}
}