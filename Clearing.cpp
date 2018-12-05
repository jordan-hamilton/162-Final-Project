#include "Clearing.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Clearing::Clearing() {
  icon = '_';
  energyCost = 1;
  type = "Clearing";
}


/***********************************************************************************************
** Description: This method sets the itemScavenged variable to true if generating a random
** number between 0 and 2 returns 0, meaning a 33% chance of scavenging this type of space. This
** is used so the game can add an item to the player's backpack if space search reveals the
** itemScavenged variable is updated to true.
***********************************************************************************************/
void Clearing::scavenge() {

  if (generateNumber(3) == 0) {
    itemScavenged = true;
  };

}


/***********************************************************************************************
** Description: This method generates a random number between 1 and 2 to determine whether 1
** or 2 spaces will be revealed while searching from this space. The number of spaces to the
** north, east, south and west of the current space that haven't been discovered are counted,
** and if there are fewer undiscovered spaces than the random number, the lesser of those two
** numbers will be revealed on the map. A while loop randomly picks a direction and reveals a
** spot on the map by marking it as discovered, if the spot is a valid pointer that has not yet
** been discovered.
***********************************************************************************************/
void Clearing::scout() {

  int spacesRevealed = 0;

  int spacesToReveal = rand() % 2 + 1;

  int discoverableSpaces = getDiscoverableSpaces();

  if (spacesToReveal > discoverableSpaces) {
    spacesToReveal = discoverableSpaces;
  }

  while (spacesRevealed < spacesToReveal) {

    int direction = rand() % 4;

    switch (direction) {

      case North: if ( revealSpace(north) ) {
                    spacesRevealed++;
                  }
                  break;

      case East:  if ( revealSpace(east) ) {
                    spacesRevealed++;
                  }
                  break;

      case South: if ( revealSpace(south) ) {
                    spacesRevealed++;
                  }
                  break;

      case West:  if ( revealSpace(west) ) {
                    spacesRevealed++;
                  }
                  break;

    }

  }

}
