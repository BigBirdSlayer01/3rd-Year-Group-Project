// Include important C++ libraries here
#include "Engine.h"

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
	sf::Music music;
	if (!music.openFromFile("sound/Music.ogg"))
		return -1; // error
	music.play();

	//engine
	Engine engine;

	engine.run();
}