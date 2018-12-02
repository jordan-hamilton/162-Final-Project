#include "Space.hpp"

using std::string;

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Space::Space() {
  north = nullptr, east = nullptr, west = nullptr, south = nullptr;
  energyCost = 1;
  type = "";
}


Space::~Space() {

}


bool Space::isPlayerHere() {
  return playerHere;
}


int Space::getEnergyCost() {
  return energyCost;
}


string Space::getType() {
  return type;
}


Space* Space::getNorth() {
  return north;
}


Space* Space::getEast() {
  return east;
}


Space* Space::getWest() {
  return west;
}


Space* Space::getSouth() {
  return south;
}


void Space::setPlayerHere(bool presence) {
  playerHere = presence;
}


void Space::setEnergyCost(int cost) {
  energyCost = cost;
}


void Space::setType(string terrainType) {
  type = terrainType;
}


void Space::setNorth(Space* northIn) {
  north = northIn;
}


void Space::setEast(Space* eastIn) {
  east = eastIn;
}


void Space::setWest(Space* westIn) {
  west = westIn;
}


void Space::setSouth(Space* southIn) {
  south = southIn;
}
