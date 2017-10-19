#include <iostream>
using namespace std;

#include "SDL.h"
#include <conio.h>
#include <time.h>
#include <ctime>

#define WIDTH 800
#define HEIGHT 800
#define PI 3.141592653589793

class Point {
public:
	double x, y;

	Point() {
	}

	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double distanceCarre(const Point& p) const {
		return (this->x - p.x)*(this->x - p.x) +
			(this->y - p.y)*(this->y - p.y);
	}

	void afficher(SDL_Renderer *renderer, int r, int g, int b, int taille) {
		SDL_Rect rect;
		rect.w = taille;
		rect.h = taille;
		rect.x = x - taille / 2;
		rect.y = y - taille / 2;

		SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);
	}

	
};

#define MAX_POINTS 1000

class NuagePoints {
public:
	Point lesPoints[MAX_POINTS];
	int nbPoints = 0;

	void ajouterPoint(const Point& p) {
		lesPoints[nbPoints++] = p;
	}

	int pointPlusProche(const Point& p) {
		int indiceMin = -1;

		if (nbPoints > 0) {
			double dMin = p.distanceCarre(lesPoints[0]);
			indiceMin = 0;

			for (int i = 1; i < nbPoints; i++) {
				double d = p.distanceCarre(lesPoints[i]);

				if (d < dMin) {
					dMin = d;
					indiceMin = i;
				}
			}
		}

		return indiceMin;
	}

	void afficher(SDL_Renderer* renderer, int r, int g, int b) {
		SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)SDL_ALPHA_OPAQUE);

		for (int i = 0; i < nbPoints; i++) {
			lesPoints[i].afficher(renderer, r, g, b, 4);
		}
	}

	Point isobarylCentre() {
		Point iso;
		iso.x = 0;
		iso.y = 0;

		for (int i = 0; i < nbPoints; i++) {
			iso.x += lesPoints[i].x;
			iso.y += lesPoints[i].y;
		}

		iso.x /= nbPoints;
		iso.y /= nbPoints;

		return iso;
	}
	
	void TracerCercle(SDL_Renderer *renderer, Point pFlottant) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 155, 123);

		Point rayon;
		Point pDroite;

		//afficher le centre et un point
		Point centre(WIDTH / 2, HEIGHT / 2);
		centre.afficher(renderer, 0, 0, 255,10);
		
		Point p(WIDTH/2+245, HEIGHT/2);
		p.afficher(renderer, 0, 255, 255, 15);

		Point p2(WIDTH / 2 - 245, HEIGHT / 2);
		p2.afficher(renderer, 0, 255, 255, 15);

		rayon.x = p.x - centre.x;
		rayon.y = p.y - centre.y;

		pDroite.x = pFlottant.x - centre.x;
		pDroite.y = pFlottant.y - centre.y;


		//affichage du cercle
		double alpha = 0;
		double pasAlpha = 2 * PI / 100;

		double x;
		double y;

		//fait le tour du cercle
		while (alpha <2 * PI)
		{		
				x = WIDTH / 2 + 245 * cos(alpha);
				y = HEIGHT / 2 -245 * sin(alpha);

				SDL_RenderDrawPoint(renderer, x, y);
			
			
			
			alpha += pasAlpha;
			
		}

		if (sqrt(pDroite.x + pDroite.y) <= sqrt(rayon.x + rayon.y)) {
			pFlottant.afficher(renderer, 255, 0, 255, 20);
		}

	}
};

enum TypeEvenement {
	EVT_AUCUN, EVT_SOURIS, EVT_CLAVIER
};

//	récupère un évènement (non bloquant)
TypeEvenement lireEvenement(int &x, int &y, int &touche) {
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
}


int main(int argc, char** argv) {
#pragma region initialisation SDL
	//	initialisation SDL
	SDL_Window* fenetre = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "ERREUR : SDL non initialisé!" << endl;
		exit(0);
	}


	SDL_ShowCursor(SDL_DISABLE);

	//	création de la fenêtre et de son renderer
	fenetre = SDL_CreateWindow("titre", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(fenetre, 0, 0);
#pragma endregion initialisation SDL	

	NuagePoints nuage;

	//point qui bouge
	Point p(WIDTH / 2, HEIGHT / 2);
	

	bool fin = false;
	while (!fin) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		//pD.afficher(renderer, 255, 255, 255, 20);
		p.afficher(renderer, 0, 255, 0, 20);
		
		nuage.TracerCercle(renderer,p);

		SDL_Rect textureRect;	


		
		//	on montre le rendu
		SDL_RenderPresent(renderer);

		//	on gère son déplacement
		int x, y, touche;		

		TypeEvenement evt = lireEvenement(x, y, touche);
		if (evt == EVT_CLAVIER) {	//	- avec le clavier
			switch (touche) {
			case 'w':
				p.y -= 4; break;
			case 's':
				p.y += 4; break;
			case 'a':
				p.x -= 4; break;
			case 'd':
				p.x += 4; break;
				// test de sortie du programme
			case ' ': fin = true;
			}
		}
		else if (evt == EVT_SOURIS) {	//	- avec la souris
			p.x = x;
			p.y = y;
		}
	}

#pragma region sortie SDL
	//	suppression de la fenêtre et sortie SDL
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
#pragma endregion sortie SDL

	return 0;
}

