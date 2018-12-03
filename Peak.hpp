/*********************************************************************
** Description: Specification file for the Peak class.
*********************************************************************/

#ifndef PEAK_HPP
#define PEAK_HPP

#include "Space.hpp"

class Peak : public Space {

  public:
    Peak();
    void scavenge() override;
    void scout() override;

  private:

};

#endif
