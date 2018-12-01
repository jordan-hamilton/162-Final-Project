#include "Space.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Space::Space() {
  top = nullptr, right = nullptr, left = nullptr, bottom = nullptr;
  energyCost = 1;
}


Space::~Space() {
  
}


int Space::getEnergyCost() {
  return energyCost;
}


void Space::setEnergyCost(int cost) {
  energyCost = cost;
}
