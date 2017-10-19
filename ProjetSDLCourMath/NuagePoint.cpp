#include <iostream>
#include <math.h>
#include <SDL.h>
#include "NuagePoint.h"

/*

NuagePoint::NuagePoint(){
	nbPoint = 0;
}

void NuagePoint::ajouterPoints(Point p) 
{
	point[nbPoint++];
}

double NuagePoint::distanceCarre(Point pt1, Point pt2) {
	return (pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y);
}

Point NuagePoint::pointPlusProche(Point p)
{
	Point lePlusProche = point[0];

	double dmin = distanceCarre(lePlusProche, p);
	if (nbPoint > 0) {

		for (int i = 1; i < nbPoint; i++) {
			double d = distanceCarre(point[i], p);
			if (d < dmin) {
				lePlusProche = point[i];
				dmin = d;
			}
		}
	}
	return lePlusProche;
}

void NuagePoint::afficher(SDL_Renderer *renderer, int r, int g, int b, int taille) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_Rect rect;
	rect.w = taille;
	rect.h = taille;
	rect.x = 3 - taille / 2;
	rect.y = 3 - taille / 2;

	SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
}

TypeEvenement NuagePoint::lireEvenement(int &x, int &y, int &touche) {
	TypeEvenement evt = EVT_AUCUN; //	aucun évènement

	SDL_Event event;
	if (SDL_PollEvent(&event) == SDL_TRUE) {
		if (event.type == SDL_KEYDOWN) {
			touche = event.key.keysym.sym;

			evt = EVT_CLAVIER;	//	évènement de clavier
		}
		if (event.type == SDL_MOUSEMOTION) {
			x = event.motion.x;
			y = event.motion.y;

			evt = EVT_SOURIS;	//	évènement de souris
		}
	}

	return evt;
}*/