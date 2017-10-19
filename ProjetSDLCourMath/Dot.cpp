#include <SDL.h>
#include "Dot.h"


Dot::Dot() {
	//init the variable
	movePosX = 0;
	movePosY = 0;

	moveVelX = 0;
	moveVelY = 0;
}

//key pressed ajuste the dot velocity
void Dot::handleEvent(SDL_Event &e) {

	//if key is pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		//adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:moveVelY -= dotVelocity; break;
			case SDLK_DOWN:moveVelY += dotVelocity; break;
			case SDLK_LEFT:moveVelX -= dotVelocity; break;
			case SDLK_RIGHT:moveVelX += dotVelocity; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: moveVelY += dotVelocity; break;
			case SDLK_DOWN: moveVelY -= dotVelocity; break;
			case SDLK_LEFT: moveVelX += dotVelocity; break;
			case SDLK_RIGHT: moveVelX -= dotVelocity; break;
		}
	}

}

//mopve the dot
void Dot::move(){}

//show the dot on screen
void Dot::render(){}