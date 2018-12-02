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
    bool isHikerHere();
    bool isPlayerHere();
    bool wasDiscovered();
    bool wasSearched();
    char getIcon();
    int getEnergyCost();
    std::string getType();
    Space* getNorth();
    Space* getEast();
    Space* getSouth();
    Space* getWest();
    void setHikerHere(bool presenceStatus);
    void setPlayerHere(bool presenceStatus);
    void setDiscovered(bool discoveryStatus);
    void setSearched(bool searchStatus);
    void setNorth(Space* northIn);
    void setEast(Space* eastIn);
    void setSouth(Space* southIn);
    void setWest(Space* westIn);

  private:


  protected:
    void setIcon(char iconIn);
    void setEnergyCost(int cost);
    void setType(std::string terrainType);
    bool hikerHere;
    bool playerHere;
    bool discovered;
    bool searched;
    char icon;
    int energyCost;
    std::string type;
    Space* north;
    Space* south;
    Space* east;
    Space* west;

};

#endif
