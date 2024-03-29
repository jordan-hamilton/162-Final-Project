/*********************************************************************
** Description: Specification file for the Item class.
*********************************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {

  public:
    Item();
    Item(const std::string &nameIn, const int &valueIn);
    std::string getName();
    int getValue();

  private:
    void setName(const std::string &nameIn);
    void setValue(const int &valueIn);
    std::string name;
    int value;
};

#endif
