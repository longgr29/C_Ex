#include <iostream>
#include <string>
#include <vector>   
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <ios>

using namespace std;

class Food{
private:
    unsigned int id;
    string name;
    unsigned int price;
    unsigned int quantity;
public:
    Food(unsigned int id, string name, unsigned int price);
    unsigned int getId() const;
    string getName() const;
    unsigned int getPrice() const;
    void setQuantity(unsigned int quantity);
    unsigned int getQuantity() const;
};

Food::Food(unsigned int id, string name, unsigned int price) : id(id), name(name), price(price) {} 

unsigned int Food::getId() const{
    return this->id;
}

string Food::getName() const{
    return this->name;
}

unsigned int Food::getPrice() const{
    return this->price;
}

void Food::setQuantity(unsigned int quantity){
    this->quantity = quantity;
}

unsigned int Food::getQuantity() const {
    return this->quantity;
}

class Table{
private:
    unsigned int id;
    //0 = free, 1 = busy
    bool state;
    vector<Food> order;
public:
    Table(unsigned int id, bool state);
    unsigned int getId() const;
    bool getState() const;
    void setState(bool newState);
    void add_food(Food food);
    void edit_quantity(unsigned int id, unsigned int newQuantity);
    void erase_food(unsigned int id);
    vector<Food> getOrder() const;
};

Table::Table(unsigned int id, bool state = false) : id(id), state(state) {}

unsigned int Table::getId() const{
    return this->id;
}

bool Table::getState() const{
    return this->state;
}

void Table::setState(bool newState){
    this->state = newState;
}

void Table::add_food(Food food){
    this->order.push_back(food);
}

void Table::edit_quantity(unsigned int id, unsigned int newQuantity){
    for(Food &food : this->order){
        if (food.getId() == id){
            food.setQuantity(newQuantity);
            break;
        }
    }
}

void Table::erase_food(unsigned int id){
    for(auto food = this->order.begin(); food != this->order.end(); food++){
        if(food->getId() == id){
            this->order.erase(food);
            break;
        }
    }
}

vector<Food> Table::getOrder() const{
    return this->order;
}

class Manager{
private:
    vector<Food> foods;
    vector<Table> tables;
public:
    void add_new_food(Food food);
    void update_food_by_id(unsigned int id, Food food);
    void delete_food_in_foods(unsigned int id);
    void display_foods();
    void sort_foods_by_id();
    void add_tables(unsigned int numOfTables);
    void check_tables();
    void order_new_food(unsigned int foodId, unsigned int quantity, unsigned int tableId);
    void delete_food_in_order(unsigned int foodId, unsigned int tableId);
    unsigned int check_out(unsigned int tableId) const;
    void set_state_table(bool state, unsigned int tableId);
};

void Manager::add_new_food(Food food){
    foods.push_back(food);
}

void Manager::update_food_by_id(unsigned int id, Food newFood){
    for(auto &food : foods){
        if(food.getId() == id){
            food = newFood;
            break;
        }
    }
}

void Manager::delete_food_in_foods(unsigned int id){
    for(auto food = foods.begin(); food != foods.end(); food++){
        if(food->getId() == id){
            foods.erase(food);
            break;
        }
    }
}

void Manager::sort_foods_by_id(){
    for(unsigned int i = 1; i < this->foods.size(); i++){
        Food selectedFood = this->foods[i];
        unsigned int j = i - 1;
        while(j >= 0 && selectedFood.getId() < this->foods[j].getId()){
            this->foods[j + 1] = this->foods[j];
            j--;
        }
        this->foods[j + 1] = selectedFood;
    }
}

void Manager::display_foods() {
    sort_foods_by_id();

    std::cout <<"|" << std::setw(4) << std::right << "STT|";
    std::cout << std::setw(5) << std::right << "ID|";
    std::cout << std::setw(14) << std::right << "Name|";
    std::cout << std::setw(13) << std::right << "Price (VND)|" << endl;
    unsigned int i = 1;
    for(Food food : foods){
        std::cout << "|" << std::setw(3) << std::right << i << "|";
        std::cout << std::setw(4) << std::right << food.getId() << "|";
        std::cout << std::setw(13) << std::right << food.getName() << "|";
        std::cout << std::setw(8) << std::right << food.getPrice()/1000 << "." << setw(3) << setfill('0') << food.getPrice()%1000 << "|" << setfill(' ') << endl;
        i++;
    }
}

void Manager::add_tables(unsigned int numOfTables){
    unsigned int currentTables = tables.size();
    for(int i = 0; i < numOfTables; i++){
        tables.push_back({currentTables + 1 + i});
    }
}

void Manager::check_tables(){
    cout << "| Tables|";
    for(auto table : tables){
        cout << setw(3) << right << table.getId() << "|";
    } 
    cout << endl << "|  State|";
    for(auto table : tables){
        cout << setw(3) << right << (table.getState()?"x ":"") << "|";
    }
}

void Manager::order_new_food(unsigned int foodId, unsigned int quantity, unsigned int tableId){
    bool findingFlag = false;
    for(Food food : tables[tableId - 1].getOrder()){
        if (food.getId() == foodId){
            findingFlag = true;
            tables[tableId - 1].edit_quantity(foodId, quantity);
            break;
        }
    }
    if(!findingFlag){
        for(auto food : foods){
            if (food.getId() == foodId){
                food.setQuantity(quantity);
                tables[tableId - 1].add_food(food);
                break;
            }
        }
    }
}

void Manager::delete_food_in_order(unsigned int foodId, unsigned int tableId){
    tables[tableId - 1].erase_food(foodId);
}

unsigned int Manager::check_out(unsigned int tableId) const{
    unsigned int i = 1;
    unsigned int totalPayments = 0;

    std::cout <<"|" << std::setw(4) << std::right << "STT|";
    std::cout << std::setw(5) << std::right << "ID|";
    std::cout << std::setw(14) << std::right << "Name|";
    std::cout << std::setw(13) << std::right << "Price (VND)|" ;
    std::cout << std::setw(9) << std::right << "Quantity|" << endl;
    for(Food food : tables[tableId - 1].getOrder()){
        std::cout << "|" << std::setw(3) << std::right << i << "|";
        std::cout << std::setw(4) << std::right << food.getId() << "|";
        std::cout << std::setw(13) << std::right << food.getName() << "|";
        std::cout << std::setw(8) << std::right << food.getPrice()/1000 << "." << setw(3) << setfill('0') << food.getPrice()%1000 << "|" << setfill(' ');
        std::cout << std::setw(8) << std::right << food.getQuantity() << "|" << endl;
        i++;
        totalPayments += food.getPrice() * food.getQuantity();
    }
    return totalPayments;
}

//Free = 0, busy = 1
void Manager::set_state_table(bool state, unsigned int tableId){
    tables[tableId - 1].setState(state);
}

struct MenuOption{
    char choice;
    char const *selectionText;
    void (*processingFunction)(void);
};

Manager manager;
unsigned int selectionTable;

bool display_menu_option(const char* menu_title, MenuOption mainMenu[], unsigned int quantitySelections);

unsigned int handleWrongInput() {
    unsigned int num;
    while (!(std::cin >> num)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    return num;
}

void show_food_menu(){
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Menu\n"
        "------------------------------\n";
    system("cls");
    cout << menu_title << endl;
    manager.display_foods();
    cout << endl;
    system("pause");
}

void add_a_new_food(){
    try{
        const char* menu_title = 
            "\n"
            "------------------------------\n"
            "         Add New Foods\n"
            "------------------------------\n";
        unsigned int id;
        string name;
        unsigned int price;

        system("cls");
        cout << menu_title << endl;
        manager.display_foods();
        cout << endl << "Enter food ID: ";
        id = handleWrongInput();
        cout << endl << "Enter food name: ";
        cin >> name;
        cout << endl << "Enter price: ";
        price = handleWrongInput();
        manager.add_new_food({id, name, price});

        system("cls");
        cout << "Add food successful." << endl;
        cout << "1. Add a different kind of food" << endl;
        cout << "0. Return" << endl;
        char choice;
        cin >> choice;
        if (choice == '1'){
            add_a_new_food();
        }
    } catch(exception ex){
        system("cls");
        cout << "Add foods unsuccessful." << endl;
        system("pause");
    }
}

void update_food(){
    try{
        const char* menu_title = 
            "\n"
            "------------------------------\n"
            "         Update A Food By ID\n"
            "------------------------------\n";
        unsigned int id;
        string name;
        unsigned int price;

        system("cls");
        cout << menu_title << endl;
        manager.display_foods();
        cout << endl << "Enter old food ID: ";
        id = handleWrongInput();
        cout << endl << "Enter new food name: ";
        cin >> name;
        cout << endl << "Enter new price: ";
        price = handleWrongInput();
        manager.update_food_by_id(id, {id, name, price});

        system("cls");
        cout << "Update successful." << endl;
        system("pause");
    } catch(exception ex){
        system("cls");
        cout << "Update food unsuccessful." << endl;
        system("pause");
    }
}

void delete_food(){
    try{
        const char* menu_title = 
            "\n"
            "------------------------------\n"
            "         Delete A Food By ID\n"
            "------------------------------\n";
        unsigned int id;

        system("cls");
        cout << menu_title << endl;
        manager.display_foods();
        cout << endl << "Enter food ID: ";
        id = handleWrongInput();
        manager.delete_food_in_foods(id);
        system("cls");
        cout << "Delete successful." << endl;
        system("pause");
    } catch(exception ex){
        system("cls");
        cout << "Delete food unsuccessful." << endl;
        system("pause");
    }
}

void add_tables(){
    try{
        const char* menu_title = 
            "\n"
            "------------------------------\n"
            "         Add New Tables\n"
            "------------------------------\n";
        unsigned int numTables;

        system("cls");
        cout << menu_title << endl;
        manager.check_tables();

        cout << endl << "Enter a number of new tables: ";
        numTables = handleWrongInput();
        manager.add_tables(numTables);
        system("cls");
        cout << "Add successful." << endl;
        system("pause");
    } catch(exception ex){
        system("cls");
        cout << "Add tables unsuccessful." << endl;
        system("pause");
    }
}

void admin_mode() {
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Admin Mode\n"
        "------------------------------\n";

    MenuOption mainMenu[] =
    {
        {'1', "Show menu", show_food_menu},
        {'2', "Add a new food", add_a_new_food},
        {'3', "Update a food by ID", update_food},
        {'4', "Delete a food by ID", delete_food},
        {'5', "Add tables", add_tables},
        {'0', "Return"},
    };

    while(1){
        if(display_menu_option(menu_title, mainMenu, 6))
            break; 
    }
}

void take_order(){
    try{
        system("cls");
        cout << "\n"
        "------------------------------\n" 
        "         Table " << selectionTable << "\n" <<
        "------------------------------\n";
        unsigned int id;
        unsigned int quantity;

        manager.check_out(selectionTable);
        cout << endl << "Enter food ID: ";
        id = handleWrongInput();
        cout << endl << "Enter quantity: ";
        quantity = handleWrongInput();
        manager.order_new_food(id, quantity, selectionTable);

        system("cls");
        cout << "Order food successful." << endl;
        cout << "1. Order a different kind of food" << endl;
        cout << "0. Return" << endl;
        char choice;
        cin >> choice;
        if (choice == '1'){
            take_order();
        }
    } catch(exception ex){
        system("cls");
        cout << "Add foods unsuccessful." << endl;
        system("pause");
    }
}

void delete_order(){
    system("cls");
    cout << "\n"
    "------------------------------\n" 
    "         Table " << selectionTable << "\n" <<
    "------------------------------\n";
    unsigned int id;

    manager.check_out(selectionTable);
    cout << endl << "Remove order. Enter food ID: ";
    id = handleWrongInput();
    manager.delete_food_in_order(id, selectionTable);
    system("cls");
    cout << "Remove order successful." << endl;
    system("pause");
}

void check_out(){
    system("cls");
    cout << "\n"
    "------------------------------\n" 
    "         Table " << selectionTable << "\n" <<
    "------------------------------\n";
    unsigned int totalPay = manager.check_out(selectionTable);

    cout << endl << "Total amount to pay: " << totalPay/1000 << "." << setw(3) << setfill('0') << totalPay%1000 << setfill(' ') << " VND" << endl;
    system("pause");
}

void staff_mode(){
    
    while(1){
        system("cls");
        cout << "\n"
        "------------------------------\n" 
        "         Table " << selectionTable << "\n" <<
        "------------------------------\n";
        MenuOption mainMenu[] =
        {
            {'1', "Take order", take_order},
            {'2', "Edit order", take_order},
            {'3', "Delete a food in order", delete_order},
            {'4', "Checkout", check_out},
            {'0', "Return"},
        };

        manager.set_state_table(true, selectionTable);
        manager.check_out(selectionTable);
        cout << endl;
        for (size_t i = 0; i < 5; ++i)
        {
            std::cout << mainMenu[i].choice << ". " << mainMenu[i].selectionText << "\n";
        }
        char choice;
        cin >> choice;
        if(choice == '0'){
            return;
        }
        for (size_t i = 0; i < 5; ++i)
        {
            if (choice == mainMenu[i].choice)
            {
                (mainMenu[i].processingFunction)();
            }
        }
    }
}

void operator_mode() {
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Select Table\n"
        "------------------------------\n";

    while(1){
        system("cls");
        cout << menu_title << endl;
        manager.check_tables();
        cout << endl << "Enter table number(or '0' to return): " ;
        unsigned int choice = handleWrongInput();
        if(choice == 0)
            return;
        else{
            selectionTable = choice;
            staff_mode();
        }
    }
}

bool display_menu_option(const char* menu_title, MenuOption mainMenu[], unsigned int quantitySelections) {
    system("cls");
    cout << menu_title;
        for (size_t i = 0; i < quantitySelections; ++i)
        {
            std::cout << mainMenu[i].choice << ". " << mainMenu[i].selectionText << "\n";
        }
        char choice;
        cin >> choice;
        if(choice == '0'){
            return true;
        }
        for (size_t i = 0; i < quantitySelections; ++i)
        {
            if (choice == mainMenu[i].choice)
            {
                (mainMenu[i].processingFunction)();
                return false;
            }
        }
}

int main()
{
    const char* menu_title = 
        "\n"
        "------------------------------\n"
        "         Main Menu\n"
        "------------------------------\n";

    MenuOption mainMenu[] =
    {
        {'1', "Admin mode", admin_mode},
        {'2', "Operator mode", operator_mode},
    };
    while(1){
        display_menu_option(menu_title, mainMenu, 2);
    }
    return 0;
    
    // Food a(1, "coca", 10000);
    // Food b(2, "pepsi", 10000);
    // Food c(3, "mo", 20000);
    // Manager ab;
    // ab.add_new_food(a);
    // ab.add_new_food(b);
    // ab.add_new_food(c);
    
    // // ab.display_foods();
    // ab.add_tables(5);
    // ab.add_tables(5);
    // ab.check_tables();

    // cout << endl;

    // ab.order_new_food(1, 2, 1);
    // ab.order_new_food(3, 5, 1);
    // ab.order_new_food(1, 1, 1);
    // ab.order_new_food(2, 1, 1);

    // unsigned int g = ab.check_out(1);
    // cout << g ;
    
    // return 0;
}
