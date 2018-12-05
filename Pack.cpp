#include "Pack.hpp"

using std::cout;
using std::endl;

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Pack::Pack() {
  itemLimit = 10;
}


/***********************************************************************************************
** Description: Takes a constant reference to a string for the name of an item from the game's
** itemStore, and a constant reference to an integer representing the randomized energy value
** associated with the scavenged item. A new item is instantiated and added to the items vector
** to add it to the backpack.
***********************************************************************************************/
void Pack::addItem(const std::string &nameIn, const int &valueIn) {

  Item newItem(nameIn, valueIn);

  items.push_back(newItem);

}


/***********************************************************************************************
** Description: Returns the size of the items vector as an integer.
***********************************************************************************************/
int Pack::getItemCount() {
  return items.size();
}


/***********************************************************************************************
** Description: Takes a constant reference to an integer for an index in the vector of items,
** then returns the value of the item at that location. This is used to restore the player's
** energy by that amount when they choose to use that item.
***********************************************************************************************/
int Pack::getItemValue(const int &index) {

  return items.at(index).getValue();

}


/***********************************************************************************************
** Description: Loops through the items vector, printing each item in a menu format for the user
** to select which item they'd like to use.
***********************************************************************************************/
void Pack::printItems() {

  for ( unsigned int i = 0; i < items.size(); i++ ) {
    cout << i + 1 << ") " << items.at(i).getName() << endl;
  }

}


/***********************************************************************************************
** Description: Takes a constant reference to an integer for an index in the vector of items,
** then calls the erase function to remove the item at that location.
***********************************************************************************************/
void Pack::removeItem(const int &index) {
  items.erase(items.begin() + index);
}


/***********************************************************************************************
** Description: Checks the size of the items vector, and returns true if the vector's size is
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
** Description: Checks the size of the items vector, and returns true if the vector's size is
** less than the backpack's itemLimit value. Otherwise, it returns false to indicate that more
** items cannot be added to the backpack.
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
