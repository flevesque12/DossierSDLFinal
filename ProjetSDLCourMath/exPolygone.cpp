#include <iostream>
using namespace std;

#include "SDL.h"
#include <conio.h>
#include <time.h>
#include <ctime>

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
	
	void ExerciceProdVectoriel(Point a, Point b, Point c, SDL_Renderer *renderer) {
		Point vectorAB;
		Point vectorAC;

		double prodVectoriel;

		vectorAB.x = b.x - a.x;
		vectorAB.y = b.y - a.y;

		vectorAC.x = c.x - a.x;
		vectorAC.y = c.y - a.y;

		prodVectoriel = (vectorAB.y * vectorAC.x) - (vectorAB.x * vectorAC.y);
		if (prodVectoriel < 0) {
			c.afficher(renderer, (Uint8)255, (Uint8)255, (Uint8)0, 40);
		}		
	}

	void CalculProdVectoriel(SDL_Renderer *renderer, Point p1, Point p2,Point pMove) {
		Point vectorAB;
		Point vectorAC;

		double prodVectoriel;

		vectorAB.x = p2.x - p1.x;
		vectorAB.y = p2.y - p1.y;

		vectorAC.x = pMove.x - p1.x;
		vectorAC.y = pMove.y - p1.y;

		prodVectoriel = (vectorAB.y * vectorAC.x) - (vectorAB.x * vectorAC.y);

		if (prodVectoriel < 0)
		{
			pMove.afficher(renderer, 0, 0, 255, 20);
		}
		else
		{
			pMove.afficher(renderer, 255, 255, 255, 20);
		}
	}
	
};

enum TypeEvenement {
	EVT_AUCUN, EVT_SOURIS, EVT_CLAVIER, EVT_CLICK_SOURIS,QUIT
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

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			cout << "mouse pressed" << endl;
		}

		if (event.type == SDL_QUIT) {
			evt = QUIT;
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
	
	Point p1(200,200);
	Point p2(500,200);
	Point p3(100, 300);
	Point p4(700, 600);
	Point p5(100,400);
	Point p6(200,700);

	nuage.ajouterPoint(p1);
	nuage.ajouterPoint(p2);
	nuage.ajouterPoint(p3);
	nuage.ajouterPoint(p4);
	nuage.ajouterPoint(p5);
	nuage.ajouterPoint(p6);


	bool fin = false;
	while (!fin) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		//affichage
		nuage.afficher(renderer, 255, 0, 0);		
		p.afficher(renderer, 0, 255, 0, 20);

		
		p1.afficher(renderer, 0, 0, 255, 10);
		p2.afficher(renderer, 255, 255, 255, 10);
		p3.afficher(renderer, 255, 0, 0, 10);
		p4.afficher(renderer, 255, 0, 255, 10);
		p5.afficher(renderer,255, 255, 0, 10);
		p6.afficher(renderer, 0, 255, 255, 10);
		

		nuage.CalculProdVectoriel(renderer, p1, p2, p);
		nuage.CalculProdVectoriel(renderer, p2, p3, p);
		nuage.CalculProdVectoriel(renderer, p3, p4, p);
		nuage.CalculProdVectoriel(renderer, p4, p5, p);
		nuage.CalculProdVectoriel(renderer, p5, p6, p);
		nuage.CalculProdVectoriel(renderer, p6, p1, p);

		

		SDL_Rect textureRect;	


		//nuage.ExerciceProdScalaire(pA, pB, p,renderer);
		//nuage.ExerciceProdVectoriel(pA, pB, p, renderer);
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
*/



