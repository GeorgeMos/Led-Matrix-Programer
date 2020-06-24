#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<string>
#include<cmath>
#include "Matrix.h"
#include "Button.h"

//Global variables
const int winx = 1900;
const int winy = 1000;

//window init
sf::RenderWindow window(sf::VideoMode(winx, winy), "Window");

Matrix ledMatrix = Matrix(winx - 1000, 10, 980, 980, 10, 10);


void clearBtnFunc() {
	ledMatrix.clear();
}

void newFrameBtnFunc() {
	ledMatrix.newFrame();
}

void nextFrameBtnFunc() {
	ledMatrix.nextFrame();
}

void prevFrameBtnFunc() {
	ledMatrix.prevFrame();
}

void saveFrameBtnFunc() {
	ledMatrix.saveFrame();
}

void saveToFileBtnFunc() {
	ledMatrix.saveToFile();
}

Button clearBtn = Button(10, 10, 50, 50, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Red, "Clear", clearBtnFunc, &window);
Button saveFrameBtn = Button(10, 70, 50, 50, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Red, "Save\nFrame", saveFrameBtnFunc, &window);
Button newFrameBtn = Button(10, 130, 50, 50, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Red, "New\nFrame", newFrameBtnFunc, &window);
Button nextFrameBtn = Button(10, 190, 50, 50, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Red, "Next\nFrame", nextFrameBtnFunc, &window);
Button prevFrameBtn = Button(10, 250, 50, 50, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Red, "Previous\nFrame", prevFrameBtnFunc, &window);
Button saveToFileBth = Button(10, 310, 50, 50, sf::Color::White, sf::Color::White, sf::Color::Blue, sf::Color::Red, "Save To\nFile", saveToFileBtnFunc, &window);

sf::Text currFrameLabel;
sf::Font labelFont;

int main() {
	labelFont.loadFromFile("Arial.ttf");
	currFrameLabel.setFont(labelFont);
	currFrameLabel.setString("Frame: " + std::to_string(ledMatrix.getCurrentFrame()));
	currFrameLabel.setCharacterSize(30);
	currFrameLabel.setPosition(sf::Vector2f(70, 130));
	sf::err().rdbuf(NULL);
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color(0, 0, 0));

		ledMatrix.draw(&window, sf::Color::Black, sf::Color::Red);
		clearBtn.drawButton();
		newFrameBtn.drawButton();
		nextFrameBtn.drawButton();
		prevFrameBtn.drawButton();
		saveFrameBtn.drawButton();
		saveToFileBth.drawButton();

		currFrameLabel.setString("Frame: " + std::to_string(ledMatrix.getCurrentFrame()));
		window.draw(currFrameLabel);

		window.display();
	}
	return 0;
}