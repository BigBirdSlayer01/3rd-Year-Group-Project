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

	//controller support
	if (state == State::PLAYING)
	{
		spriteCrosshair.setPosition(50, 50);

		//checks if joystick is connected
		if (sf::Joystick::isConnected(0))
		{
			unsigned int buttonCount = sf::Joystick::getButtonCount(0);
		}

		//fires the gun
		if (sf::Joystick::getAxisPosition(0, Joystick::Z) < -99.f)
		{
			if (totalGameTime.asMilliseconds() - lastFired.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
			{
				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				bullets[currentBullet].shootBullet(user.getCenter().x, user.getCenter().y, spriteCrosshair.getPosition().x, spriteCrosshair.getPosition().y);

				currentBullet++;

				if (currentBullet > 99)
				{
					currentBullet = 0;
				}
				lastFired = totalGameTime;
				bulletsInClip--;
			}
		}
		//reloads
		if ((sf::Joystick::isButtonPressed(0, 1)))
		{
			bulletsInClip = clipsize;
		}
		//move mouse with controller
		if (sf::Joystick::isConnected(0))
		{
			//used to move the target
			//float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			//float y = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

			/*

			float mx = Mouse::getPosition().x;
			float my = Mouse::getPosition().y;

			float newX = mx + x;
			float newY = my + y;

			Vector2i position(newX, newY);

			Mouse::setPosition(position, window);*/

			float x = 0;
			float y = 0;

			
			if (sf::Joystick::getAxisPosition(0, Joystick::Y) < 0.5f)
			{
				x == 20;
			}
			else if (sf::Joystick::getAxisPosition(0, Joystick::Y) > -0.5f)
			{
				x = 20;
			}
			else if (sf::Joystick::getAxisPosition(0, Joystick::X) < 0.5f)
			{
				x = 20;
			}
			else if (sf::Joystick::getAxisPosition(0, Joystick::X) > -0.5f)
			{
				x = 20;
			}


			Vector2f pos(x, y);



			spriteCrosshair.setPosition(pos);

		}
		else
		{
			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);
		}
	}

	//shooting with mouse
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
				bullets[currentBullet].shootBullet(user.getCenter().x, user.getCenter().y, spriteCrosshair.getPosition().x, spriteCrosshair.getPosition().y);

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

