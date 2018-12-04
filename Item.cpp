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

std::string Item::getName() {
  return name;
}


int Item::getValue() {
  return value;
}


void Item::setName(std::string nameIn) {
  name = nameIn;
}


void Item::setValue(int valueIn) {
  value = valueIn;
}
