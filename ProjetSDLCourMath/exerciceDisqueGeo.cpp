#include <iostream>
using namespace std;

#include "SDL.h"
#include <conio.h>
#include <time.h>
#include <ctime>
#include <cmath>

#define WIDTH 800
#define HEIGHT 800
#define PI 3.141592653589793
/*
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
	
	//exercice point a l'interieur du disque
	void TracerCercle(SDL_Renderer *renderer, Point pFlottant) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 155, 123);

		Point rayon(0,0);
		Point pDroite(0,0);

		//afficher le centre et un point
		Point centre(WIDTH / 2, HEIGHT / 2);
		centre.afficher(renderer, 0, 0, 255,10);
		
		Point p(WIDTH/2+245, HEIGHT/2);
		p.afficher(renderer, 0, 255, 255, 15);

		Point p2(WIDTH / 2 - 245, HEIGHT / 2);
		p2.afficher(renderer, 0, 255, 255, 15);

		rayon.x = centre.x - p.x;
		rayon.y = centre.y - p.y;

		pDroite.x = centre.x - pFlottant.x;
		pDroite.y = centre.y - pFlottant.y;


		//affichage du cercle
		double alpha = 0;
		double pasAlpha = 2 * PI / 100;

		double x;
		double y;

		//fait le tour du cercle
		while (alpha <2 * PI)
		{		
			x = WIDTH / 2 + 245 * cos(alpha);
			y = HEIGHT / 2 - 245 * sin(alpha);

			SDL_RenderDrawPoint(renderer, x, y);
			
			alpha += pasAlpha;
		}

		double expXY = pow(pDroite.x + pDroite.y,2);
		double rayon2 = pow(rayon.x + rayon.y,2);

		if (expXY >= rayon2) {
			pFlottant.afficher(renderer, 255, 0, 255, 20);
		}

		//cout << rayon.x << "::" << rayon.y << endl;
		//cout << expXY << "::" << rayon2 << endl;

	}

	void tracerCercleGeo(SDL_Renderer *renderer, int r, int g, int b, Point centre, Point pt ) {
		SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)SDL_ALPHA_OPAQUE);
		Point rayon(0, 0);
		Point pDroite(0, 0);

		Point point3(500, 200);
		Point point4(300, 300);


		//afficher le centre et un point
		Point p(WIDTH / 2 + pt.x, HEIGHT / 2 - pt.y);
		//p.afficher(renderer, 0, 255, 255, 15);
		centre.afficher(renderer, 0, 0, 255, 10);
		point3.afficher(renderer, 0, 0, 255, 10);

		
		rayon.x = centre.x - pt.x;
		rayon.y = centre.y - pt.y;
		
		//affichage du cercle
		double alpha = 0;
		double pasAlpha = 2 * PI / 10000;

		double x;
		double y;

		double x2;
		double y2;

		//fait le tour du cercle
		while (alpha <2 * PI)
		{
			x = centre.x + pt.x * cos(alpha);
			y = centre.y - pt.y * sin(alpha);

			x2 = point3.x + point4.x * cos(alpha);
			y2 = point3.y - point4.y * sin(alpha);

			if (x == x2 && y == y2) {
				cout << "point crois�" << endl;
			}

			SDL_RenderDrawPoint(renderer, x, y);
			SDL_RenderDrawPoint(renderer, x2, y2);

			alpha += pasAlpha;
		}		
	}

	Point geolocalisation(Point p1, Point p2, Point p3,double dA,double dB,double dC) {


	}
};


enum TypeEvenement {
	EVT_AUCUN, EVT_SOURIS, EVT_CLAVIER
};

//	r�cup�re un �v�nement (non bloquant)
TypeEvenement lireEvenement(int &x, int &y, int &touche) {
	TypeEvenement evt = EVT_AUCUN; //	aucun �v�nement

	SDL_Event event;
	if (SDL_PollEvent(&event) == SDL_TRUE) {
		if (event.type == SDL_KEYDOWN) {
			touche = event.key.keysym.sym;

			evt = EVT_CLAVIER;	//	�v�nement de clavier
		}
		if (event.type == SDL_MOUSEMOTION) {
			x = event.motion.x;
			y = event.motion.y;

			evt = EVT_SOURIS;	//	�v�nement de souris
		}
	}

	return evt;
}


int main(int argc, char** argv) 
{
#pragma region initialisation SDL
	//	initialisation SDL
	SDL_Window* fenetre = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "ERREUR : SDL non initialis�!" << endl;
		exit(0);
	}


	SDL_ShowCursor(SDL_DISABLE);

	//	cr�ation de la fen�tre et de son renderer
	fenetre = SDL_CreateWindow("titre", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(fenetre, 0, 0);
#pragma endregion initialisation SDL	

	NuagePoints nuage;

	//point qui bouge
	Point p(WIDTH / 2, HEIGHT / 2);
	
	//Point pCentre(400, 400);
	Point pCentre2(300, 500);


	//Point point(300, 300);
	Point point2(300, 300);

	Point point3(500, 200);
	Point point4(300, 300);

	bool fin = false;

	while (!fin) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		//pD.afficher(renderer, 255, 255, 255, 20);
		p.afficher(renderer, 0, 255, 0, 20);
		
		//nuage.tracerCercleGeo(renderer, 255, 0, 0, pCentre, point);
		nuage.tracerCercleGeo(renderer, 255, 255, 0, pCentre2, point2);
		//nuage.tracerCercleGeo(renderer, 233, 2, 222, point3, point4);


		SDL_Rect textureRect;	


		
		//	on montre le rendu
		SDL_RenderPresent(renderer);

		//	on g�re son d�placement
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
	//	suppression de la fen�tre et sortie SDL
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
#pragma endregion sortie SDL

	return 0;
}
*/
