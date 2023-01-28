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

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button
{
private:
    short unsigned buttonState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColour;
    sf::Color hoverColor;
    sf::Color activeColor;




public:
    Button(float x, float y, float width, float height,
        sf::Font* font, std::string text,
        sf::Color idleColour, sf::Color hoverColour, sf::Color activeColour);
    ~Button();

    //functions
    void render(sf::RenderTarget* target);

    void update(const sf::Vector2f mousePos);

    sf::RectangleShape getShape();
    sf::Text getText();

    short getButtonState();

    //accessors
    const bool isPressed() const;


};
#endif // BUTTON_HPP