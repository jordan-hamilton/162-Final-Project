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
    virtual void search() = 0;
    int getEnergyCost();
    void setEnergyCost(int cost);

  private:
    int energyCost;

  protected:
    std::shared_ptr<Space> top, right, left, bottom;

};

#endif
