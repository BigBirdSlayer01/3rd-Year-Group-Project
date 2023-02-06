#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <SFML/Graphics/Text.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED };

class Button
{
private:
    short unsigned buttonState;

    //variables for shape, font and text
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    //coolour variables
    sf::Color idleColour;
    sf::Color hoverColor;
    sf::Color activeColor;




public:
    //button constructor
    Button(float x, float y, float width, float height,
        sf::Font* font, std::string text,
        sf::Color idleColour, sf::Color hoverColour, sf::Color activeColour);
    ~Button();

    //functions
    void render(sf::RenderTarget* target);

    //updates the button based on the mouse position
    void update(const sf::Vector2f mousePos);

    //get methods for shape and text
    sf::RectangleShape getShape();
    sf::Text getText();

    //gets the buttons state
    short getButtonState();

    //accessors
    const bool isPressed() const;


};
#endif // BUTTON_HPP