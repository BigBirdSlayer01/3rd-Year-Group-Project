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

	//set texture and sprite for menu
	float menuYRatio = resolution.y / 1011;
	float menuXRatio = resolution.x / 1798;
	menuTexture.loadFromFile("graphics/FarmYard.jpg");
	menuSprite.setTexture(menuTexture);
	menuSprite.setScale(menuXRatio, menuYRatio);
	menuSprite.setPosition(0, 0);

	backgroundTexture.loadFromFile("graphics/back.png");

	backgroundTexture.setRepeated(true);

	//sf::Sprite backgroundSprite(backgroundTexture, iBounds);
	backgroundSprite.setTexture(backgroundTexture);
	//scaling background to screen
	float screenBackgroundYRatio = resolution.y / 677;
	backgroundSprite.setScale(1.0f, screenBackgroundYRatio);
	//floorY value - this variable will hold Y value of the ground level
	float floorY = resolution.y * 0.65; // 0.7 of screen size
	//declares start position
	Vector2f startPos(150, floorY);

	//create floor sprite
	floorTexture.loadFromFile("graphics/Floor.png");
	floorTexture.setRepeated(true);
	floorSprite.setTexture(floorTexture);
	floorSprite.setScale(1.0f, screenBackgroundYRatio);
	//position floor
	floorSprite.setPosition(0.0, resolution.y * 0.7);//0.7 of resolution down on screen

	//spawns player
	user.Spawn(startPos, Gravity, resolution);
	//enemy.spawn(resolution.x, resolution.y / 2);

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

	//load font
	font.loadFromFile("fonts/Farm.ttf");

	//menu buttons
	gamestate_btn = new Button(
	resolution.x/2-150,resolution.y/2-200,300,80, &this->font, "Play",sf::Color(185,65,255), sf::Color(219,165,255), sf::Color(119,0,200));

	highButton = new Button(
		resolution.x / 2 - 150, resolution.y / 2 , 300, 80, &this->font, "Highscore", sf::Color(185, 65, 255), sf::Color(219, 165, 255), sf::Color(119, 0, 200));

	quitButton = new Button(
		resolution.x / 2 - 150, resolution.y / 2+200, 300, 80, &this->font, "Quit", sf::Color(185, 65, 255), sf::Color(219, 165, 255), sf::Color(119, 0, 200));

	//Menu Text
	menuText.setFont(font);
	menuText.setCharacterSize(150);
	menuText.setFillColor(Color::Black);
	menuText.setPosition(resolution.x / 2 - 750, 250);
	menuText.setString("Chicken Hunt (Working Title)");

	//paused text
	pauseText.setFont(font);
	pauseText.setCharacterSize(128);
	pauseText.setFillColor(Color::Black);
	pauseText.setPosition(resolution.x / 2 - 650, resolution.y / 2);
	pauseText.setString("PAUSED: Press Enter to Resume");

	//setting up sounds for the game
	shootBuffer.loadFromFile("sound/Shoot.ogg");
	shoot.setBuffer(shootBuffer);
	//reload
	reloadBuffer.loadFromFile("sound/reload.wav");
	reload.setBuffer(reloadBuffer);
	//chicken death noise
	chickenBuffer.loadFromFile("sound/ChickenDie.ogg");
	chicken.setBuffer(chickenBuffer);
	//player hit noise
	hitBuffer.loadFromFile("sound/hit.wav");
	hit.setBuffer(hitBuffer);


}// End Engine constructor

void Engine::run()
{
	mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

	//values used to scroll background
	FloatRect fBounds(0.f, 0.f, (resolution.x * 2.8), (resolution.y));

	IntRect iBounds(fBounds);

	backgroundSprite.setTextureRect(iBounds);

	const sf::Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const sf::Vector2f spriteStart(fBounds.left, fBounds.top);

	//values used to scroll floor
	FloatRect floorBounds(0.f, 0.f, (resolution.x * 2.8), resolution.y * 0.7);
	IntRect iFloorBounds(floorBounds);
	floorSprite.setTextureRect(iFloorBounds);

	const sf::Vector2f viewFloorStart(floorBounds.left + (floorBounds.width / 2), floorBounds.top + floorBounds.height);
	const sf::Vector2f spriteFloorStart(floorBounds.left, floorBounds.top + floorBounds.height);

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
			//m_HudView.move(user.getSpeed(), 0.0f);
			//sets the offset of the view
			sf::Vector2f viewOffset(viewStart - mainView.getCenter());
			//creates the sprite offset
			sf::Vector2f spriteOffset;
			//sets the x and y offsets so both can be moved
			spriteOffset.x = floor(viewOffset.x / backgroundTexture.getSize().x) * backgroundTexture.getSize().x;
			spriteOffset.y = floor(viewOffset.y / backgroundTexture.getSize().y) * backgroundTexture.getSize().y;
			//sets the background position
			backgroundSprite.setPosition(spriteStart - spriteOffset);

			/* FLOOR */
			viewOffset = viewFloorStart - mainView.getCenter(); //reset offset for floor
			//sets the x and y offsets so both can be moved
			spriteOffset.x = floor(viewOffset.x / floorTexture.getSize().x) * floorTexture.getSize().x;
			spriteOffset.y = floor(viewOffset.y / floorTexture.getSize().y) * floorTexture.getSize().y;
			//sets the floor position
			floorSprite.setPosition(spriteFloorStart - spriteOffset);
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
						hit.play();
					}
				}
				if ((*it)->getPosition().left > 0)
				{
					(*it)->isAlive() == false;
				}
			}
			//updates scene
			update(dtAsSeconds);
		}
		
		if (state == State::PAUSED || state == State::GAME_OVER)
		{
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			gamestate_btn->update(mouseWorldPosition);
			highButton->update(mouseWorldPosition);
			quitButton->update(mouseWorldPosition);

			if (gamestate_btn->getButtonState() == BTN_PRESSED)
			{
				state = State::PLAYING;
			}
			if (quitButton->getButtonState() == BTN_PRESSED)
			{
				window.close();
			}
		}
		draw();
	}
}