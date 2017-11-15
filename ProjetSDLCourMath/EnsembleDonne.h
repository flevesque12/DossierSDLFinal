#pragma once
#include "Donnee.h"

#define DONNEE_MAX 10 


class EnsembleDonnee {

public:
	int nbDonnee = 0;
	Donnee donnees[DONNEE_MAX];

	void AjouterDonnee(const Donnee& d);

	void AfficherDonne();
};
