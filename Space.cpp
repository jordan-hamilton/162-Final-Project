#include "Space.hpp"

using std::string;

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Space::Space() {
  top = nullptr, right = nullptr, left = nullptr, bottom = nullptr;
  energyCost = 1;
  type = "";
}


Space::~Space() {

}


int Space::getEnergyCost() {
  return energyCost;
}


string Space::getType() {
  return type;
}


void Space::setEnergyCost(int cost) {
  energyCost = cost;
}


void Space::setType(string terrainType) {
  type = terrainType;
}
