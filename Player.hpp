/*********************************************************************
** Description: Specification file for the Player class.
*********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stack>

#include "Pack.hpp"

class Player {

  public:
    Player();
    ~Player();
    bool hasEnergy();
    int getEnergy();
    int getRow();
    int getCol();
    void setEnergy(int energyLeft);
    void setRow(int rowIn);
    void setCol(int colIn);

  private:
    Pack* backpack;
    int energy;
    int row, col;

};

#endif
