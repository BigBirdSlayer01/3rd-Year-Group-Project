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
			else if (event.key.code == Keyboard::Return && state == State::PAUSED || gamestate_btn->getButtonState() == BTN_PRESSED && state == State::PAUSED)
			{
				state = State::PLAYING;
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
			// Start a new game while in GAME_OVER state
			else if (event.key.code == Keyboard::Return && state == State::GAME_OVER || gamestate_btn->getButtonState() == BTN_PRESSED && state == State::GAME_OVER)
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
					//	for (int i = 0; i < 10000; i++) {
					//		if (i == 10000) {
					bulletsInClip = clipsize;
					reload.play();
					//	}
				//	}
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
				shoot.play();

				bullets[currentBullet].shootBullet(user.getCenter().x, user.getCenter().y, newX, newY);

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
			//for (int i = 0; i < 10000; i++) {
				//if (i == 10000) {
			bulletsInClip = clipsize;
			reload.play();
			//}
		//}
		}
		if ((sf::Joystick::isButtonPressed(0, 7)))
		{
			window.close();
		}
		//move mouse with controller

		if (sf::Joystick::isConnected(0))
		{
			//used to move the target
			float x = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
			float y = sf::Joystick::getAxisPosition(0, sf::Joystick::V);

			newX = newX + user.getSpeed();


			if ((sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -20))
			{
				newX--;
			}
			if ((sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 20))
			{
				newX++;
			}
			if ((sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -20))
			{
				newY--;
			}
			if ((sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 20))
			{
				newY++;
			}
			spriteCrosshair.setPosition(newX, newY);

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
				shoot.play();
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