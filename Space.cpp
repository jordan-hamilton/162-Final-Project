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


/***********************************************************************************************
** Description: This method takes a pointer to a space object. If the pointer is valid, the
** method verifies that the space has not been discovered by the player yet, and sets the space
** as discovered. If the space is a null pointer or was a valid pointer but has already been
** discovered by the player, the method returns false, so the search function in the inherited
** classes can attempt to reveal a space in other directions.
***********************************************************************************************/
bool Space::revealSpace(Space* spaceToReveal) {

  bool revealedSuccess = false;

  if (spaceToReveal) {

    if ( !spaceToReveal->wasDiscovered() ){
      spaceToReveal->setDiscovered(true);
      revealedSuccess = true;
    }

  }

  return revealedSuccess;

}


/***********************************************************************************************
** Description: This method checks for valid pointers to the north, east, south, and west of
** the current space, then returns an integer indicating how many of those spaces have been
** marked as discovered. This indicates the maximum number of spaces that can be revealed when
** searching.
***********************************************************************************************/
int Space::getDiscoverableSpaces() {

  int eligibleSpaces = 0;

  if ( north && !north->wasDiscovered()) {
    eligibleSpaces++;
  }

  if ( east && !east->wasDiscovered()) {
    eligibleSpaces++;
  }

  if ( south && !south->wasDiscovered()) {
    eligibleSpaces++;
  }

  if ( west && !west->wasDiscovered()) {
    eligibleSpaces++;
  }

  return eligibleSpaces;

}


/***********************************************************************************************
** Description: Takes a constant reference to an integer for the maximum random value to return,
** then generates and returns a random integer between 0 and 1 less than that value.
***********************************************************************************************/
int Space::generateNumber(const int &max) {
  return rand() % max;
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

  if (hikerHere && discovered) {
    return '!';
  } else if (playerHere) {
    return '*';
  } else if (discovered) {
    return icon;
  } else {
    return '?';
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
