#pragma once
#include <iostream>
#include <SDL.h>

class Dot {
public:
	//dimension of the dot
	static const int dotHeight = 20;
	static const int dotWidth = 20;

	//velocity of the dot
	static const int dotVelocity = 10;

	Dot();

	//key pressed ajuste the dot velocity
	void handleEvent(SDL_Event &e);

	//mopve the dot
	void move();

	//show the dot on screen
	void render();

private:
	// the x and y offset of the dot
	int movePosX, movePosY;

	//the velocity(vitesse) of the dot
	int moveVelX, moveVelY;
};
