/*********************************************************************
** Description: Specification file for the Space class.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <string>

class Space {

  public:
    Space();
    virtual ~Space();
    virtual void search() = 0;
    bool isPlayerHere();
    int getEnergyCost();
    std::string getType();
    Space* getNorth();
    Space* getEast();
    Space* getWest();
    Space* getSouth();
    void setPlayerHere(bool presence);
    void setEnergyCost(int cost);
    void setType(std::string terrainType);
    void setNorth(Space* northIn);
    void setEast(Space* eastIn);
    void setWest(Space* westIn);
    void setSouth(Space* southIn);

  private:


  protected:
    bool playerHere;
    int energyCost;
    std::string type;
    Space* north;
    Space* south;
    Space* east;
    Space* west;

};

#endif
