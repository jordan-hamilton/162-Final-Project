/*********************************************************************
** Description: Specification file for the Player class.
*********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Pack.hpp"

class Player {

  public:
    Player();
    ~Player();
    bool hasEnergy();
    int getEnergy();
    void setEnergy(int energyLeft);

  private:
    Pack backpack;
    int energy;
    int xCoordinate, yCoordinate;

};

#endif
