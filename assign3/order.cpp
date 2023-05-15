#include "order.h"

// Default Constructor
Order::Order(){
    this->id = 0;
    this->coffee_name = "N/A";
    this->coffee_size = 'x';
    this->quantity = 0;
}

// Non-Default Constructor
Order::Order(int id, string coffee_name, char coffee_size, int quantity){
    this->id = id;
    this->coffee_name = coffee_name;
    this->coffee_size = coffee_size;
    this->quantity = quantity;
}

// AAO
Order& Order::operator=(const Order& old){
    this->id = old.id;
    this->coffee_name = old.coffee_name;
    this->coffee_size = old.coffee_size;
    this->quantity = old.quantity;
    return *this;
}

// CC
Order::Order(const Order& old){
    this->id = old.id;
    this->coffee_name = old.coffee_name;
    this->coffee_size = old.coffee_size;
    this->quantity = old.quantity;
}

// // Destructor
// Order::~Order(){

// }


// getters
int Order::get_id() const {return this->id;}
string Order::get_coffee_name() const {return this->coffee_name;}
char Order::get_coffee_size() const {return this->coffee_size;}
int Order::get_quantity() const {return this->quantity;}

//setters
void Order::set_id(int id){this->id = id;}
void Order::set_coffee_name(string coffee_name){this->coffee_name = coffee_name;}
void Order::set_coffee_size(char coffee_size){this->coffee_size = coffee_size;}
void Order::set_quantity(int quantity){this->quantity = quantity;}


void Order::print_order() {
    cout << "Order #" << id << endl;
    cout << quantity << " ";
    switch (coffee_size) {
        case 'S':
            cout << "Small ";
            break;
        case 'M':
            cout << "Medium ";
            break;
        case 'L':
            cout << "Large ";
            break;
        default:
            cerr << "Error: Invalid coffee size" << endl;
            return;
    }
    cout << coffee_name << endl;
    cout << endl;
}


