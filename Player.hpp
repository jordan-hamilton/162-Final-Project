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
    Pack* getBackpack();
    int getEnergy();
    void drainEnergy(const int &energyDrained);
    void restoreEnergy(const int &energyRestored);
    void setEnergy(const int &energyLeft);

  private:
    Pack* backpack;
    int energy;

};

#endif
