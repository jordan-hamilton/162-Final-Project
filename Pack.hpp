/*********************************************************************
** Description: Specification file for the Pack class.
*********************************************************************/

#ifndef PACK_HPP
#define PACK_HPP

#include <iostream>
#include <vector>
#include <string>

#include "Item.hpp"

class Pack {

  public:
    Pack();
    ~Pack();
    void addItem(const std::string &nameIn, const int &valueIn);
    bool hasItems();
    bool hasRoom();
    int getItemCount();
    int getItemLimit();
    int getItemValue(const int &index);
    void printItems();
    void removeItem(const int &index);

  private:
    unsigned int itemLimit;
    std::vector<Item> items;

    void setItemLimit(int limit);

};

#endif
