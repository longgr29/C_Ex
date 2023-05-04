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
#include <functional>

using namespace std;

struct MenuOption{
    char choice;
    char const *selectionText;
    std::function<void(void)> processingFunction;
};

enum RentalStatus {
    FREE = 0,
    HOURLY_RENTAL = 1,
    OVERNIGHT_RENTAL = 2,
};

class Date {
public:
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    unsigned int year;

    Date(int h, int d, int m, unsigned int y) ;
    //caculate the different hours
    unsigned int operator-(const Date& other) const;
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

class Room{
private:
    unsigned int id;
    RentalStatus state;
    vector<Food> order;
    Date startDate;
public:
    Room(unsigned int id, RentalStatus state);
    unsigned int getId() const;
    RentalStatus getState() const;
    void setState(RentalStatus newState);
    void add_food(Food food, unsigned int newQuantity);
    void edit_quantity(unsigned int id, unsigned int newQuantity);
    void erase_food(unsigned int id);
    vector<Food> getOrder() const;
    Date getStartDate() const;
    void setStartDate(Date startDate);
};

class Database{
private:
    unsigned int hourlyPrice;
    unsigned int overnightPrice;
    vector<Food> foods;
    vector<Room> rooms;
public:
    void setHourlyPrice(unsigned int newHourlyPrice);
    unsigned int getHourlyPrice() const;
    void setOvernightPrice(unsigned int newOvernightPrice);
    unsigned int getOvernightPrice() const;
    void add_new_food(Food food);
    void update_food_by_id(unsigned int id, Food food);
    void delete_food_by_id(unsigned int id);
    vector<Food> getFoods();
    void sort_foods_by_id();
    void add_rooms(unsigned int numOfRooms);
    vector<Room> getRooms() const;
    RentalStatus getRoomStatus(unsigned int roomId) const;
    void setRoomStatus(unsigned int roomId, RentalStatus state);
    void setStartDate(unsigned int roomId, Date startDate);
    Date getStartDate(unsigned int roomId);
    void take_order(unsigned int roomId, unsigned int foodId, unsigned int quantity);
    void remove_order(unsigned int roomId, unsigned int foodId);
    unsigned int show_bill(unsigned int roomId) const;
};

class Admin{
public:
    void menu_option(void);
    void add_new_food();
    void update_food_by_id();
    void delete_food_by_id();
    void display_foods() const;
    void add_rooms();
    void display_rooms() const;
    void update_room_price();
    void menu_foods_and_drinks() const;
};

class Operator {
public:
    void room_selection(void);
    void check_in();
    void order_new_food();
    void remove_food_in_order();
    void check_out() const;
    void display_rooms() const;
    void selected_room_menu();
    void order_foods_menu();
    void get_room_status();
    void show_food_bill() const;
};

bool display_menu_option(const char* menu_title, MenuOption mainMenu[], unsigned int quantitySelections);
unsigned int handleWrongInput(void);
void home_menu();

#endif