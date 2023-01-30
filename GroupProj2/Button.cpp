#include "Button.h"

Button::Button(float x, float y, float width, float height,
    sf::Font* font, std::string text,
    sf::Color idleColour, sf::Color hoverColour, sf::Color activeColour)


{
    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(46);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->idleColour = idleColour;
    this->hoverColor = hoverColour;
    this->activeColor = activeColour;

}

Button::~Button()
{

}

void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}

short Button::getButtonState()
{
    return buttonState;
}

sf::RectangleShape Button::getShape()
{
    return this->shape;
}
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