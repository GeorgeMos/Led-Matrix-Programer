#pragma once
class Led
{
private:
	//All the leds are off by default
	bool isOn = false;
	int posX;
	int posY;
	int width;
	int height;
public:
	Led();
	Led(int posX, int posY, int width, int height);
	bool state();
	void chState(bool state);
	void chPos(int x, int y);
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
};

