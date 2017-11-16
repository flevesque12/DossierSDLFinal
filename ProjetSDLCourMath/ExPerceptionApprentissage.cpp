#include <iostream>
using namespace std;

#include <conio.h>
#include <time.h>
#include <ctime>

#include "Donnee.h"
#include "EnsembleDonne.h"

#define DONNE_MAX 10

int main() {

	double initial;
	double initial2;

	double const n = 0.2;
	
	srand((unsigned int)time(NULL));
	int nbDonnee = 20;

	EnsembleDonnee ensembleDonnee1;
	EnsembleDonnee ensembleDonnee2;

	for (int i = 0; i < nbDonnee; i++) {
		ensembleDonnee1.AjouterDonnee(Donnee(1,5+rand()%10, 5+rand()%10));
	}

	for (int i = 0; i < nbDonnee; i++) {
		ensembleDonnee2.AjouterDonnee(Donnee(-1, -5 - rand() % 10, -5 - rand() % 10));
	}
	
	initial = ensembleDonnee1.InitialisationVecteur(Donnee(0, rand() % 20, rand() % 20));
	

	ensembleDonnee1.AfficherDonne();
	//ensembleDonnee2.AfficherDonne();
	cout << endl;
	ensembleDonnee1.VerificationApprentissage(12);

	cout << "x2: " << initial << endl;
	
	system("PAUSE");
	return 0;
}