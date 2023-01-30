#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;

void Engine::writeScore(int newScore)
{
	std::string filePath = "score/highScore.txt";
	//read in score from file
	std::ifstream readFile;
	readFile.open(filePath); //open file for reading
	std::string scoreString; //string - contains file data
	readFile >> scoreString; //place data into string
	int oldScore = stoi(scoreString); //convert string to int for score
	readFile.close();

	std::ofstream writeFile;
	writeFile.open(filePath);
	//check if old score if smaller than new score
	if (newScore > oldScore)
	{
		writeFile << newScore;//overwrite score in file if greater than previous high score
	}
	writeFile.close();
}