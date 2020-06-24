#pragma once
#include "Led.h"
#include <iostream>
#include<vector>
#include<fstream>
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Matrix
{
private:
	int matrixPosX;
	int matrixPosY;
	int ledsX;
	int ledsY;
	int width;
	int height;
	std::vector<std::vector<Led>> ledMatrix;
	std::vector<std::vector<std::vector<int>>> frames;
	int currentFrame;
	void applyData();

public:
	Matrix(int matrixPosX, int matrixPosY, int width, int height, int ledsX, int ledsY);
	void draw(sf::RenderWindow* window, sf::Color offColor, sf::Color onColor);
	void clear();
	//saves the frames vector to file
	void saveAll();
	//saves current frame to the vector and creates a new one
	void newFrame();
	//view next frame
	void nextFrame();
	//view previus frame
	void prevFrame();
	//Saves the current frame to frames vector
	void saveFrame();
	int getCurrentFrame();
	//Creates a file with the matrix info compatible with the arduino code
	void saveToFile();
};

