#include "Camp.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Camp::Camp() {
  icon = '@';
  energyCost = 0;
  type = "Camp";
}

/***********************************************************************************************
** Description: This method sets the number of spaces that should be revealed to 1, then the
** number of spaces to the north, east, south and west of the current space that haven't been
** discovered are counted, and if there are fewer undiscovered spaces than 1, no space is
** marked as discovered. Otherwise, a while loop randomly picks a direction and reveals a spot
** on the map by marking it as discovered, if the spot is a valid pointer that has not yet been
** discovered.
***********************************************************************************************/
void Camp::search() {

  int spacesRevealed = 0;

  int spacesToReveal = 1;

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

  searched = true;

}
