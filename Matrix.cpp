#include "Matrix.h"

Matrix::Matrix(int matrixPosX, int matrixPosY, int width, int height, int ledsX, int ledsY)
{
	this->matrixPosX = matrixPosX;
	this->matrixPosY = matrixPosY;
	this->width = width;
	this->height = height;
	this->ledsX = ledsX;
	this->ledsY = ledsY;
	currentFrame = 0;
	std::vector<std::vector<int>> frameTemp;
	//Matrix creartion and first frame creation
	for (int x = 0; x < this->ledsX; x++) {
		std::vector<Led> temp;
		std::vector<int> xyTemp;
		for (int y = 0; y < this->ledsY; y++) {
			temp.push_back(Led());
			xyTemp.push_back(0);
		}
		ledMatrix.push_back(temp);
		frameTemp.push_back(xyTemp);
	}
	frames.push_back(frameTemp);
	for (int x = 0; x < this->ledsX; x++) {
		for (int y = 0; y < this->ledsY; y++) {
			ledMatrix.at(x).at(y).chPos(this->matrixPosX + x * this->width / this->ledsX, this->matrixPosY + y * this->height / this->ledsY);
			ledMatrix.at(x).at(y).setWidth(this->width / this->ledsX);
			ledMatrix.at(x).at(y).setHeight(this->height / this->ledsY);
		}
	}

}

void Matrix::draw(sf::RenderWindow* window, sf::Color offColor, sf::Color onColor)
{
	for (int x = 0; x < ledsX; x++) {
		for (int y = 0; y < ledsY; y++) {
			sf::RectangleShape led(sf::Vector2f(ledMatrix.at(x).at(y).getWidth(), ledMatrix.at(x).at(y).getHeight()));
			led.setPosition(sf::Vector2f(ledMatrix.at(x).at(y).getPosX(), ledMatrix.at(x).at(y).getPosY()));
			if (ledMatrix.at(x).at(y).state()) {
				led.setFillColor(onColor);
			}
			else {
				led.setFillColor(offColor);
			}

			if (sf::Mouse::getPosition(*window).x >= ledMatrix.at(x).at(y).getPosX() && sf::Mouse::getPosition(*window).x <= ledMatrix.at(x).at(y).getPosX() + ledMatrix.at(x).at(y).getWidth() && sf::Mouse::getPosition(*window).y >= ledMatrix.at(x).at(y).getPosY() && sf::Mouse::getPosition(*window).y <= ledMatrix.at(x).at(y).getPosY() + ledMatrix.at(x).at(y).getHeight() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				ledMatrix.at(x).at(y).chState(true);
			}
			else if (sf::Mouse::getPosition(*window).x >= ledMatrix.at(x).at(y).getPosX() && sf::Mouse::getPosition(*window).x <= ledMatrix.at(x).at(y).getPosX() + ledMatrix.at(x).at(y).getWidth() && sf::Mouse::getPosition(*window).y >= ledMatrix.at(x).at(y).getPosY() && sf::Mouse::getPosition(*window).y <= ledMatrix.at(x).at(y).getPosY() + ledMatrix.at(x).at(y).getHeight() && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				ledMatrix.at(x).at(y).chState(false);
			}
			led.setOutlineColor(sf::Color(255, 255, 255, 100));
			led.setOutlineThickness(1);
			window->draw(led);
			//ghosting the previous frame
			if (currentFrame != 0) {
				if (frames.at(currentFrame - 1).at(x).at(y) == 1) {
					//width and height is the same for all leds
					sf::RectangleShape ghostLed(sf::Vector2f(width / ledsX, height / ledsY));
					ghostLed.setPosition(sf::Vector2f(x * width / ledsX + matrixPosX, y * height / ledsY + matrixPosY));
					ghostLed.setFillColor(sf::Color(255, 0, 0, 100));
					window->draw(ghostLed);
				}
			}
		}
	}
}

void Matrix::clear()
{
	for (int x = 0; x < ledsX; x++) {
		for (int y = 0; y < ledsY; y++) {
			ledMatrix.at(x).at(y).chState(false);
		}
	}
	saveFrame();
}

void Matrix::applyData()
{
	for (int x = 0; x < ledsX; x++) {
		for (int y = 0; y < ledsY; y++) {
			if (frames.at(currentFrame).at(x).at(y) == 1) {
				ledMatrix.at(x).at(y).chState(true);
			}
			else {
				ledMatrix.at(x).at(y).chState(false);
			}
		}
	}
}

void Matrix::newFrame()
{
	if (currentFrame == frames.size() - 1) {
		saveFrame();
		std::vector<std::vector<int>> frameTemp;
		for (int x = 0; x < ledsX; x++) {
			std::vector<int> xyTemp;
			for (int y = 0; y < ledsY; y++) {
				xyTemp.push_back(0);
			}
			frameTemp.push_back(xyTemp);
		}
		frames.push_back(frameTemp);
		currentFrame++;
		clear();
	}
}

void Matrix::nextFrame()
{
	if (currentFrame < frames.size() - 1) {
		currentFrame++;
		applyData();
	}
}

void Matrix::prevFrame()
{
	if (currentFrame > 0) {
		currentFrame--;
		applyData();
	}
}

void Matrix::saveFrame()
{
	for (int x = 0; x < ledsX; x++) {
		for (int y = 0; y < ledsY; y++) {
			if (ledMatrix.at(x).at(y).state()) {
				frames.at(currentFrame).at(x).at(y) = 1;
			}
			else {
				frames.at(currentFrame).at(x).at(y) = 0;
			}
		}
	}
}

int Matrix::getCurrentFrame()
{
	return currentFrame;
}

void Matrix::saveToFile()
{
	std::ofstream outfile("MatrixFramesArray.txt");
	outfile << "{";
	//Array structure => [frame][x][y]
	for (int f = 0; f < frames.size(); f++) {
		outfile << "{";
		for (int x = 0; x < frames.at(f).size(); x++) {
			outfile << "{";
			for (int y = 0; y < frames.at(f).at(x).size(); y++) {
				outfile << frames.at(f).at(x).at(y);
				if (y < frames.at(f).at(x).size() - 1) {
					outfile << " ,";
				}
			}
			outfile << "}";
			if (x < frames.at(f).size() - 1) {
				outfile << " ,\n";
			}
			else {
				outfile << "\n";
			}
		}
		outfile << "}";
		if (f < frames.size() - 1) {
			outfile << " ,\n";
		}
		else {
			outfile << "\n";
		}
	}
	outfile << "}";
}


