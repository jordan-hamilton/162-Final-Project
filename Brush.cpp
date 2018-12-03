#include "Brush.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Brush::Brush() {
  icon = '#';
  energyCost = 2;
  type = "Brush";
}


/***********************************************************************************************
** Description: This method generates a random number between 0 and 1 to determine whether or
** not a space will be revealed while searching from this space. The number of spaces to the
** north, east, south and west of the current space that haven't been discovered are counted,
** and if there are fewer undiscovered spaces than the random number, the lesser those two
** numbers will be revealed on the map. A while loop randomly picks a direction and reveals a
** spot on the map by marking it as discovered, if the spot is a valid pointer that has not yet
** been discovered.
***********************************************************************************************/
void Brush::search() {

  int spacesRevealed = 0;

  int spacesToReveal = rand() % 2;

  int discoverableSpaces = getDiscoverableSpaces();

  if (spacesToReveal > discoverableSpaces) {
    spacesToReveal = discoverableSpaces;
  }

  while (spacesRevealed < spacesToReveal) {

    int direction = rand() % 4;

    switch (direction) {

      case North: if ( this->getNorth() && !this->getNorth()->wasDiscovered() ) {
                    this->getNorth()->setDiscovered(true);
                    spacesRevealed++;
                    std::cout << "Revealed to the north" << std::endl;
                  }
                  break;

      case East:  if ( this->getEast() && !this->getEast()->wasDiscovered() ) {
                    this->getEast()->setDiscovered(true);
                    spacesRevealed++;
                    std::cout << "Revealed to the east" << std::endl;
                  }
                  break;

      case South: if ( this->getSouth() && !this->getSouth()->wasDiscovered() ) {
                    this->getSouth()->setDiscovered(true);
                    spacesRevealed++;
                    std::cout << "Revealed to the south" << std::endl;
                  }
                  break;

      case West:  if ( this->getWest() && !this->getWest()->wasDiscovered() ) {
                    this->getWest()->setDiscovered(true);
                    spacesRevealed++;
                    std::cout << "Revealed to the west" << std::endl;
                  }
                  break;

    }

  }

  searched = true;

}
