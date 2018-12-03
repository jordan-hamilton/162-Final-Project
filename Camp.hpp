/*********************************************************************
** Description: Specification file for the Camp class.
*********************************************************************/

#ifndef CAMP_HPP
#define CAMP_HPP

#include "Space.hpp"

class Camp : public Space {

  public:
    Camp();
    void scavenge() override;
    void scout() override;

  private:

};

#endif
