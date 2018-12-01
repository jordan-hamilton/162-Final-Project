/*********************************************************************
** Description: Specification file for the Pack class.
*********************************************************************/

#ifndef PACK_HPP
#define PACK_HPP

#include <iostream>

class Pack {

  public:
    Pack();
    ~Pack();
    void listItems();
    int getItemLimit();
    void setItemLimit(int limit);

  private:
    int itemLimit;

};

#endif
