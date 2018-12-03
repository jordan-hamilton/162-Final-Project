#include "Player.hpp"

/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Player::Player() {
  backpack = nullptr;
  energy = 100;
}


Player::~Player() {

  if (backpack) {
    delete backpack;
    backpack = nullptr;
  }

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


/***********************************************************************************************
** Description: This method takes an integer representing the energy cost of a space the player
** just moved to, then decreases the player's energy by that amount.
***********************************************************************************************/
void Player::drainEnergy(const int &energyDrained) {
  energy -= energyDrained;
}


Pack* Player::getBackpack() {
  return backpack;
}


int Player::getEnergy() {
  return energy;
}


void Player::setEnergy(const int &energyLeft) {
  energy = energyLeft;
}
