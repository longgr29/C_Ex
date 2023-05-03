#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <vector>   
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <ios>

using namespace std;

struct MenuOption{
    char choice;
    char const *selectionText;
    void (*processingFunction)(void);
};

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

bool display_menu_option(const char* menu_title, MenuOption mainMenu[], unsigned int quantitySelections);
unsigned int handleWrongInput(void);
void show_food_menu(void);
void add_a_new_food(void);
void update_food(void);
void delete_food(void);
void add_tables(void);
void admin_mode(void);
void take_order(void);
void delete_order(void);
void check_out(void);
void staff_mode(void);
void operator_mode(void);

#endif