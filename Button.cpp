#include "Button.h"

Button::Button(int posX, int posY, int width, int height, sf::Color textColor, sf::Color outlineColor, sf::Color backgroundColor, sf::Color clickColor, std::string text, void (*function)(), sf::RenderWindow* window)
{
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	this->textColor = textColor;
	this->backgroundColor = backgroundColor;
	this->clickColor = clickColor;
	this->text = text;
	this->function = function;
	this->window = window;
}

void Button::drawButton()
{
	sf::RectangleShape button(sf::Vector2f(width, height));
	button.setPosition(posX, posY);
	if (!clicked && sf::Mouse::getPosition(*window).x >= posX && sf::Mouse::getPosition(*window).x <= posX + width && sf::Mouse::getPosition(*window).y >= posY && sf::Mouse::getPosition(*window).y <= posY + height && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		button.setFillColor(clickColor);
		function();
		clicked = true;
	}
	else {
		button.setFillColor(backgroundColor);
		clicked = false;
	}
	button.setOutlineColor(outlineColor);
	button.setOutlineThickness(1);

	sf::Text btntext;
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	btntext.setFont(font);
	btntext.setString(text);
	btntext.setCharacterSize(width / 4);
	btntext.setFillColor(textColor);
	btntext.setPosition(posX, posY);


	window->draw(button);
	window->draw(btntext);
}
