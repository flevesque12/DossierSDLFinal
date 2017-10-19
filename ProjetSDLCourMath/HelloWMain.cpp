#pragma once
#include <iostream>
#include <stdio.h>
#include <SDL.h>
/*


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

enum KeyPresseSurface
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN, 
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};




#pragma region VariablesGlobals
//dont use global variable by default
//always put the pointer on null
//the window we be rendering to
SDL_Window *gWindow = NULL;

//the surface contain by the window
SDL_Surface *gScreenSurface = NULL;

//current display image
SDL_Surface *gScreenSurgace = NULL;

//the images correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//the image we will load and show on screen(will use the cpu to render the image)
SDL_Surface *gHelloWorld = NULL;

//Current displayed image 
SDL_Surface *gCurrentSurface = NULL;

SDL_Surface *gStretchedSurface = NULL;

SDL_Renderer *gRenderer = NULL;

#pragma endregion

#pragma region AllFunction


//startup sdl and create window
bool init();

//load media
bool loadMedia();

//Loads individual image
SDL_Surface *loadSurface(std::string path);

//free media and shut down sdl
void close();

#pragma endregion

//have to do the main like this in order to use the sdl
int main(int argc, char *argv[])
{
		
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" ); 
	} 
	else
	{
		//Load media 
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag 
			bool quit = false;
			//Event handler 
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			//While application is running (Main loop(core of the application))
			#pragma region MainLoop
			while (!quit)
			{
				//Handle events on queue (keep processing the event queue until it is empty(ret 0 when empty))
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					
					else if (e.type == SDL_KEYDOWN)
					{
						//Select surfaces based on key press 
						switch( e.key.keysym.sym )
						{
							case SDLK_UP: gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ]; break;
							case SDLK_DOWN: gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ]; break;
							case SDLK_LEFT: gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ]; break;
							case SDLK_RIGHT: gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ]; break; 
							default: gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ]; break; 
						}
					}
				}
				
				//Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				

				SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

				//Apply the image take a source surface and stamp a copy of it into the destination surface
				//render to the back buffer before to see the screen
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				
				//Clear screen 
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render red filled quad 
				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderFillRect( gRenderer, &fillRect );
				
				//Render green outlined quad
				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 }; 
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF ); 
				SDL_RenderDrawRect( gRenderer, &outlineRect );
				
				//Draw blue horizontal line 
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
				SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );
				
				//Draw vertical line of yellow dots 
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF ); 
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
				}

				//Update screen 
				SDL_RenderPresent( gRenderer );

				//Update the surface (front buffer)
				//SDL_UpdateWindowSurface(gWindow);
				
				
			}
			#pragma endregion
		}
	}
	//Free resources and close SDL 
	close(); 
	//system("PAUSE");
	return 0;
}

bool init()
{
	//init flag
	bool success = true;

	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("sdl counld not initialise! SDL error: ", SDL_GetError());
		success = false;
	}
	else 
	{
		//create windows
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) 
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;			
		}
		else
		{
			//create renderer for windows
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("renderer could not loaded");
				success = false;
			}
			else
			{
				//init renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

			//get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			
		}
	}

	return success;
}


bool loadMedia() { 
	//Loading success flag 
	bool success = true; 
	
	//Load default surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "press.bmp" ); 
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	} 
	//Load up surface 
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL ) 
	{
		printf( "Failed to load up image!\n" ); 
		success = false;
	}
	
	//Load down surface 
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL ) 
	{ 
		printf( "Failed to load down image!\n" ); 
		success = false;
	} 
	
	//Load left surface 
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" ); 
		success = false; 
	} 

	//Load right surface 
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "right.bmp" ); 
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL ) 
	{ 
		printf( "Failed to load right image!\n" ); 
		success = false;
	}

	//Load stretching surface
	gStretchedSurface = loadSurface("stretch.bmp");
	if (gStretchedSurface == NULL)
	{
		printf("Failed to load stretching image!\n");
		success = false;
	}

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "hello.bmp" ); 	
	if( gHelloWorld == NULL ) 
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "hello.bmp", SDL_GetError() );
		success = false; 
	} 
	
	return success;
}

void close() { 
	//Deallocate surface 
	SDL_FreeSurface( gHelloWorld ); 
	gHelloWorld = NULL;

	SDL_DestroyRenderer(gRenderer);

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL; 
	gRenderer = NULL;
	//Quit SDL subsystems
	SDL_Quit(); 
}

SDL_Surface* loadSurface(std::string path) { 

	//The final optimized image 
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path 
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
	}
	else {
		//Convert surface to screen format 
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL ); 
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface ); 
	}	

	return optimizedSurface;
}

*/