#include "Player.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Player::Player() {
  energy = 100;
}


Player::~Player() {
  
}


/***********************************************************************************************
** Description: Method that returns a boolean to indicate if the player still has energy to
** continue moving through the wilderness.
***********************************************************************************************/
bool Player::hasEnergy() {

  if (energy > 0) {
    return true;
  } else {
    return false;
  }

}


int Player::getEnergy() {
  return energy;
}


void Player::setEnergy(int energyLeft) {
  energy = energyLeft;
}
