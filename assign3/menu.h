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
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    //need to use 'const' when appropriate
    

//************************************************//
    // Default & Non-Default Constructor
    Menu();
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

    // Suggested functions:
    const Coffee search_coffee_by_name(string name); 
    // Menu search_coffee_by_price(int upper_bound); 
    void add_to_menu(Coffee& coffee_to_add); //add a coffee object into the Menu
    void remove_from_menu(int index_of_coffee_on_menu); //remove a coffee object from the Menu

    // feel free to add more member functions
    void display_menu();

    //const Coffee& get_menu_item();
    const Coffee& get_menu_item(int menuItemIndex);

    const Coffee* find_coffee_by_name(string name);

};

#endif