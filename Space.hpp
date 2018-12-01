/*********************************************************************
** Description: Specification file for the Space class.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <memory>

class Space {

  public:
    Space();
    virtual ~Space();

  private:

  protected:
    std::shared_ptr<Space> top, right, left, bottom;

};

#endif
