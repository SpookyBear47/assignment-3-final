#include "menu.h"

// Default Constructor
Menu::Menu(){
    this -> num_coffee = 0;
    this -> coffee_arr = NULL;
}

// Non-default Constructor
Menu::Menu(int num_coffee){
    this -> num_coffee = num_coffee;
    this -> coffee_arr = new Coffee[this->num_coffee];
}

// CC
Menu::Menu(const Menu& old){
    this->num_coffee = old.num_coffee;

    //deep copy
    this->coffee_arr = new Coffee[this->num_coffee];
    for(int i = 0; i < this->num_coffee; ++i){
        this->coffee_arr[i] = old.coffee_arr[i];
    }
}

// AAO
Menu& Menu::operator=(const Menu& old){
    this->num_coffee = old.num_coffee;
    
    //deep copy
    if(this->coffee_arr != NULL){
        delete[] this->coffee_arr;
    }
    this->coffee_arr = new Coffee [this->num_coffee];
    for(int i = 0; i < this->num_coffee; i++){
        this->coffee_arr[i] = old.coffee_arr[i];
    }
    return *this;
}

// Destructor
Menu::~Menu(){
    if(this->coffee_arr != NULL){
        delete[] this->coffee_arr;
        this->coffee_arr=NULL;
    }
}

// getters
int Menu::get_num_coffee() const {
    return this->num_coffee;
}
Coffee* Menu::get_coffee_arr() const {
    return this->coffee_arr;
}

// setters
void Menu::set_num_coffee(int num_coffee){
    this->num_coffee = num_coffee;
}
void Menu::set_coffee_arr(Coffee* coffee_arr){
    this->coffee_arr = coffee_arr;
}


// Suggested functions:
const Coffee Menu::search_coffee_by_name(string name){
    cout << "Enter the coffee's name you're searching for:" << endl;
    cin >> name;
    while (name.empty() || cin.fail()) {
        cout << "Invalid input. Please enter a valid name:" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cin >> name;
    }
    
    for (int i = 0; i < num_coffee; i++) {
        if (coffee_arr[i].get_name() == name) {
            return coffee_arr[i];
        }
    }
    // if no coffee with the given name is found, return an empty coffee object
    return Coffee();
}

// Menu Menu::search_coffee_by_price(int upper_bound) {
//     // Create a new menu to hold coffees within the price range
//     Menu new_menu;
    
//     // Loop through each coffee in the current menu
//     for (int i = 0; i < this->num_coffee; i++) {
//         Coffee current_coffee = this->coffee_arr[i];
        
//         // If the current coffee's price is within the specified range, add it to the new menu
//         if (current_coffee.get_small_cost() <= upper_bound || current_coffee.get_medium_cost() <= upper_bound || current_coffee.get_large_cost() <= upper_bound) {
//             new_menu.add_to_menu(current_coffee);
//         }
//     }
    
//     // Return the new menu containing only coffees within the specified price range
//     return new_menu;
// }



void Menu::add_to_menu(Coffee& coffee_to_add) {
    // create a new array with size num_coffee + 1
    Coffee* new_arr = new Coffee[num_coffee + 1];
    
    // copy the old array to the new array
    for (int i = 0; i < num_coffee; i++) {
        new_arr[i] = coffee_arr[i];
    }
    
    // add the new coffee object to the end of the new array
    new_arr[num_coffee] = coffee_to_add;
    
    // delete the old array
    delete[] coffee_arr;
    
    // update the coffee array pointer and number of coffee
    coffee_arr = new_arr;
    num_coffee++;
}

void Menu::remove_from_menu(int index_of_coffee_on_menu){
    if(index_of_coffee_on_menu < 0 || index_of_coffee_on_menu >= this->num_coffee) {
        cout << "Invalid index. Please enter a valid index between 0 and " << this->num_coffee-1 << "." << endl;
        return;
    }

    Coffee* new_coffee_arr = new Coffee[this->num_coffee-1];
    int new_index = 0;
    for(int i = 0; i < this->num_coffee; i++){
        if(i != index_of_coffee_on_menu){
            new_coffee_arr[new_index] = this->coffee_arr[i];
            new_index++;
        }
    }

    delete[] this->coffee_arr;
    this->coffee_arr = new_coffee_arr;
    this->num_coffee--;
}


// feel free to add more member functions

void Menu::display_menu(){
    cout << endl << "~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " --- Menu Items --- " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    for(int i = 0; i < this->num_coffee; i++){
        cout << " -- Menu Item #" << i+1 << " -- " << endl;
        cout << endl << "  Name:  " << endl << "    " << this->coffee_arr[i].get_name() << endl << endl;
        cout << "  Pricing Options:  " << endl;
        cout << "    Small Size  - $" << this->coffee_arr[i].get_small_cost() << endl;
        cout << "    Medium Size - $" << this->coffee_arr[i].get_medium_cost() << endl;
        cout << "    Large Size  - $" << this->coffee_arr[i].get_large_cost() << endl;
        if(i+1 != this->num_coffee){
            cout << endl << endl;
        }
    }
}

const Coffee& Menu::get_menu_item(int menuItemIndex){
    return coffee_arr[menuItemIndex];
}

const Coffee* Menu::find_coffee_by_name(string name) {
    for (int i = 0; i < num_coffee; i++) {
        if (coffee_arr[i].get_name() == name) {
            return &coffee_arr[i];
        }
    }
    return NULL; // if no matching coffee is found
}