#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>
#include "menu.h"
#include "order.h"
#include "coffee.h"

using namespace std;

class Shop {
  private:
    Menu m;
    string phone;
    string address;
    float revenue;
    Order *order_arr;
    int num_orders;
  public:
  //************************************************//
    // Default Constructor
    Shop();
    
    // Non-Default Constructor
    Shop(Menu m, string phone, string address, float revenue, int num_orders);
    
    // CC
    Shop(const Shop& old);
    
    // AOO
    Shop& operator=(const Shop& old);
    
    // Destructor
    ~Shop();
    
    // getters
    Menu get_menu() const;
    string get_phone() const;
    string get_address() const;
    float get_revenue() const;
    Order* get_order_arr() const;
    int get_num_orders() const;
    
    // setters
    void set_menu(const Menu& m);
    void set_phone(const string& phone);
    void set_address(const string& address);
    void set_revenue(float revenue);
    void set_order_arr(const Order* order_arr);
    void set_num_orders(int num_orders);
    //************************************************//

/*********************************************************************
** Function: load_data()
** Description: Reads from the files given to correctly populate coffee, menu, phone, address, and all other relevant variables read from files
** Parameters: N/A
** Pre-Conditions: Must have files to read from
** Post-Conditions: Populates the Shop object's data where relevant
*********************************************************************/
    void load_data();

/*********************************************************************
** Function: load_menu_data()
** Description: a part of the "load_data()" function; used to specifically populate the menu's data
** Parameters: N/A
** Pre-Conditions: needs a proper "menu.txt" file in order to function
** Post-Conditions: properly populates all relevant menu information in the shop object
*********************************************************************/
    void load_menu_data();

/*********************************************************************
** Function: load_orders_data()
** Description: a part of the "load_data()" function; used to specifically populate the orders' data
** Parameters: N/A
** Pre-Conditions: must have a proper "orders.txt" file to read from in order to function
** Post-Conditions: properly populates all relevant order information in the shop object
*********************************************************************/
    void load_orders_data();

/*********************************************************************
** Function: load_shopInfo_data()
** Description: a part of the "load_data()" function; used to specifically populate the shopInfo data
** Parameters: N/A
** Pre-Conditions: requires a proper "shop_info.txt" file in order to function/run
** Post-Conditions: properly populates all relevant shopInfo data in the shop object
*********************************************************************/
    void load_shopInfo_data();

/*********************************************************************
** Function: view_shop_detail()
** Description: shows all menu information & shopInfo information
** Parameters: N/A
** Pre-Conditions: must have valid information to read from the menu & shopInfo regards of the shop object
** Post-Conditions: properly displays the output data for the shop's menu & shopInfo information
*********************************************************************/
    void view_shop_detail();

/*********************************************************************
** Function: search_by_price()
** Description: searches the shop's menu for coffee items by price
** Parameters: N/A
** Pre-Conditions: must have a valid array of menu items to query from
** Post-Conditions: returns results that satisfy the user's respective queries
*********************************************************************/
    void search_by_price();

/*********************************************************************
** Function: search_by_name()
** Description: searches the shop's menu for coffee items by name
** Parameters: N/A
** Pre-Conditions: must have a valid menu array to query from
** Post-Conditions: will return results that satisfy the user's queries
*********************************************************************/
    void search_by_name();

/*********************************************************************
** Function: place_order_from_search(string coffee_name)
** Description: used in conjunction with the search functions to place an order after a search is made
** Parameters: takes a string "coffee_name" to start off the order (assumes that the user wishes to order an item with that name)
** Pre-Conditions: must have the user query for their result & decide to order beforehand; doesn't work as a standalone order
** Post-Conditions: will place an order based upon the user's query + additional input thereafter to specify the details
*********************************************************************/
    void place_order_from_search(string coffee_name);

/*********************************************************************
** Function: place_order()
** Description: places an order based upon the user's input
** Parameters: N/A
** Pre-Conditions: must have a valid orders array to append to + valid input from the user
** Post-Conditions: appends an order to the orders array & order.txt file
*********************************************************************/
    void place_order();

/*********************************************************************
** Function: view_best_seller()
** Description: shows the most-ordered item (quantity wise) from the orders array & .txt file
** Parameters: N/A
** Pre-Conditions: must have a valid/populated orders.txt file & orders array to read from
** Post-Conditions: returns the most ordered order & shows it to the user
*********************************************************************/
    void view_best_seller();

/*********************************************************************
** Function: view_top_3_popular_drinks()
** Description: returns the most ordered small, medium, and large sized drinks (respectively)
** Parameters: N/A
** Pre-Conditions: Must have a valid orders array & .txt file to read from; must also have a small/medium/large drink(s) to compare against one another/to display in the results menu (otherwise, returns "N/A" for the most ordered drink of its size (if there's none of its size that've been ordered otherwise))
** Post-Conditions: Returns the top ordered small, medium, and large drinks for the user to view
*********************************************************************/
    void view_top_3_popular_drinks();

/*********************************************************************
** Function: add_to_menu()
** Description: addsd a drink to the menu contained in the shop object
** Parameters: N/A
** Pre-Conditions: Must have a valid menu array to populate
** Post-Conditions: adds a drink to the shop's menu (determinant upon the user's respective input)
*********************************************************************/
    void add_to_menu();

/*********************************************************************
** Function: remove_from_menu()
** Description: removes a drink from the menu contained within the shop object
** Parameters: N/A
** Pre-Conditions: Must have a valid menu array to remove from & the query must be a valid index of the array being removed from
** Post-Conditions: Removes the menu item that the user decides to remove from the menu array contained within the shop object
*********************************************************************/
    void remove_from_menu();
    
/*********************************************************************
** Function: view_orders()
** Description: views all of the current orders that've been made with the shop
** Parameters: N/A
** Pre-Conditions: must have a valid orders.txt file to read from, & a populated file to read from as well
** Post-Conditions: returns the total amount of orders, or none if no orders have been made yet
*********************************************************************/
    void view_orders();

/*********************************************************************
** Function: view_shop_revenue()
** Description: displays the total revenue the shop currently has generated (based upon the orders listed in the orders.txt file)
** Parameters: N/A
** Pre-Conditions: must have a valid & populated orders.txt file to read from
** Post-Conditions: outputs the total sum of revenue generated by the shop based upon the orders made to it (via indicated in the orders.txt file)
*********************************************************************/
    void view_shop_revenue();

/*********************************************************************
** Function: get_order_price(Order& order)
** Description: gets the price of a specific order via querying the menu & finding the order price & multiplying it by the order's size; then returns the price as a float
** Parameters: Order& order
** Pre-Conditions: must have a valid menu array to query from & a valid order name to search with (in order to return relevant results)
** Post-Conditions: returns the price of an order via utilizing menu queries & multiplying them by the size of the order; returns it all as a float to the user afterward
*********************************************************************/
    float get_order_price(Order& order);

/*********************************************************************
** Function: display_employee_menu()
** Description: displays the base menu for the "employee" user type; shows all options for them to pick from, as well as an option to quit back to the user selection screen
** Parameters: N/A
** Pre-Conditions: shop must have been successfully populated with each of the .txt files before this will be allowed to load; in addition, it must be queried for via the "Employee" user option that the user can pick in the main menu
** Post-Conditions: Shows the user relevant operations that the employee can do with the shop
*********************************************************************/
    void display_employee_menu();

/*********************************************************************
** Function: display_customer_menu()
** Description: displays the base menu for the "customer" user type; shows all options for them to pick from, as well as an option to quit back to the user selection screen
** Parameters: N/A
** Pre-Conditions: shop must have been successfully populated with each of the .txt files before this will be allowed to load; in addition, it must be queried for via the "Customer" user option that the user can pick in the main menu
** Post-Conditions: Shows the user relevant operations that the customer can do with the shop
*********************************************************************/
    void display_customer_menu();

/*********************************************************************
** Function: load_initial_menu()
** Description: loads the initial "user selection screen" menu for the user for the program
** Parameters: N/A
** Pre-Conditions: shop must have been successfully populated with each of the .txt files before this will be allowed to load
** Post-Conditions: displays the user-type options for the user, as well as an option to quit the program
*********************************************************************/
    void load_initial_menu();
};

#endif
