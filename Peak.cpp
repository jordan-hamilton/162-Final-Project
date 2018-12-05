#include "Peak.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Peak::Peak() {
  icon = '^';
  energyCost = 3;
  type = "Peak";
}


/***********************************************************************************************
** Description: This method sets the itemScavenged variable to true if generating a random
** number between 0 and 4 returns 0, meaning a 20% chance of scavenging this type of space. This
** is used so the game can add an item to the player's backpack if space search reveals the
** itemScavenged variable is updated to true.
***********************************************************************************************/
void Peak::scavenge() {

  if (generateNumber(5) == 0) {
    itemScavenged = true;
  };

}


/***********************************************************************************************
** Description: This method attempts to reveal the map in all directions, if the pointers to
** those spaces are valid pointers and locations that haven't yet been revealed.
***********************************************************************************************/
void Peak::scout() {

  revealSpace( this->getNorth() );
  revealSpace( this->getEast() );
  revealSpace( this->getSouth() );
  revealSpace( this->getWest() );

}
