#include "Pack.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Pack::Pack() {
  itemLimit = 10;
}


Pack::~Pack() {
  
}


int Pack::getItemLimit() {
  return itemLimit;
}


void Pack::setItemLimit(int limit) {
  itemLimit = limit;
}
