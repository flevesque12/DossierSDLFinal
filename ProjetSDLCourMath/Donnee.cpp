#pragma once
#include "Donnee.h"

Donnee::Donnee() {

}


Donnee::Donnee(double classification,double w1, double w2) {
	this->classification = classification;
	this->w1 = w1;
	this->w2 = w2;
}