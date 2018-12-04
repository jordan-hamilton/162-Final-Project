/*********************************************************************
** Description: Specification file for the Pack class.
*********************************************************************/

#ifndef PACK_HPP
#define PACK_HPP

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

  private:
    int itemLimit;
    std::vector<Item> items;
    int getItemLimit();
    void setItemLimit(int limit);

};

#endif
