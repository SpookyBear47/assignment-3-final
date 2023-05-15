#ifndef ORDER_H
#define ORDER_H 

#include <string>
#include <iostream>

using namespace std;

class Order
{
private:
	int id;
	string coffee_name;
	char coffee_size;
	int quantity;

public:
	//need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate
	
	// Default Constructor
	Order();

	// Non-Default Constructor
	Order(int id, string coffee_name, char coffee_size, int quantity);

	// AAO
	Order& operator=(const Order& old);	

	// CC
	Order(const Order& old);

	// Destructor
	//~Order();


	// getters
	int get_id() const;
	string get_coffee_name() const;
	char get_coffee_size() const;
	int get_quantity() const;

	//setters
	void set_id(int id);
	void set_coffee_name(string coffee_name);
	void set_coffee_size(char coffee_size);
	void set_quantity(int quantity);

	// print order
	void print_order();

	
};
#endif