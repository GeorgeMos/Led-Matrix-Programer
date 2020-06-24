#include "Led.h"

Led::Led()
{
}

Led::Led(int posX, int posY, int width, int height)
{
	this->posX = posX;
	this->posY = posY;
	this->height = height;
	this->width = width;
}

bool Led::state() {
	return this->isOn;
}
void Led::chState(bool state) {
	this->isOn = state;
}
void Led::chPos(int x, int y) {
	this->posX = x;
	this->posY = y;
}
int Led::getPosX() {
	return this->posX;
}
int Led::getPosY() {
	return this->posY;
}

int Led::getWidth()
{
	return width;
}

int Led::getHeight()
{
	return height;
}

void Led::setWidth(int width)
{
	this->width = width;
}

void Led::setHeight(int height)
{
	this->height = height;
}
