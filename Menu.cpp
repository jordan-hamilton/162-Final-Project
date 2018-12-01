#include "Menu.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;


/***********************************************************************************************
** Description: Default constructor that initializes data members.
***********************************************************************************************/
Menu::Menu() {
  menuPrompt = "";
  lastEnteredString = "";
  intArray = nullptr;
}


/***********************************************************************************************
** Description: Overloaded constructor that takes a string to initialize the menu's prompt.
***********************************************************************************************/
Menu::Menu(const std::string &prompt) {
  menuPrompt = prompt;
  lastEnteredString = "";
  intArray = nullptr;
}


/***********************************************************************************************
** Description: Destructor that frees memory dynamically allocated for the menu's intArray.
***********************************************************************************************/
Menu::~Menu() {

  if (intArray) {
    delete [] intArray;
    intArray = nullptr;
  }

}


/***********************************************************************************************
** Description: Prints a list of all options in the options vector for the user to select an
** option from the menu.
***********************************************************************************************/
void Menu::displayMenu() {
  for (unsigned int i = 0; i < options.size(); i++) {
    cout << i + 1 << ") " << options.at(i) << endl;
  }
}


void Menu::addMenuItem(const string &menuItem) {
  options.push_back(menuItem);
}


/***********************************************************************************************
** Description: Takes a reference to a string used to indicate a prompt for the user to enter
** data, followed by references to integers that output valid values to hint that the user
** should enter an integer value within the entered values. Input is passed to validateInput and
** validateRange to verify that the input is an integer and falls within a valid range for the
** prompt, then the integer value the user entered is returned if it was valid. Otherwise, the
** prompt is repeated. A boolean is passed to specify whether the entire menu should be
** displayed along with the prompt for a selection.
***********************************************************************************************/
int Menu::getIntFromPrompt(const string &prompt, const int &minVal, const int &maxVal, const bool &displayTheMenu) {

  string userInput;

  do {

    cout << prompt << endl;

    if (displayTheMenu) {
      displayMenu();
    }

    cout << "Valid input range: [" << minVal << " - " << maxVal << "]: ";
    getline(cin, userInput);

  } while( !validateInput(userInput) || !validateRange( stoi(userInput), minVal, maxVal ) );

return stoi(userInput);

}


/***********************************************************************************************
** Description: Takes references to integers that output valid values to hint that the user
** should enter an integer value within the entered values. Input is passed to validateInput and
** validateRange to verify that the input is an integer and falls within a valid range for the
** prompt, then the integer value the user entered is returned if it was valid. Otherwise, the
** prompt is repeated. A boolean is passed to specify whether the entire menu should be
** displayed along with the prompt for a selection. If the menu was initialized with a prompt,
** this is displayed prior to accepting user input.
***********************************************************************************************/
int Menu::getIntFromPrompt(const int &minVal, const int &maxVal, const bool &displayTheMenu) {

  string userInput;

  do {

    if (!menuPrompt.empty()) {
      cout << menuPrompt << endl;
    }

    if (displayTheMenu) {
      displayMenu();
    }

    cout << "Valid input range: [" << minVal << " - " << maxVal << "] ";
    getline(cin, userInput);

  } while( !validateInput(userInput) || !validateRange( stoi(userInput), minVal, maxVal ) );

return stoi(userInput);

}


/***********************************************************************************************
** Description: Takes references to a string to display to the user before accepting input, and
** a reference to a boolean to output possible menu choices if set to true. User input is then
** stored in the lastEnteredString data member and returned.
***********************************************************************************************/
std::string Menu::getStrFromPrompt(const std::string &prompt, const bool &displayTheMenu) {

  cout << prompt << endl;

  if (displayTheMenu) {
    displayMenu();
  }

  getline(cin, lastEnteredString);

  return getEnteredString();

}


/***********************************************************************************************
** Description: Takes a reference to a boolean to output possible menu choices if set to true.
** If the menu was initialized with a prompt, this is displayed prior to accepting user input.
** User input is then stored in the lastEnteredString data member and returned.
***********************************************************************************************/
std::string Menu::getStrFromPrompt(const bool &displayTheMenu) {

  if (!menuPrompt.empty()) {
    cout << menuPrompt << endl;
  }

  if (displayTheMenu) {
    displayMenu();
  }

  getline(cin, lastEnteredString);

  return getEnteredString();

}


/*********************************************************************
** Description: Dynamically allocates memory for an array of integers,
** then sets the intArraySize variable to the passed integer so the
** size of the array can be tracked.
*********************************************************************/
void Menu::makeIntArray(int arraySize) {
  intArray = new int[arraySize];
  setIntArraySize(arraySize);
}


/*********************************************************************
** Description: Prompts the user to enter integer values for each
** element in the array and performs validation to ensure an integer.
** was entered.
*********************************************************************/
void Menu::populateIntArray() {
  for (int i = 0; i < getIntArraySize(); i++) {
    intArray[i] = getIntFromPrompt("Enter an integer", -100000, 100000, false);
  }

}


/*********************************************************************
** Description: Returns a pointer to the intArray.
*********************************************************************/
int* Menu::getIntArray() {
      return intArray;
}


/*********************************************************************
** Description: Returns an integer representing the size of the
** integer array.
*********************************************************************/
int Menu::getIntArraySize() {
  return intArraySize;
}


/*********************************************************************
** Description: Takes an integer to set the intArraySize data member.
*********************************************************************/
void Menu::setIntArraySize(int arraySize) {
  intArraySize = arraySize;
}


/*********************************************************************
** Description: Returns the size of the options vector.
** Used with the getIntFromPrompt method to determine the
** maximum valid selection for a menu item.
*********************************************************************/
int Menu::getMenuChoices() {
      return options.size();
}


/*********************************************************************
** Description: Returns the last string entered by the user that was
** stored in the lastEnteredString data member.
*********************************************************************/
string Menu::getEnteredString() {
      return lastEnteredString;
}


/*********************************************************************
** Description: Takes a constant reference to a string, then sets
** the data member lastEnteredString to the provided value.
*********************************************************************/
void Menu::setEnteredString(const std::string &inputStr) {
  lastEnteredString = inputStr;
}


/*********************************************************************
** Description: This method accepts a reference to a string, which
** is then looped through to search for non-digit characters. The
** return value is true if there are only digits or a minus sign at
** the first index in the string passed to the method, otherwise,
** the method returns false.
*********************************************************************/
bool Menu::validateInput(const string &inputStr) {
  bool isValid = true;

  if (inputStr.empty()) {
    isValid = false;
  }

  for (unsigned int i = 0; i < inputStr.length(); i++) {

    if (!isdigit(inputStr[i])) {

      if (i != 0 || inputStr[i] != '-') {
        isValid = false;
      }

    }

  }

  return isValid;

}


/***********************************************************************************************
** Description: Takes a reference to an integer value to check, and minimum and maximum values.
** If the input is an integer and in the valid range, the method returns true. Otherwise,
** it returns false.
***********************************************************************************************/
bool Menu::validateRange(const int &inputVal, const int &minVal, const int &maxVal) {

  if ((inputVal >= minVal) && (inputVal <= maxVal)) {
    return true;
  } else {
    return false;
  }
}
