#ifndef MENU_H
#define MENU_H 

#include <string>
#include <iostream>
#include <limits>
#include <fstream>
#include "coffee.h"

using namespace std;

class Menu {
  private:
    int num_coffee;
    Coffee* coffee_arr;
  public:
//************************************************//
    // Default Constructor
    Menu();

    // Non-Default Constructor
    Menu(int num_coffee);

    // CC
    Menu(const Menu& old);

    // AAO
    Menu& operator=(const Menu& old);

    // Destructor
    ~Menu();


    // getters
    int get_num_coffee() const;
    Coffee* get_coffee_arr() const;

    // setters
    void set_num_coffee(int num_coffee);
    void set_coffee_arr(Coffee* coffee_arr);
//************************************************//

/*********************************************************************
** Function: search_coffee_by_name(string name)
** Description: takes a string and searches for a coffee object by name
** Parameters: needs a name to search for
** Pre-Conditions: must have a populated array to search from
** Post-Conditions: returns the Coffee object that the user was querying for (if it exists)
*********************************************************************/
    const Coffee search_coffee_by_name(string name);

/*********************************************************************
** Function: add_to_menu(Coffee& coffee_to_add)
** Description: adds a coffee object into the Menu coffee object array
** Parameters: needs a reference to the Coffee object you're going to add
** Pre-Conditions: Must have a coffee object to add + a coffee array to add to
** Post-Conditions: Adds a coffee object to the menu
*********************************************************************/
    void add_to_menu(Coffee& coffee_to_add);

/*********************************************************************
** Function: remove_from_menu(int index_of_coffee_on_menu)
** Description: removes a coffee object from the menu
** Parameters: must have the index of the coffee object you wish to remove
** Pre-Conditions: must have a coffee array to remove the object from and a valid index input
** Post-Conditions: will remove the coffee object from the coffee array in menu
*********************************************************************/
    void remove_from_menu(int index_of_coffee_on_menu); //remove a coffee object from the Menu

/*********************************************************************
** Function: display_menu()
** Description: displays the menu held in the Shop class
** Parameters: must have a valid menu to read from (when called to read from it via within the function)
** Pre-Conditions: must have all variables present that are called
** Post-Conditions: will display the menu items in accordance of their order of appearance in the menu
*********************************************************************/
    void display_menu();

/*********************************************************************
** Function: get_menu_item(int menuItemIndex)
** Description: will return the menu item at the given index
** Parameters: requires the index you wish to return the menu item of
** Pre-Conditions: needs a valid menu array to read from in order to properly function
** Post-Conditions: will return a reference to the menu item at menuItemIndex
*********************************************************************/
    const Coffee& get_menu_item(int menuItemIndex);

/*********************************************************************
** Function:find_coffee_by_name(string name)
** Description: will find a coffee by the name you pass into the function
** Parameters: needs a valid string name to search for
** Pre-Conditions: requires for there to be a valid array to query
** Post-Conditions: will return the Coffee you query for, given that it exists
*********************************************************************/
    const Coffee* find_coffee_by_name(string name);
};

#endif