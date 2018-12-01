/*********************************************************************
** Description: Specification file for the Player class.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

class Player {

  public:
    Player();
    ~Player();
    int getEnergy();
    void setEnergy(int energyLeft);

  private:
    int energy;

};

#endif
