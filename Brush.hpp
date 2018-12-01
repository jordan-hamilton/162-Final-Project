/*********************************************************************
** Description: Specification file for the Brush class.
*********************************************************************/

#ifndef BRUSH_HPP
#define BRUSH_HPP

#include "Space.hpp"

class Brush : public Space {

  public:
    Brush();
    void search() override;

  private:

};

#endif
