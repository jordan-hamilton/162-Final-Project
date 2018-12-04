#include "Pack.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Pack::Pack() {
  itemLimit = 10;
}


Pack::~Pack() {

}


void Pack::addItem(const std::string &nameIn, const int &valueIn) {

  Item newItem(nameIn, valueIn);

  items.push_back(newItem);
  
}


/***********************************************************************************************
** Description: Checks the size of the items stack, and returns true if the stack's size is
** greater than 0. Otherwise, this method returns false.
***********************************************************************************************/
bool Pack::hasItems() {

  if (items.size() > 0) {
    return true;
  } else {
    return false;
  }

}


/***********************************************************************************************
** Description: Checks the size of the items stack, and returns true if the stack's size is less
** than the backpack's itemLimit value. Otherwise, it returns false to indicate that more items
** cannot be added to the backpack.
***********************************************************************************************/
bool Pack::hasRoom() {

  if (items.size() < itemLimit) {
    return true;
  } else {
    return false;
  }

}


int Pack::getItemLimit() {
  return itemLimit;
}


void Pack::setItemLimit(int limit) {
  itemLimit = limit;
}
