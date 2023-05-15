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
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate

    // Default Constructor
    Shop();
    
    // Parameterized Constructor
    Shop(Menu m, string phone, string address, float revenue, int num_orders);
    
    // Copy Constructor
    Shop(const Shop& old);
    
    // Assignment Operator
    Shop& operator=(const Shop& old);
    
    // Destructor
    ~Shop();
    
    // Accessors
    Menu get_menu() const;
    string get_phone() const;
    string get_address() const;
    float get_revenue() const;
    Order* get_order_arr() const;
    int get_num_orders() const;
    
    // Mutators
    void set_menu(const Menu& m);
    void set_phone(const string& phone);
    void set_address(const string& address);
    void set_revenue(float revenue);
    void set_order_arr(const Order* order_arr);
    void set_num_orders(int num_orders);
    
    //Suggested functions
    void load_data(); //reads from files to correctly populate coffee, menu, etc.
    void load_menu_data();
    void load_orders_data();
    void load_shopInfo_data();

    void view_shop_detail();
    void search_by_price();
    void search_by_name();

    void place_order_from_search(string coffee_name);
    void place_order();

    void view_best_seller();
    void view_top_3_popular_drinks();


    void add_to_menu();
    void remove_from_menu();
    
    void view_orders();

    void view_shop_revenue();
    float get_order_price(Order& order);

    void display_employee_menu();
    void display_customer_menu();

    void load_initial_menu();
};

#endif
