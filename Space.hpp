/*********************************************************************
** Description: Specification file for the Space class.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <memory>
#include <string>

class Space {

  public:
    Space();
    virtual ~Space();
    virtual void search() = 0;
    int getEnergyCost();
    std::string getType();
    void setEnergyCost(int cost);
    void setType(std::string terrainType);

  private:


  protected:
    int energyCost;
    std::string type;
    std::shared_ptr<Space> top, right, left, bottom;

};

#endif
