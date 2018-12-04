#include "Space.hpp"

using std::string;

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Space::Space() {
  north = nullptr, east = nullptr, south = nullptr, west = nullptr;
  hikerHere = false;
  playerHere = false;
  discovered = false;
  itemScavenged = false;
  searched = false;
  icon ='\0';
  energyCost = 1;
  type = "";
}


Space::~Space() {

}


void Space::search() {

  scout();
  scavenge();

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
** Description: Takes a constant reference to an integer for the number of possible random
** values that could be returned (between 0 and one less than the passed integer), then
** generates and returns a random integer between 0 and 1 less than that value.
***********************************************************************************************/
int Space::generateNumber(const int &possibilities) {
  return rand() % possibilities;
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


bool Space::wasItemScavenged() {
  return itemScavenged;
}


bool Space::wasSearched() {
  return searched;
}


/***********************************************************************************************
** Description: This method is used to print a map and returns an * at the player's location,
** regardless of the icon assigned to a space. If the hiker is set to a location that has also
** been discovered by the player, an ! is returned. If the space hasn't been discovered by
** the player yet, a ? is returned. If the location doesn't match the previous criteria, then
** the space is discovered and not unique, so the space's icon character is returned.
***********************************************************************************************/
char Space::getIcon() {

  if (playerHere) {
    return '*';
  } else if (hikerHere && discovered) {
    return '!';
  } else if (!discovered) {
    return '?';
  } else {
    return icon;
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


void Space::setHikerHere(const bool &presenceStatus) {
  hikerHere = presenceStatus;
}


/***********************************************************************************************
** Description: Takes a constant reference to a boolean, then sets the playerHere variable to
** that value. If the player is at that space, the space is also marked as discovered.
***********************************************************************************************/
void Space::setPlayerHere(const bool &presenceStatus) {

  playerHere = presenceStatus;

  if (playerHere) {
    discovered = true;
  }

}


void Space::setDiscovered(const bool &discoveryStatus) {
  discovered = discoveryStatus;
}


void Space::setItemScavenged(const bool &itemStatus) {
  itemScavenged = itemStatus;
}


void Space::setSearched(const bool &searchStatus) {
  searched = searchStatus;
}


void Space::setIcon(const char &iconIn) {
  icon = iconIn;
}


void Space::setEnergyCost(const int &cost) {
  energyCost = cost;
}


void Space::setType(const string &terrainType) {
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
