#include "Button.h"

Button::Button(float x, float y, float width, float height,
    sf::Font* font, std::string text,
    sf::Color idleColour, sf::Color hoverColour, sf::Color activeColour)


{
    //sets the button to idle state
    this->buttonState = BTN_IDLE;

    //sets the position and size
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    //sets the font
    this->font = font;
    this->text.setFont(*this->font);
    //sets the text
    this->text.setString(text);
    //sets the colour
    this->text.setFillColor(sf::Color::Black);
    //sets character size
    this->text.setCharacterSize(46);
    //sets the position
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    //sets the colours
    this->idleColour = idleColour;
    this->hoverColor = hoverColour;
    this->activeColor = activeColour;

}

Button::~Button()
{

}
//renders the button
void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}
//gets the button state
short Button::getButtonState()
{
    return buttonState;
}
//gets the button shape
sf::RectangleShape Button::getShape()
{
    return this->shape;
}
//gets the text
sf::Text Button::getText()
{
    return text;
}

//Accessors
const bool Button::isPressed() const
{
    if (this->buttonState == BTN_PRESSED)
    {
        return true;
    }

}

//functions
void Button::update(const sf::Vector2f mousePos)
{
    //Update the booleans for hover and pressed
    this->buttonState = BTN_IDLE;

    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_PRESSED;
        }
    }

    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColour);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_PRESSED:
        this->shape.setFillColor(this->activeColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}