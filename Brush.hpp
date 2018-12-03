/*********************************************************************
** Description: Specification file for the Brush class.
*********************************************************************/

#ifndef BRUSH_HPP
#define BRUSH_HPP

#include "Space.hpp"

class Brush : public Space {

  public:
    Brush();
    void scavenge() override;
    void scout() override;

  private:

};

#endif
