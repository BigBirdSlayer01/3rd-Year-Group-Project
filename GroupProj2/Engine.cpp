#include "Engine.h"


Engine::Engine()
{
	//enum for the games state
	state = State::GAME_OVER;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Chicken Hunt (Working Title)", Style::Fullscreen);
	window.setFramerateLimit(500);

	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	//creates a view
	//View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	mainView = View(window.getDefaultView());


	backgroundTexture.loadFromFile("graphics/back.png");

	backgroundTexture.setRepeated(true);

	//sf::Sprite backgroundSprite(backgroundTexture, iBounds);
	backgroundSprite.setTexture(backgroundTexture);
	//scaling background to screen
	float screenBackgroundYRatio = resolution.y / 677;
	backgroundSprite.setScale(1.0f,screenBackgroundYRatio);
	//floorY value - this variable will hold Y value of the ground level
	float floorY = resolution.y * 0.7; // 0.7 of screen size
	//declares start position
	Vector2f startPos(150, floorY);

	//spawns player
	user.Spawn(startPos, Gravity, resolution);
	enemy.spawn(resolution.x, resolution.y / 2);

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(false);

	textureCrosshair.loadFromFile("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	
	//for bullets
	
	currentBullet = 0;
	clipsize = 6;
	bulletsInClip = 6;
	fireRate = 1;
	
	
}// End Engine constructor

void Engine::run()
{
	//values used to scroll background
	FloatRect fBounds(0.f, 0.f, (resolution.x * 2.8), (resolution.y));

	IntRect iBounds(fBounds);

	backgroundSprite.setTextureRect(iBounds);

	const sf::Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const sf::Vector2f spriteStart(fBounds.left, fBounds.top);

	while (window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		totalGameTime += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		if (state == State::PLAYING)
		{
			//all used for scrolling background
			//moves the x value of the view by 0.2f (value may be changed to suit the game)
			mainView.move(user.getSpeed(), 0.0f);
			//sets the offset of the view
			const sf::Vector2f viewOffset(viewStart - mainView.getCenter());
			//creates the sprite offset
			sf::Vector2f spriteOffset;
			//sets the x and y offsets so both can be moved
			spriteOffset.x = floor(viewOffset.x / backgroundTexture.getSize().x) * backgroundTexture.getSize().x;
			spriteOffset.y = floor(viewOffset.y / backgroundTexture.getSize().y) * backgroundTexture.getSize().y;
			//sets the background position
			backgroundSprite.setPosition(spriteStart - spriteOffset);
		}	

		input();
	
		if (state == State::PLAYING)
		{
			//update player
			user.input();
			user.update(dt.asSeconds(), mouseWorldPosition);
			//updates enemy
			for (auto it = begin(enemyVector); it != end(enemyVector); ++it)
			{
				if ((*it)->isAlive())
				{
					(*it)->update(dt.asSeconds(), user.getCenter());
					if (user.detectCollisions((*it)->getPosition()))//check for collision between player and enemy)
					{
						(*it)->hit();
						user.setHealth(user.getHealth() - 1);
					} 
				}
				if ((*it)->getPosition().left > 0)
				{
					(*it)->isAlive() == false;
				}
			}		
			
			//updates scene
			update(dtAsSeconds);
			draw();
		}
	}
}