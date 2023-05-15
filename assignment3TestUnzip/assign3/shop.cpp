#include "shop.h"

//need to include accessor functions and mutator functions for private member when appropriate
//need to include constructors and destructors where appropriate
//need to use 'const' when appropriate

// Default Constructor
Shop::Shop() : m(Menu()), phone(""), address(""), revenue(0.0), order_arr(NULL), num_orders(0) {}

// Non-Default Constructor
Shop::Shop(Menu m, string phone, string address, float revenue, int num_orders) : m(m), phone(phone), address(address), revenue(revenue), num_orders(num_orders) {
    if(num_orders > 0) {
        this->order_arr = new Order[num_orders];
        for(int i = 0; i < num_orders; i++) {
            this->order_arr[i] = Order();
        }
    }
}

// Copy Constructor
Shop::Shop(const Shop& old) : m(old.m), phone(old.phone), address(old.address), revenue(old.revenue), num_orders(old.num_orders) {
    if (old.order_arr != NULL) {
        this->order_arr = new Order[old.num_orders];
        for (int i = 0; i < old.num_orders; i++) {
            this->order_arr[i] = old.order_arr[i];
        }
    } else {
        this->order_arr = NULL;
    }
}

// Assignment Operator
Shop& Shop::operator=(const Shop& old) {
    if (this != &old) {
        this->m = old.m;
        this->phone = old.phone;
        this->address = old.address;
        this->revenue = old.revenue;
        this->num_orders = old.num_orders;

        if (old.order_arr != NULL) {
            Order* new_order_arr = new Order[old.num_orders];
            for (int i = 0; i < old.num_orders; i++) {
                new_order_arr[i] = old.order_arr[i];
            }
            delete[] this->order_arr;
            this->order_arr = new_order_arr;
        } else {
            delete[] this->order_arr;
            this->order_arr = NULL;
        }
    }
    return *this;
}


Shop::~Shop() {
    // free memory for the order array
    delete[] order_arr;
}


// Accessors
Menu Shop::get_menu() const {return m;}
string Shop::get_phone() const {return phone;}
string Shop::get_address() const {return address;}
float Shop::get_revenue() const {return revenue;}
Order* Shop::get_order_arr() const {return order_arr;}
int Shop::get_num_orders() const {return num_orders;}

// Mutators
void Shop::set_menu(const Menu& m) {this->m = m;}
void Shop::set_phone(const string& phone) {this->phone = phone;}
void Shop::set_address(const string& address) {this->address = address;}
void Shop::set_revenue(float revenue) {this->revenue = revenue;}

void Shop::set_order_arr(const Order* order_arr) {
    if(num_orders > 0) {
        delete[] this->order_arr;
        this->order_arr = new Order[num_orders];
        for(int i = 0; i < num_orders; i++) {
            this->order_arr[i] = order_arr[i];
        }
    }
}

void Shop::set_num_orders(int num_orders) {
    if(num_orders > 0) {
        if(this->num_orders > 0) {
            delete[] this->order_arr;
        }
        this->order_arr = new Order[num_orders];
        this->num_orders = num_orders;
    }
}


//Suggested functions

// req for load_data
void Shop::load_menu_data(){
    // Read menu data from file
    // error checking
    ifstream menu_file("menu.txt");
    if (!menu_file) {
        cerr << "Error opening menu.txt" << endl;
        std::exit(1);
    }
    // temp var creation
    Menu m;
    int number_of_items;
    string menu_item_name;
    float small_cost, medium_cost, large_cost;

    menu_file >> number_of_items;

    // need to have this loop through for the number of times listed at the start of the file
    for(int i = 0; i < number_of_items; i++){
        menu_file >> menu_item_name >> small_cost >> medium_cost >> large_cost;
        Coffee item(menu_item_name, small_cost, medium_cost, large_cost);
        m.add_to_menu(item);
    }
    
    Shop::set_menu(m);

    menu_file.close();
}

// req for load_data
void Shop::load_orders_data(){
    // Read orders data from file
    // error checking
    ifstream orders_file("orders.txt");
    if (!orders_file) {
        cerr << "Error opening orders.txt" << endl;
        std::exit(1);
    }
    //temp var creation
    int number_of_items;
    int id;
    string coffee_name;
    char coffee_size;
    int quantity;

    orders_file >> number_of_items;
    Shop::set_num_orders(number_of_items);

    // loops through the number of times listed at the start of the file
    Order* tempOrderArray = new Order[number_of_items];

    for(int i = 0; i < number_of_items; i++){
        orders_file >> id >> coffee_name >> coffee_size >> quantity;
        Order item(id, coffee_name, coffee_size, quantity);
        tempOrderArray[i] = item; // need to add to shop's orders_arr
    }
    set_order_arr(tempOrderArray);

    orders_file.close();
}

// req for load_data
void Shop::load_shopInfo_data(){
    // Read shop data from file
    ifstream shop_file("shop_info.txt");
    if (!shop_file) {
        cerr << "Error opening shop_info.txt" << endl;
        std::exit(1);
    }

    string phone, address;
    getline(shop_file, phone); // read the first line into the phone variable
    getline(shop_file, address); // read the entire second line into the address variable

    Shop::set_phone(phone);
    Shop::set_address(address);

    shop_file.close();
}

// dependent on load_menu_data, load_orders_data, & load_shopInfo_data
void Shop::load_data() {
    load_menu_data();
    load_orders_data();
    load_shopInfo_data();
}

void Shop::view_shop_detail() {
    m.display_menu();
    cout << endl << endl << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " --- Contact Info --- " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    cout << "Phone: " << Shop::get_phone() << endl;
    cout << "Address: " << Shop::get_address() << endl << endl;
}

// utilizes get_order_price for most function
void Shop::view_shop_revenue(){
    float shopRevenue = 0.0;
    Order* orderArr = get_order_arr();

    for(int i = 0; i < Shop::get_num_orders(); i++){ 
        shopRevenue += Shop::get_order_price(orderArr[i]);
    }
    cout << endl << endl << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "    Revenue: $" << shopRevenue << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
}

// crucial for view_shop_revenue ^
float Shop::get_order_price(Order& order){
    Coffee coffeeOrder = Coffee();
    Coffee* coffeeArr = m.get_coffee_arr();
    for(int i = 0; i < m.get_num_coffee(); i++){
        if(coffeeArr[i].get_name() == order.get_coffee_name()){
            coffeeOrder = coffeeArr[i];
            break;
        }
    }
    if(coffeeOrder.get_name() == "N/A"){
        cout << "Error: Order not found, returning $0.00" << endl;
        return 0.0;
    }
    if(order.get_coffee_size() == 'S' || order.get_coffee_size() == 's'){
        return ((coffeeOrder.get_small_cost()) * (order.get_quantity()));
    }
    else if(order.get_coffee_size() == 'M' || order.get_coffee_size() == 'm'){
        return ((coffeeOrder.get_medium_cost()) * (order.get_quantity())); 
    }
    else if(order.get_coffee_size() == 'L' || order.get_coffee_size() == 'l'){
        return ((coffeeOrder.get_large_cost()) * (order.get_quantity()));
    }
    else{
        cout << "Error: Invalid order size for" << coffeeOrder.get_name() << ", returning $0.00" << endl;
        return 0.0;
    }

}

void Shop::search_by_price() { // problem function; simply doesn't work for some reason
    float desiredPrice;
    do{
    cout << "Enter the maximum price you're willing to spend: ";
    cin >> desiredPrice;
    }while(desiredPrice <= 0);

    int potentialCandidates = 0;

    
    for (int i = 0; i < m.get_num_coffee(); i++) {
        Coffee item = m.get_menu_item(i);
        //cout << item.get_small_cost() << " "; //debug line
        if (item.get_small_cost() <= desiredPrice || item.get_medium_cost() <= desiredPrice || item.get_large_cost() <= desiredPrice) {
            potentialCandidates++;
        }
    }

    if (potentialCandidates == 0) {
        cout << endl << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << " --- Error: No items found. --- " << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        return;
    }

    Coffee* queryResults = new Coffee[potentialCandidates];

    int queryResultsIndex = 0;
    for (int i = 0; i < m.get_num_coffee(); i++) {
        Coffee item = m.get_menu_item(i);
        if (item.get_small_cost() <= desiredPrice || item.get_medium_cost() <= desiredPrice || item.get_large_cost() <= desiredPrice) {
            queryResults[queryResultsIndex] = m.get_menu_item(i);
            queryResultsIndex++;
        }
    }


    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " --- Result(s) found! --- " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

    for (int i = 0; i < potentialCandidates; i++){
        cout << endl << "  Name:  " << endl << "    " << queryResults[i].get_name() << endl << endl;
        cout << "  Pricing Options:  " << endl;
        cout << "    Small Size  - $" << queryResults[i].get_small_cost() << endl;
        cout << "    Medium Size - $" << queryResults[i].get_medium_cost() << endl;
        cout << "    Large Size  - $" << queryResults[i].get_large_cost() << endl;
        cout << endl << endl << endl;
    }

    int yesOrNo;
    cout << "Do you wish to order something from the search results? yes(1) or no(0): ";
    cin >> yesOrNo;
    if(yesOrNo == 1){
        cout << endl << "Awesome! Queueing up your order prompts now." << endl << endl;
        cout << "Please pick the name of the coffee you wish to order from the following options:" << endl << endl;
        int userChoice;
        do{
        for(int i = 0; i < potentialCandidates; i++){
            cout << i+1 << ") " << queryResults[i].get_name() << endl;
        }
        cin >> userChoice;
        }while(userChoice <= 0 || userChoice > potentialCandidates);
        place_order_from_search(queryResults[userChoice - 1].get_name());
    }
    else{
        cout << endl << "- Returning to customer menu - " << endl << endl;
    }
}


void Shop::search_by_name() {
    string name;
    Coffee desiredCoffee;
    cout << "Enter the name of the item you want to search for: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < m.get_num_coffee(); i++) {
        Coffee item = m.get_menu_item(i);
        if (item.get_name() == name) {
            desiredCoffee = item;
            found = true;
            cout << endl << "~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << " --- Item found! --- " << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << " -- Menu Item #" << i+1 << " -- " << endl;
            cout << endl << "  Name:  " << endl << "    " << item.get_name() << endl << endl;
            cout << "  Pricing Options:  " << endl;
            cout << "    Small Size  - $" << item.get_small_cost() << endl;
            cout << "    Medium Size - $" << item.get_medium_cost() << endl;
            cout << "    Large Size  - $" << item.get_large_cost() << endl;
            cout << endl << endl << endl;
        }
    }
    if (!found) {
        cout << endl << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << " --- Error: Item not found. --- " << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        return;
    }
    int yesOrNo;
    cout << "Do you wish to order a " << desiredCoffee.get_name() << "? yes(1) or no(0): ";
    cin >> yesOrNo;
    if(yesOrNo == 1){
        cout << "Awesome! Queueing up your order prompts now." << endl << endl;
        place_order_from_search(desiredCoffee.get_name());
    }
    else{
        cout << endl << " - Returning to customer menu - " << endl << endl;
    }
}

void Shop::place_order_from_search(string coffee_name) {
    // Read the current order count from the file
    int order_count;
    ifstream count_file("orders.txt");
    count_file >> order_count;
    count_file.close();

    // ** Prompt the user for the order details **

    // gets the coffee size
    bool validOrder = false;
    char coffee_size;
    do{
    cout << "Enter the size you wish to order (S, M, or L): ";
    cin >> coffee_size;
    if(coffee_size == 'S' || coffee_size == 's'){
        if(coffee_size == 's'){coffee_size = 'S';}
        validOrder = true;
    }
    else if(coffee_size == 'M' || coffee_size == 'm'){
        if(coffee_size == 'm'){coffee_size = 'M';}
        validOrder = true;
    }
    else if(coffee_size == 'L' || coffee_size == 'l'){
        if(coffee_size == 'l'){coffee_size = 'L';}
        validOrder = true;
    }
    }while(!validOrder);

    // gets the coffee quantity
    int quantity;
    cout << "Enter quantity: ";
    cin >> quantity;
    while(quantity <= 0){
        cout << "Enter quantity: ";
        cin >> quantity;
    }

    // Create a new Order object
    Order new_order(order_count + 1, coffee_name, coffee_size, quantity);

    Order* newOrderArr = new Order[order_count + 1];

    for(int i = 0; i < order_count; i++){
        newOrderArr[i].set_id(order_arr[i].get_id());
        newOrderArr[i].set_coffee_name(order_arr[i].get_coffee_name());
        newOrderArr[i].set_coffee_size(order_arr[i].get_coffee_size());
        newOrderArr[i].set_quantity(order_arr[i].get_quantity());
    }
    newOrderArr[order_count].set_id(order_count + 1);
    newOrderArr[order_count].set_coffee_name(coffee_name);
    newOrderArr[order_count].set_coffee_size(coffee_size);
    newOrderArr[order_count].set_quantity(quantity);

    // Increment the order count and write it back to the file
    order_count++;
    ofstream count_outfile("orders.txt");
    count_outfile << order_count << endl;
    count_outfile.close();

    // Open the orders file in append mode
    ofstream orders_file("orders.txt", ios::app);

    // Re-include the orders already present into the file
    for(int i = 0; i <= num_orders; i++){
        orders_file << newOrderArr[i].get_id() << " " << newOrderArr[i].get_coffee_name() << " " << newOrderArr[i].get_coffee_size() << " " << newOrderArr[i].get_quantity() << endl; 
    }

    // Close the orders file
    orders_file.close();
    cout << endl << endl << "Order of " << new_order.get_coffee_name() << " successfully placed! :)" << endl << endl << endl;
}


// ***** BONUS FUNCTIONS!! *****
void Shop::view_best_seller(){
    if(order_arr == NULL){
        cout << endl << "You need to have orders before you can execute this operation!" << endl << endl;
        return;
    }

    Order largestOrder;
    int largestQuantity = 0;
    for(int i = 1; i < num_orders; i++){
        if(order_arr[i].get_quantity() > largestQuantity){
            largestOrder = order_arr[i];
            largestQuantity = order_arr[i].get_quantity();
        }
    }
    cout << endl << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " --- Best Seller --- " << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    
    cout << "Name: " << largestOrder.get_coffee_name() << endl;
    cout << "Size: " << largestOrder.get_coffee_size() << endl << endl;
}

void Shop::view_top_3_popular_drinks(){
    if(order_arr == NULL){
        cout << endl << "You need to have more orders before you can execute this operation!" << endl << endl;
        return;
    }

    Order greatest_small_size;
    Order greatest_medium_size;
    Order greatest_large_size;

    int greatest_small_size_val = 0;
    int greatest_medium_size_val = 0;
    int greatest_large_size_val = 0;

    for(int i = 0; i < num_orders; i++){
        if(order_arr[i].get_coffee_size() == 'S'){
            if(Shop::get_order_price(order_arr[i]) > greatest_small_size_val){
                greatest_small_size_val = Shop::get_order_price(order_arr[i]);
                greatest_small_size = order_arr[i];
            }
        }
        else if(order_arr[i].get_coffee_size() == 'M'){
            if(Shop::get_order_price(order_arr[i]) > greatest_medium_size_val){
                greatest_medium_size_val = Shop::get_order_price(order_arr[i]);
                greatest_medium_size = order_arr[i];
            }
        }
        else if(order_arr[i].get_coffee_size() == 'L'){
            if(Shop::get_order_price(order_arr[i]) > greatest_large_size_val){
                greatest_large_size_val = Shop::get_order_price(order_arr[i]);
                greatest_large_size = order_arr[i];
            }
        }
    }

    cout << "Most Popular Small Drink: " << greatest_small_size.get_coffee_name() << endl;
    cout << "Most Popular Medium Drink: " << greatest_medium_size.get_coffee_name() << endl;
    cout << "Most Popular Large Drink: " << greatest_large_size.get_coffee_name() << endl << endl;
}
// *****************************

// for the customer
void Shop::place_order() {
    // Read the current order count from the file
    int order_count;
    ifstream count_file("orders.txt");
    count_file >> order_count;
    count_file.close();

    // ** Prompt the user for the order details **

    // Gets the coffee name
    string coffee_name;
    bool validOrder = false;
    do{
    cout << "Enter a coffee that's on the menu: ";
    cin >> coffee_name;

    Coffee* coffeeArr = m.get_coffee_arr();
    for(int i = 0; i < m.get_num_coffee(); i++){
        if(coffeeArr[i].get_name() == coffee_name){
            validOrder = true;
            break;
        }
    }
    }while(!validOrder);

    // gets the coffee size
    validOrder = false;
    char coffee_size;
    do{
    cout << "Enter the size you wish to order (S, M, or L): ";
    cin >> coffee_size;
    if(coffee_size == 'S' || coffee_size == 's'){
        if(coffee_size == 's'){coffee_size = 'S';}
        validOrder = true;
    }
    else if(coffee_size == 'M' || coffee_size == 'm'){
        if(coffee_size == 'm'){coffee_size = 'M';}
        validOrder = true;
    }
    else if(coffee_size == 'L' || coffee_size == 'l'){
        if(coffee_size == 'l'){coffee_size = 'L';}
        validOrder = true;
    }
    }while(!validOrder);

    // gets the coffee quantity
    int quantity;
    cout << "Enter quantity: ";
    cin >> quantity;
    while(quantity <= 0){
        cout << "Enter quantity: ";
        cin >> quantity;
    }

    // Create a new Order object
    Order new_order(order_count + 1, coffee_name, coffee_size, quantity);

    Order* newOrderArr = new Order[order_count + 1];

    for(int i = 0; i < order_count; i++){
        newOrderArr[i].set_id(order_arr[i].get_id());
        newOrderArr[i].set_coffee_name(order_arr[i].get_coffee_name());
        newOrderArr[i].set_coffee_size(order_arr[i].get_coffee_size());
        newOrderArr[i].set_quantity(order_arr[i].get_quantity());
    }
    newOrderArr[order_count].set_id(order_count + 1);
    newOrderArr[order_count].set_coffee_name(coffee_name);
    newOrderArr[order_count].set_coffee_size(coffee_size);
    newOrderArr[order_count].set_quantity(quantity);

    // Increment the order count and write it back to the file
    order_count++;
    ofstream count_outfile("orders.txt");
    count_outfile << order_count << endl;
    count_outfile.close();

    // Open the orders file in append mode
    ofstream orders_file("orders.txt", ios::app);

    // Re-include the orders already present into the file
    for(int i = 0; i <= num_orders; i++){
        orders_file << newOrderArr[i].get_id() << " " << newOrderArr[i].get_coffee_name() << " " << newOrderArr[i].get_coffee_size() << " " << newOrderArr[i].get_quantity() << endl; 
    }

    // Close the orders file
    orders_file.close();
    cout << endl << endl << "Order of " << new_order.get_coffee_name() << " successfully placed! :)" << endl << endl << endl;
}

// for the employee
void Shop::add_to_menu() {
    // get item details from user
    string name;
    float small_price;
    float medium_price;
    float large_price;

    cout << "Enter coffee name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    do {
        cout << "Enter coffee small size price: ";
        cin >> small_price;
    } while (small_price <= 0);

    do {
        cout << "Enter coffee medium size price: ";
        cin >> medium_price;
    } while (medium_price <= 0);

    do {
        cout << "Enter coffee large size price: ";
        cin >> large_price;
    } while (large_price <= 0);

    Coffee* newCoffee = new Coffee(name, small_price, medium_price, large_price);
    m.add_to_menu(*newCoffee);

    ofstream menuFile("menu.txt", ios::trunc);
    menuFile << m.get_num_coffee() << endl;

    Coffee* coffeeArr = m.get_coffee_arr();

    for(int i = 0; i < m.get_num_coffee(); i++){
        menuFile << coffeeArr[i].get_name() << " ";
        menuFile << coffeeArr[i].get_small_cost() << " ";
        menuFile << coffeeArr[i].get_medium_cost() << " ";
        menuFile << coffeeArr[i].get_large_cost() << endl;
    }
    menuFile.close();
    cout << endl << "Successfully added " << newCoffee->get_name() << " to the menu!" << endl << endl;
}

// req. for the remove_from_menu() function
struct MenuItem {
    string name;
    float small_price, medium_price, large_price;
};

// dependent on struct MenuItem
void Shop::remove_from_menu() {
    // display menu and prompt user for item to remove
    int choice;
    do {
        cout << "Menu:" << endl;
        ifstream file("menu.txt");
        int num_items;
        file >> num_items;
        for (int i = 0; i < num_items; i++) {
            string name;
            float small_price, medium_price, large_price;
            file >> name >> small_price >> medium_price >> large_price;
            cout << i + 1 << ") " << name << endl;
        }
        file.close();

        cout << "Enter the number of the item you want to remove (enter 0 to quit): ";
        cin >> choice;

        if (choice != 0 && choice <= num_items && !(choice < 0)) {
            // read data from file into an array of structs
            file.open("menu.txt");
            file >> num_items;
            struct MenuItem items[num_items];
            for (int i = 0; i < num_items; i++) {
                file >> items[i].name >> items[i].small_price >> items[i].medium_price >> items[i].large_price;
            }
            file.close();

            // remove desired item from array
            for (int i = choice - 1; i < num_items - 1; i++) {
                items[i] = items[i + 1];
            }
            num_items--;

            // rewrite entire file with updated data
            ofstream out("menu.txt");
            out << num_items << endl;
            for (int i = 0; i < num_items; i++) {
                out << items[i].name << " " << items[i].small_price << " " << items[i].medium_price << " " << items[i].large_price << endl;
            }
            out.close();

            cout << endl << "Item successfully removed from the menu!" << endl << endl;
        } else if (choice != 0 || choice < 0) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    Shop::load_data();
}

// for the employee
void Shop::view_orders() {
    //Shop::load_data();
    ifstream orders_file("orders.txt");
    if (!orders_file) {
        cerr << "Failed to open orders file." << endl;
        return;
    }

    int num_orders;
    orders_file >> num_orders;

    cout << endl << endl << "~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " --- Current orders --- " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    for (int i = 0; i < num_orders; i++) {
      int order_num, quantity;
      string coffee_name;
      char coffee_size;
      orders_file >> order_num >> coffee_name >> coffee_size >> quantity;

      cout << "Order " << order_num << ": " << coffee_name << ", " << coffee_size << ", " << quantity << " cup(s)" << endl << endl;
    }
    cout << endl;

    orders_file.close();
}

// for initial bootup
void Shop::load_initial_menu(){
    int menuChoice;
    bool validOption = false;
    // std::cout << "\033[2J";
    // std::cout << "\033[2J";
    cout << "************************************************************" << endl;
    cout << "Welcome to the Coffee++ Shop main menu!" << endl;
    cout << "************************************************************" << endl;
    cout << endl << "Please select your login type, or quit the program via the options below:" << endl << endl;
    do{
        cout << "1) Login as Employee" << endl << "2) Login as Customer" << endl << "3) Quit the Program" << endl << endl << " - Specify your option (1, 2, or 3) - " << endl << endl;
        cin >> menuChoice;

        if(menuChoice == 1){
            display_employee_menu();
            validOption = true;
        }
        else if(menuChoice == 2){
            display_customer_menu();
            validOption = true;
        }
        else if(menuChoice == 3){
            cout << endl << "Thank you for using Coffee++ Shop!" << endl << endl;
            validOption = true;
            std::exit(0);
        }
        else{
            cout << "Invalid option; please try again:" << endl;
        }
    }while(!validOption);
}

// for displaying the employee menu screen
void Shop::display_employee_menu(){
    Shop::load_data();

    int menuChoice;
    bool validOption = false;
    // std::cout << "\033[2J";
    // std::cout << "\033[2J";
    cout << "************************************************************" << endl;
    cout << "Welcome to the employee menu!" << endl;
    cout << "************************************************************" << endl;
    cout << endl << "Please select the employee operation you wish to execute:" << endl << endl;
    do{
        cout << "1) Add a coffee to the menu" << endl
        << "2) Remove a coffee from the menu" << endl
        << "3) View orders" << endl
        << "4) View shop revenue" << endl
        << "5) View shop details" << endl
        << "6) View best seller" << endl
        << "7) View top 3 popular drinks" << endl
        << "8) Quit to login screen" << endl << endl
        << " - Specify your option (1, 2, 3, 4, 5, 6, 7, or 8) - " << endl << endl;
        cin >> menuChoice;

        if(menuChoice == 1){ // add a coffee to the menu // **TODO**
            validOption = true;
            Shop::add_to_menu();
        }
        else if(menuChoice == 2){ // remove a coffee from the menu // **TODO**
            validOption = true;
            Shop::remove_from_menu();
        }
        else if(menuChoice == 3){ // view orders //
            validOption = true;
            Shop::view_orders();
        }
        else if(menuChoice == 4){ // view shop revenue //
            validOption = true;
            Shop::view_shop_revenue();
        }
        else if(menuChoice == 5){ // view shop details //
            validOption = true;
            Shop::view_shop_detail();
        }
        else if(menuChoice == 6){ // view best seller //
            validOption = true;
            Shop::view_best_seller();
        }
        else if(menuChoice == 7){ // view top 3 popular drinks //
            validOption = true;
            Shop::view_top_3_popular_drinks();
        }
        else if(menuChoice == 8){ // quit to login screen //
            validOption = true;
            cout << "Thank you for using the Coffee++ Shop employee menu!" << endl << endl;
            Shop::load_initial_menu();
        }
        else{
            cout << "Invalid option; please try again:" << endl;
        }
    }while(!validOption);
    Shop::display_employee_menu();
}

// for displaying the customer menu screen
void Shop::display_customer_menu(){
	Shop::load_data();

    int menuChoice;
    bool validOption = false;
    // std::cout << "\033[2J";
    // std::cout << "\033[2J";
    cout << "************************************************************" << endl;
    cout << "Welcome to the customer menu!" << endl;
    cout << "************************************************************" << endl << endl;
    cout << "Please select the customer operation you wish to execute:" << endl << endl;
    do{
        cout << "1) Search menu by coffee name" << endl
        << "2) Search menu by coffee price" << endl
        << "3) Place a coffee order" << endl
        << "4) View shop details" << endl
        << "5) Quit to login screen" << endl << endl
        << " - Specify your option (1, 2, 3, 4, or 5) - " << endl << endl;
        cin >> menuChoice;

        if(menuChoice == 1){ // Search menu by coffee name // **TODO**
            validOption = true;
            Shop::search_by_name();
        }
        else if(menuChoice == 2){ // Search menu by coffee price // **TODO**
            validOption = true;
            Shop::search_by_price();
        }
        else if(menuChoice == 3){ // Place a coffee order // **TODO**
            validOption = true;
            Shop::place_order();
        }
        else if(menuChoice == 4){ // View shop details //
            validOption = true;
            Shop::view_shop_detail();
        }
        else if(menuChoice == 5){ // quit to login screen //
            validOption = true;
            cout << "Thank you for using the Coffee++ Shop customer menu!" << endl << endl;
            Shop::load_initial_menu();
        }
        else{
            cout << "Invalid option; please try again:" << endl;
        }
    }while(!validOption);
    Shop::display_customer_menu();
}


// enable a "would you like to order based off of your results?" prompt option for after the user searches for something (via either name or price). If the user selects yes, just run them through the place_order() function (you also likely don't need to add error checking for whether or not what they order next is actually on the menu lol, so just run the function like normal after they search and nobody'll be the wiser)


// fix "place_order();" function
// 