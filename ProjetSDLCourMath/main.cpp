#include <iostream>
#include <stdio.h>
#include <SDL.h>

/*
//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;

//startup sdl and create window
bool init();

//load media
bool loadMedia();

//free media and shut down sdl
void close();

//have to do the main like this in order to use the sdl
int main(int argc, char *argv[])
{	
	//The window we'll be rendering to 
	SDL_Window* window = NULL;

	//The surface contained by the window 
	SDL_Surface* screenSurface = NULL; 

	//Initialize SDL
	//go to -1 if everything gone wrong
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else 
		{ 
			//Get window surface 
			screenSurface = SDL_GetWindowSurface( window ); 

			//Fill the surface white 
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) ); 

			//Update the surface 
			SDL_UpdateWindowSurface( window ); 

			//Wait two seconds 
			SDL_Delay( 2000 ); 
		} 
	}

	//Destroy window 
	SDL_DestroyWindow( window ); 
	
	//Quit SDL subsystems 
	SDL_Quit(); 
	
	return 0;
}

//startup sdl and create window

bool init(){
	//init flag
	bool success =true;

	//init sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("sdl could not initialize! SDL error:", SDL_GetError);
		success = false;
	}
	else {
		//create window
		gWindow = SDL_CreateWindow("sdl tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	}

}

//load media
bool loadMedia(){}

//free media and shut down sdl
void close(){}
*/