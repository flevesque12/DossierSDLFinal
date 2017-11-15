#include "EnsembleDonne.h"
#include <iostream>

void EnsembleDonnee::AjouterDonnee(const Donnee& d){
	donnees[nbDonnee++] = d;
}

void EnsembleDonnee::AfficherDonne() {
	for (int i = 0; i < nbDonnee; i++) {
		std::cout << ""+donnees[i]<< std::endl;
	}
}