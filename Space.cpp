#include "Space.hpp"

using std::string;

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Space::Space() {
  north = nullptr, east = nullptr, west = nullptr, south = nullptr;
  hikerHere = false;
  playerHere = false;
  discovered = false;
  searched = false;
  icon ='\0';
  energyCost = 1;
  type = "";
}


Space::~Space() {

}


bool Space::isHikerHere() {
  return hikerHere;
}


bool Space::isPlayerHere() {
  return playerHere;
}


bool Space::wasDiscovered() {
  return discovered;
}


bool Space::wasSearched() {
  return searched;
}


char Space::getIcon() {

  if (hikerHere) {
    return '!';
  } else if (playerHere) {
    return '*';
  } else if (discovered) {
    return icon;
  } else {
    return icon;//DEBUG:'?';
  }

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


Space* Space::getSouth() {
  return south;
}


Space* Space::getWest() {
  return west;
}


void Space::setHikerHere(bool presenceStatus) {
  hikerHere = presenceStatus;
}


void Space::setPlayerHere(bool presenceStatus) {
  playerHere = presenceStatus;

  if (playerHere) {
    discovered = true;
  }

}


void Space::setDiscovered(bool discoveryStatus) {
  discovered = discoveryStatus;
}


void Space::setSearched(bool searchStatus) {
  searched = searchStatus;
}


void Space::setIcon(char iconIn) {
  icon = iconIn;
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


void Space::setSouth(Space* southIn) {
  south = southIn;
}


void Space::setWest(Space* westIn) {
  west = westIn;
}
