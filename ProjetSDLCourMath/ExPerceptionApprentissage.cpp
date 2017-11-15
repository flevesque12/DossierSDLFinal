#include <iostream>
using namespace std;

#include <conio.h>
#include <time.h>
#include <ctime>

#include "Donnee.h"
#include "EnsembleDonne.h"

#define DONNE_MAX 10

int main() {

	double const n = 0.2;
	
	srand((unsigned int)time(NULL));
	

	EnsembleDonnee ensembleDonnee1;
	EnsembleDonnee ensembleDonnee2;


	for (int i = 0; i < 10; i++) {
		ensembleDonnee1.AjouterDonnee(Donnee(rand() % 10 + 5, rand() % 10 + 5));
	}

	for (int i = 0; i < 10; i++) {
		ensembleDonnee2.AjouterDonnee(Donnee(rand() % 10 - 5, rand() % 10 - 5));
	}
	


	system("PAUSE");
	return 0;
}