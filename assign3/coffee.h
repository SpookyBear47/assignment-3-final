#ifndef COFFEE_H
#define COFFEE_H

#include <string>
#include <fstream>

using namespace std;

class Coffee {
  private:
    string name;
    float small_cost;
    float medium_cost;
    float large_cost;
    
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate

    // Default Constructor
    Coffee();

    // Non-Default Constructor
    Coffee(string name, float small_cost, float medium_cost, float large_cost);

    // AAO
    Coffee& operator=(const Coffee& old);

    // CC
    Coffee(const Coffee& old);

    // Destructor (Unneeded; no dynamic memory allocated)
    // ~Coffee();

    
    // getters
    string get_name() const;
    float get_small_cost() const;
    float get_medium_cost() const;
    float get_large_cost() const;

    // setters
    void set_name(string name);
    void set_small_cost(float small_cost);
    void set_medium_cost(float medium_cost);
    void set_large_cost(float large_cost);

};

#endif