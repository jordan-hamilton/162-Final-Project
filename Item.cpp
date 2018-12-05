#include "Item.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Item::Item() {
  name = "";
  value = -1;
}


/***********************************************************************************************
** Description: Overloaded constructor that takes a constant reference to a string for the name,
** and a constant reference to an integer for the energy value of the item.
***********************************************************************************************/
Item::Item(const std::string &nameIn, const int &valueIn) {
  name = nameIn;
  value = valueIn;
}


/***********************************************************************************************
** Description: Returns a string for the name data member to display the name of an item in the
** player's backpack.
***********************************************************************************************/
std::string Item::getName() {
  return name;
}


/***********************************************************************************************
** Description: Returns an integer for the energy value of an item.
***********************************************************************************************/
int Item::getValue() {
  return value;
}


/***********************************************************************************************
** Description: Takes a constant reference to a string to set the name data member for an item.
***********************************************************************************************/
void Item::setName(const std::string &nameIn) {
  name = nameIn;
}


/***********************************************************************************************
** Description: Takes a constant reference to an integer to set the energy value of an item.
***********************************************************************************************/
void Item::setValue(const int &valueIn) {
  value = valueIn;
}
