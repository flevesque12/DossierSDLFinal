#include "EnsembleDonne.h"
#include <iostream>


void EnsembleDonnee::AjouterDonnee(const Donnee& d){
	donnees[nbDonnee++] = d;
}

void EnsembleDonnee::AfficherDonne() {
	for (int i = 0; i < nbDonnee; i++) {
		std::cout << donnees[i].classification<<"::";
		std::cout << donnees[i].w1 << "::";
		std::cout << donnees[i].w2 << std::endl;
	}
}

double EnsembleDonnee::InitialisationVecteur(const Donnee& d) {
	double x1 = 1;
	double x2 = 1;
	double res = 0;
	x2 = x2 * donnees->w2;
	x1 = x1 * donnees->w1;;
	res = x1 / x2;
	return res;
}

void EnsembleDonnee::VerificationApprentissage(double res) {
	double resultW0 = 0;
	double resultW1;
	double resultW2;
	int nbDonne = 0;

	double vecteur[DONNEE_MAX];

	for (int i = 0; i < nbDonnee; i++)
	{
		vecteur[i] = donnees[i].classification + donnees[i].w1 + donnees[i].w2;
		if (vecteur[i] > 0) {
			nouvelleDonnees[nbDonne].classification = donnees[i].classification - tauxApp;
			nouvelleDonnees[nbDonne].w1 = donnees[i].w1 - tauxApp;
			nouvelleDonnees[nbDonne].w2 = donnees[i].w2 - tauxApp;
			nbDonne++;
		}
	}

	for (int i = 0; i < nbDonne; i++)
	{
		std::cout << nouvelleDonnees[i].classification << "::";
		std::cout << nouvelleDonnees[i].w1 << "::";
		std::cout << nouvelleDonnees[i].w2 << std::endl;
	}
}