/*********************************************************************
** Description: Specification file for the Clearing class.
*********************************************************************/

#ifndef CLEARING_HPP
#define CLEARING_HPP

#include "Space.hpp"

class Clearing : public Space {

  public:
    Clearing();
    void search() override;

  private:

};

#endif
