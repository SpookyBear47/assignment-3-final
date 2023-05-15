#include "coffee.h"


// Default Constructor
Coffee::Coffee(){
    this->name = "N/A";
    this->small_cost = 1.00;
    this->medium_cost = 2.00;
    this->large_cost = 3.00;
}

// Non-Default Constructor
Coffee::Coffee(string name, float small_cost, float medium_cost, float large_cost){
    this->name = name;
    this->small_cost = small_cost;
    this->medium_cost = medium_cost;
    this->large_cost = large_cost;
}

// AAO
Coffee& Coffee::operator=(const Coffee& old){
    this->name = old.name;
    this->small_cost = old.small_cost;
    this->medium_cost = old.medium_cost;
    this->large_cost = old.large_cost;

    return *this;
}

// CC
Coffee::Coffee(const Coffee& old){
    this->name = old.name;
    this->small_cost = old.small_cost;
    this->medium_cost = old.medium_cost;
    this->large_cost = old.large_cost;
}

// Destructor (Unneeded; no dynamic memory allocated)
// Coffee::~Coffee();


// getters
string Coffee::get_name() const {return this->name;}
float Coffee::get_small_cost() const {return this->small_cost;}
float Coffee::get_medium_cost() const {return this->medium_cost;}
float Coffee::get_large_cost() const {return this->large_cost;}

// setters
void Coffee::set_name(string name){this->name = name;}
void Coffee::set_small_cost(float small_cost){this->small_cost = small_cost;}
void Coffee::set_medium_cost(float medium_cost){this->medium_cost = medium_cost;}
void Coffee::set_large_cost(float large_cost){this->large_cost = large_cost;}
