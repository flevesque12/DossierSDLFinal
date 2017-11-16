#pragma once
#include "Donnee.h"

#define DONNEE_MAX 20 

class EnsembleDonnee {

public:
	int nbDonnee = 0;
	double tauxApp = 0.2;
	Donnee donnees[DONNEE_MAX];

	Donnee nouvelleDonnees[DONNEE_MAX];

	void AjouterDonnee(const Donnee& d);

	void AfficherDonne();

	double InitialisationVecteur(const Donnee& d);

	void VerificationApprentissage(double x);

};
