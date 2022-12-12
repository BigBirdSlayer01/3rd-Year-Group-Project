#include "Engine.h"

void Engine::input()
{
	Event event;
	while (window.pollEvent(event))
	{

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Return && state == State::PLAYING)
			{
				state = State::PAUSED;
				//music.pause();
			}
			else if (event.key.code == Keyboard::Return && state == State::PAUSED)
			{
				state = State::PLAYING;
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
			// Start a new game while in GAME_OVER state
			else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
			{
				state = State::PLAYING;
				currentBullet = 0;
				clipsize = 6;
				bulletsInClip = 6;
				fireRate = 1.5;
			}
			if (state == State::PLAYING)
			{
				if (event.key.code == Keyboard::R)
				{
					bulletsInClip = clipsize;
					//insert sound for reload here
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	//controls

	if (state == State::PLAYING)
	{

		//shoots bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			if (totalGameTime.asMilliseconds()
				- lastFired.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
			{
				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				bullets[currentBullet].shootBullet(user.getCenter().x, user.getCenter().y, mouseWorldPosition.x, mouseWorldPosition.y);

				currentBullet++;

				if (currentBullet > 99)
				{
					currentBullet = 0;
				}
				lastFired = totalGameTime;
				bulletsInClip--;
			}
		}
	}

}