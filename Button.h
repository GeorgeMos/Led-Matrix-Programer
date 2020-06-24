#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Button
{
private:
	int posX;
	int posY;
	int width;
	int height;
	bool clicked = false;
	sf::Color textColor;
	sf::Color outlineColor;
	sf::Color backgroundColor;
	sf::Color clickColor;
	std::string text;
	void (*function)();
	sf::RenderWindow* window;
public:
	Button(int posX, int posY, int width, int height, sf::Color textColor, sf::Color outlineColor, sf::Color backgroundColor, sf::Color clickColor, std::string text, void (*function)(), sf::RenderWindow* window);
	void drawButton();
};

