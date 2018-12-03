#include "Peak.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Peak::Peak() {
  icon = '^';
  energyCost = 3;
  type = "peak";
}


void Peak::search() {

  revealSpace( this->getNorth() );
  revealSpace( this->getEast() );
  revealSpace( this->getSouth() );
  revealSpace( this->getWest() );

}
