#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "Point.h"
#include "NuagePoint.h"

#define PI 3.1415

using namespace std;

double piApproximatif(int nbJets) {

	
	int nbDansCercle = 0;

	for (int i = 0; i < nbJets; i++) {
		//												0x2ffffff
		double x = (double)((rand() << 15)+ rand()) / (1 << 30 - 1);
		double y = (double)((rand() << 15) + rand()) / (1 << 30 - 1);

		//nbre de fois que ca tombe a l'intérieur du disque
		if ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) <= 0.25)
			nbDansCercle++;
	}
	
	return (double)nbDansCercle / nbJets * 4;
}


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*
int main(int argc, char *argv[]){

	int touche = 0;

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	SDL_Renderer* renderer = NULL;

	SDL_bool done = SDL_FALSE;


	//creation de point
	
	Point p1(27, 123);
	Point p2(57, 88);
	Point p3(110, 83);
	Point p4(100, 227);
	Point p5(232, 500);
	Point p6(230, 300);

	Point pFlottant(20, 20);	

	NuagePoint nuage;

	nuage.ajouterPoints(p1);
	nuage.ajouterPoints(p2);
	nuage.ajouterPoints(p3);
	nuage.ajouterPoints(p4);
	nuage.ajouterPoints(p5);
	nuage.ajouterPoints(p6);

	Point pointPlusProche = nuage.pointPlusProche(pFlottant);	
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

		srand((unsigned int)time(NULL));
		NuagePoint cloud;
		for (int i = 0; i < 20; i++) {
			cloud.ajouterPoints(Point(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
		}

		Point p(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		while (!done)
		{
			
			SDL_Event event;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			cloud.afficher(renderer, 255, 255, 255,3);

			//cloud.point[cloud.pointPlusProche(p)].afficher(renderer, 0, 255, 0, 10);
			/*
			//mettre le point flottant en rouge
			if (_kbhit() != 0) {
				int touche = _getch();
				switch (touche)
				{
					case 'w':pFlottant.y -= 1; break;
					case 's':pFlottant.y += 1; break;
					case 'a':pFlottant.y -= 1; break;
					case 'd':pFlottant.y += 1; break;
				}

				SDL_SetRenderDrawColor(renderer, (Uint8)255, (Uint8)0, (Uint8)0, 0xFF);
				SDL_RenderDrawPoint(renderer, pFlottant.x, pFlottant.y);
			}*/
			

			//SDL_RenderPresent(renderer);


			//Get window surface
			//screenSurface = SDL_GetWindowSurface(window);

			//Update the surface
			//SDL_UpdateWindowSurface(window);

			
		//}

	//}


	/*

	cout << "Le point flottant: " << pFlottant.x << "; " << pFlottant.y << endl;
	cout << "Le point le plus proche du point d'origine: " << pointPlusProche.x << "; " << pointPlusProche.y << endl;


	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10; i++) 
	{
		cout << piApproximatif(10) << endl;
	}
	*/
	//system("PAUSE");
//	return 0;
//}
