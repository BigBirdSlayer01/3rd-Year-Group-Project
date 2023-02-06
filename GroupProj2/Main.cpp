// Include important C++ libraries here
#include "Engine.h"

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
	//plays the music
	sf::Music music;
	if (!music.openFromFile("sound/Music.ogg"))
		return -1; // error
	music.play();

	//engine constructor called
	Engine engine;

	//calls the run method
	engine.run();
}