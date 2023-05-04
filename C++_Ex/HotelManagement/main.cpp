#include "main.h"

Database database1;
Admin manager;
Operator staff;
unsigned int selectedRoom {0};

Date::Date(int h = 0, int d = 1, int m = 1, unsigned int y = 1) : hour(h), day(d), month(m), year(y) {}

unsigned int Date::operator-(const Date& other) const {
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        daysInMonth[1] = 29;
    }
    int totalDays1 = day;
    for (int i = 0; i < month - 1; i++) {
        totalDays1 += daysInMonth[i];
    }
    totalDays1 += (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

    int totalDays2 = other.day;
    for (int i = 0; i < other.month - 1; i++) {
        totalDays2 += daysInMonth[i];
    }
    totalDays2 += (other.year - 1) * 365 + (other.year - 1) / 4 - (other.year - 1) / 100 + (other.year - 1) /400;

    int diffDays = (totalDays2 - totalDays1);
    int diffHours = diffDays * 24 + (other.hour - hour);
    return diffHours;
}

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

Room::Room(unsigned int id, RentalStatus state = FREE) : id(id), state(state) {}

unsigned int Room::getId() const{
    return this->id;
}

RentalStatus Room::getState() const{
    return this->state;
}

void Room::setState(RentalStatus newState){
    this->state = newState;
}

void Room::add_food(Food food, unsigned int quantity){
    food.setQuantity(quantity);
    this->order.push_back(food);
}

void Room::edit_quantity(unsigned int id, unsigned int newQuantity){
    for(Food &food : this->order){
        if (food.getId() == id){
            food.setQuantity(newQuantity);
            break;
        }
    }
}

void Room::erase_food(unsigned int id){
    for(auto food = this->order.begin(); food != this->order.end(); food++){
        if(food->getId() == id){
            this->order.erase(food);
            break;
        }
    }
}

vector<Food> Room::getOrder() const{
    return this->order;
}

Date Room::getStartDate() const{
    return this->startDate;
}

void Room::setStartDate(Date startDate){
    this->startDate = startDate;
}

void Database::add_new_food(Food food){
    foods.push_back(food);
}

void Database::update_food_by_id(unsigned int id, Food newFood){
    for(auto &food : foods){
        if(food.getId() == id){
            food = newFood;
            break;
        }
    }
}

void Database::delete_food_by_id(unsigned int id){
    for(auto food = foods.begin(); food != foods.end(); food++){
        if(food->getId() == id){
            foods.erase(food);
            break;
        }
    }
}

void Database::sort_foods_by_id(){
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

void Database::add_rooms(unsigned int numOfRooms){
    unsigned int currentRooms = rooms.size();
    for(int i = 0; i < numOfRooms; i++){
        rooms.push_back({currentRooms + 1 + i});
    }
}

vector<Food> Database::getFoods(){
    this->sort_foods_by_id();
    return this->foods;
}

vector<Room> Database::getRooms() const{
    return this->rooms;
}

void Database::setHourlyPrice(unsigned int newHourlyPrice){
    this->hourlyPrice = newHourlyPrice;
}

unsigned int Database::getHourlyPrice() const{
    return this->hourlyPrice;
}

void Database::setOvernightPrice(unsigned int newOvernightPrice){
    this->overnightPrice = newOvernightPrice;
}
unsigned int Database::getOvernightPrice() const{
    return this->overnightPrice;
}

RentalStatus Database::getRoomStatus(unsigned int roomId) const
{
    return rooms[roomId - 1].getState();
}

void Database::setRoomStatus(unsigned int roomId, RentalStatus state){
    rooms[roomId - 1].setState(state);
}

void Database::setStartDate(unsigned int roomId, Date startDate){
    rooms[roomId - 1].setStartDate(startDate);
}

Date Database::getStartDate(unsigned int roomId){
    return rooms[roomId - 1].getStartDate();
}

void Database::take_order(unsigned int roomId, unsigned int foodId, unsigned int quantity){
    for (Food food : rooms[roomId - 1].getOrder()){
        if(food.getId() == foodId){
            rooms[roomId - 1].edit_quantity(foodId, quantity);
            return;
        }
    }
    for(Food food : foods){
        if(food.getId() == foodId){
            rooms[roomId - 1].add_food(food, quantity);
            break;
        }
    }
}

void Database::remove_order(unsigned int roomId, unsigned int foodId){
    rooms[roomId - 1].erase_food(foodId);
}

unsigned int Database::show_bill(unsigned int roomId) const{
    unsigned int i = 1;
    unsigned int totalPayments = 0;

    std::cout << "|" << std::setw(4) << std::right << "STT|";
    std::cout << std::setw(5) << std::right << "ID|";
    std::cout << std::setw(14) << std::right << "Name|";
    std::cout << std::setw(13) << std::right << "Price (VND)|";
    std::cout << std::setw(9) << std::right << "Quantity|" << endl;
    vector<Room> rooms = database1.getRooms();
    for (Food food : rooms[roomId - 1].getOrder())
    {
        std::cout << "|" << std::setw(3) << std::right << i << "|";
        std::cout << std::setw(4) << std::right << food.getId() << "|";
        std::cout << std::setw(13) << std::right << food.getName() << "|";
        std::cout << std::setw(8) << std::right << food.getPrice() / 1000 << "." << setw(3) << setfill('0') << food.getPrice() % 1000 << "|" << setfill(' ');
        std::cout << std::setw(8) << std::right << food.getQuantity() << "|" << endl;
        i++;
        totalPayments += food.getPrice() * food.getQuantity();
    }
    return totalPayments;
}

void Admin::add_new_food(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "         Add New Foods\n"
        "------------------------------\n";
    unsigned int id;
    string name;
    unsigned int price;

    system("cls");
    cout << menu_title << endl;
    this->display_foods();
    cout << endl
         << "Enter food ID: ";
    id = handleWrongInput();
    cout << endl
         << "Enter food name: ";
    cin >> name;
    cout << endl
         << "Enter price: ";
    price = handleWrongInput();
    database1.add_new_food({id, name, price});

    system("cls");
    cout << "Add food successful." << endl;
    cout << "1. Add a different kind of food" << endl;
    cout << "0. Return" << endl;
    char choice;
    cin >> choice;
    if (choice == '1')
    {
        this->add_new_food();
    }
}

void Admin::update_food_by_id(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "         Update A Food By ID\n"
        "------------------------------\n";
    unsigned int id;
    string name;
    unsigned int price;

    system("cls");
    cout << menu_title << endl;
    this->display_foods();
    cout << endl
         << "Enter old food ID: ";
    id = handleWrongInput();
    cout << endl
         << "Enter new food name: ";
    cin >> name;
    cout << endl
         << "Enter new price: ";
    price = handleWrongInput();
    database1.update_food_by_id(id, {id, name, price});

    system("cls");
    cout << "Update successful." << endl;
    system("pause");
}

void Admin::delete_food_by_id(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "     Remove A Food By ID\n"
        "------------------------------\n";
    unsigned int id;

    system("cls");
    cout << menu_title << endl;
    this->display_foods();
    cout << endl
         << "Enter food ID: ";
    id = handleWrongInput();
    database1.delete_food_by_id(id);
    system("cls");
    cout << "Delete successful." << endl;
    system("pause");
}

void Admin::display_foods() const{
    vector<Food> foods = database1.getFoods();
    std::cout << "\n|" << std::setw(4) << std::right << "STT|";
    std::cout << std::setw(5) << std::right << "ID|";
    std::cout << std::setw(14) << std::right << "Name|";
    std::cout << std::setw(13) << std::right << "Price (VND)|" << endl;
    unsigned int i = 1;
    for (Food food : foods)
    {
        std::cout << "|" << std::setw(3) << std::right << i << "|";
        std::cout << std::setw(4) << std::right << food.getId() << "|";
        std::cout << std::setw(13) << std::right << food.getName() << "|";
        std::cout << std::setw(8) << std::right << food.getPrice() / 1000 << "." << setw(3) << setfill('0') << food.getPrice() % 1000 << "|" << setfill(' ') << endl;
        i++;
    }
    cout << endl;
    system("pause");
}

void Admin::add_rooms(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "         Add New Rooms\n"
        "------------------------------\n";

    system("cls");
    cout << menu_title << endl;
    this->display_rooms();
    cout << endl
         << "Enter a number of new rooms: ";
    unsigned int numRooms = handleWrongInput();
    database1.add_rooms(numRooms);
    system("cls");
    cout << "Add successful." << endl;
    system("pause");
}

void Admin::display_rooms() const{
    vector<Room> rooms = database1.getRooms();
    cout << "|  Rooms|";
    for (auto room : rooms)
    {
        cout << setw(3) << right << room.getId() << "|";
    }
    cout << endl
         << "|  State|";
    for (auto room : rooms)
    {
        cout << setw(3) << right << (room.getState() ? "x " : "") << "|";
    }
}

void Admin::update_room_price(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "      Update Room Price\n"
        "------------------------------\n";

    system("cls");
    cout << menu_title << endl;
    cout << "Enter hourly room rental price: ";
    database1.setHourlyPrice(handleWrongInput());
    cout << endl << "Enter overnight room rental price: ";
    database1.setOvernightPrice(handleWrongInput());
    system("cls");
    cout << "Update successful." << endl;
    system("pause");
}

void Admin::menu_option()
{
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "         Manager Mode\n"
        "------------------------------\n";

    MenuOption mainMenu[] =
    {
        {'1', "Update the rental price", std::bind(&Admin::update_room_price, &manager)},
        {'2', "Update Foods and Drinks", std::bind(&Admin::menu_foods_and_drinks, &manager)},
        {'3', "Update new rooms", std::bind(&Admin::add_rooms, &manager)},
        {'0', "Return"},
    };

    while (1)
    {
        if (display_menu_option(menu_title, mainMenu, 4))
            break;
    }
}

void Admin::menu_foods_and_drinks() const {
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "   Foods And Drinks Setting\n"
        "------------------------------\n";

    MenuOption mainMenu[] =
        {
            {'1', "Add a new food into the menu", std::bind(&Admin::add_new_food, &manager)},
            {'2', "Update the food in the menu", std::bind(&Admin::update_food_by_id, &manager)},
            {'3', "Remove the food in the menu", std::bind(&Admin::delete_food_by_id, &manager)},
            {'4', "Show the menu", std::bind(&Admin::display_foods, &manager)},
            {'0', "Return"},
        };

    while (1)
    {
        if (display_menu_option(menu_title, mainMenu, 5))
            break;
    }
}

void Operator::room_selection(){
    while(1){
        const char *menu_title =
            "\n"
            "------------------------------\n"
            "          Hotel ABC\n"
            "------------------------------\n";
        system("cls");
        cout << menu_title << endl;
        this->display_rooms();
        cout << endl << "Enter room number(Enter'0' to return): ";
        selectedRoom = handleWrongInput();
        if(selectedRoom == 0)
            return;
        else{
            this->selected_room_menu();
        }
    }
}

void Operator::selected_room_menu(){
    while (1)
    {
        system("cls");
        cout << "\n"
                "------------------------------\n"
                "         Room "
             << selectedRoom << "\n"
             << "------------------------------\n";
        MenuOption mainMenu[] =
            {
                {'1', "Check out", std::bind(&Operator::check_out, &staff)},
                {'2', "Order foods and drinks", std::bind(&Operator::order_foods_menu, &staff)},
                {'0', "Return"},
            };

        if(database1.getRoomStatus(selectedRoom) == FREE){
            mainMenu[0] = {'1', "Check in", std::bind(&Operator::check_in, &staff)};
        }

        cout << endl;
        for (size_t i = 0; i < 3; ++i)
        {
            std::cout << mainMenu[i].choice << ". " << mainMenu[i].selectionText << "\n";
        }
        cout << "Enter your choice: ";
        char choice;
        cin >> choice;
        if (choice == '0')
        {
            return;
        }
        for (size_t i = 0; i < 3; ++i)
        {
            if (choice == mainMenu[i].choice)
            {
                (mainMenu[i].processingFunction)();
                break;
            }
        }
    }
}

void Operator::check_in(){
    system("cls");
    cout << "\n"
            "------------------------------\n"
            "      Check In Room "
         << selectedRoom << "\n"
         << "------------------------------\n";
    MenuOption mainMenu[] =
        {
            {'1', "Rent a new room by hours"},
            {'2', "Rent a new room overnight"},
            {'0', "Return"},
        };

    cout << endl;
    for (size_t i = 0; i < 3; ++i)
    {
        std::cout << mainMenu[i].choice << ". " << mainMenu[i].selectionText << "\n";
    }
    cout << "Enter your choice: ";
    char choice;
    cin >> choice;
    if (choice == '0')
    {
        return;
    }

    switch (choice)
    {
    case '1':
    {
        database1.setRoomStatus(selectedRoom, HOURLY_RENTAL);
        break;
    }
    case '2':
    {
        database1.setRoomStatus(selectedRoom, OVERNIGHT_RENTAL);
        break;
    }
    }

    cout << endl << "Enter the start hour (0 - 23h): ";
    uint8_t hour = (uint8_t)handleWrongInput();
    cout << endl
         << "Enter the start day (1 - 31): ";
    uint8_t day = (uint8_t)handleWrongInput();
    cout << endl
         << "Enter month (1 - 12): ";
    uint8_t month = (uint8_t)handleWrongInput();
    cout << endl
         << "Enter year: ";
    unsigned int year = handleWrongInput();
    database1.setStartDate(selectedRoom, {hour, day, month, (unsigned int)year});
    cout << endl << "Rent successful\n";
    system("pause");
}

void Operator::check_out() const{
    system("cls");
    cout << "\n"
            "------------------------------\n"
            "      Check Out Room "
         << selectedRoom << "\n"
         << "------------------------------\n";
    
    switch (database1.getRoomStatus(selectedRoom))
    {
        case HOURLY_RENTAL:
            cout << "You're renting this room by hours\n";
            break;
        
        case OVERNIGHT_RENTAL:
            cout << "You're renting this room overnight\n";
            break;
    }  

    cout << "Enter the end hour: ";
    uint8_t hour = (uint8_t)handleWrongInput();
    cout << "\nEnter the end day: ";
    uint8_t day = (uint8_t)handleWrongInput();
    cout << "\nEnter month: ";
    uint8_t month = (uint8_t)handleWrongInput();
    cout << "\nEnter year: ";
    unsigned int year = handleWrongInput();

    system("cls");
    cout << "\n"
            "------------------------------\n"
            "      Check Out Room "
         << selectedRoom << "\n"
         << "------------------------------\n";

    switch (database1.getRoomStatus(selectedRoom))
    {
    case HOURLY_RENTAL:
            cout << "You're renting this room by hours\n";
            break;

    case OVERNIGHT_RENTAL:
            cout << "You're renting this room overnight\n";
            break;
    }

    unsigned int roomRentalBill {0};
    if (database1.getRoomStatus(selectedRoom) > HOURLY_RENTAL)
    {
        roomRentalBill = database1.getOvernightPrice() * (((database1.getStartDate(selectedRoom) - (Date){hour, day, month, (unsigned int)year}) / 24) + 1);
    }
    else
    {
        roomRentalBill = database1.getHourlyPrice() * (database1.getStartDate(selectedRoom) - (Date){hour, day, month, (unsigned int)year});
    }

    cout << "\nRoom rental start date: " << (unsigned int)database1.getStartDate(selectedRoom).hour << "h - " << (unsigned int)database1.getStartDate(selectedRoom).day << "/"
         << (unsigned int)database1.getStartDate(selectedRoom).month << "/" << database1.getStartDate(selectedRoom).year;
    cout << "\nRoom rental end date: " << (unsigned int)hour << "h - " << (unsigned int)day << "/" << (unsigned int)month << "/" << year;
    cout << "\nThe room rent bill: " << roomRentalBill / 1000 << "." << setw(3) << setfill('0') << roomRentalBill % 1000 << setfill(' ') << " VND" << "\n\n";

    unsigned int foodBill = database1.show_bill(selectedRoom);
    cout << "\nThe service bill: " << foodBill / 1000 << "." << setw(3) << setfill('0') << foodBill % 1000 << setfill(' ') << " VND" << endl;
    cout << "\nThe total bill: " << (foodBill + roomRentalBill) / 1000 << "." << setw(3) << setfill('0') << (foodBill + roomRentalBill) % 1000 << setfill(' ') << " VND";
    cout << "\n\n1. Pay \n0. Return\nEnter your choice: ";
    uint8_t choice = (uint8_t)handleWrongInput();
    switch (choice)
    {
    case 1:
        {
            database1.setRoomStatus(selectedRoom, FREE);
            return;
        }    
    case 0:
        {
            return;
        }
    }
}

void Operator::order_new_food(){
    system("cls");
    cout << "\n"
            "------------------------------\n"
            "          Take Order                \n"
         << "------------------------------\n";
    unsigned int id;
    unsigned int quantity;

    database1.show_bill(selectedRoom);
    cout << endl
         << "Enter food ID: ";
    id = handleWrongInput();
    cout << endl
         << "Enter quantity: ";
    quantity = handleWrongInput();

    database1.take_order(selectedRoom, id, quantity);

    system("cls");
    cout << "Order food successful." << endl;
    cout << "1. Order a different kind of food" << endl;
    cout << "0. Return" << endl;
    cout << "Enter your choice: ";
    char choice;
    cin >> choice;
    if (choice == '1')
    {
        this->order_new_food();
    }
}

void Operator::order_foods_menu(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "       Foods And Drinks\n"
        "------------------------------\n";

    MenuOption mainMenu[] =
        {
            {'1', "Order foods and drinks", std::bind(&Operator::order_new_food, &staff)},
            {'2', "Update the food in the order", std::bind(&Operator::order_new_food, &staff)},
            {'3', "Remove the food in the order", std::bind(&Operator::remove_food_in_order, &staff)},
            {'4', "Show the menu", std::bind(&Admin::display_foods, &manager)},
            {'5', "Show the bill", std::bind(&Operator::show_food_bill, &staff)},
            {'0', "Return"},
        };

    while (1)
    {
        if (display_menu_option(menu_title, mainMenu, 6))
            break;
    }
}

void Operator::remove_food_in_order(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "     Remove Food In Order\n"
        "------------------------------\n";
    unsigned int id;

    system("cls");
    cout << menu_title << endl;
    manager.display_foods();
    cout << endl
         << "Enter food ID: ";
    id = handleWrongInput();
    database1.remove_order(selectedRoom, id);
    system("cls");
    cout << "Delete successful." << endl;
    system("pause");
}

void Operator::display_rooms() const{
    cout << "|  Rooms|";
    for (auto room : database1.getRooms())
    {
        cout << setw(3) << right << room.getId() << "|";
    }
    cout << endl
         << "|  State|";
    for (auto room : database1.getRooms())
    {
        cout << setw(3) << right << (room.getState() ? "x " : "") << "|";
    }
}

void Operator::show_food_bill() const{
    unsigned int foodBill = database1.show_bill(selectedRoom);
    cout << "\n\n"
         << "The service bill: " << foodBill / 1000 << "." << setw(3) << setfill('0') << foodBill % 1000 << setfill(' ') << " VND"
         << endl;
    system("pause");
}

unsigned int handleWrongInput()
{
    unsigned int num;
    while (!(std::cin >> num)) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    return num;
}

bool display_menu_option(const char *menu_title, MenuOption mainMenu[], unsigned int quantitySelections)
{
    system("cls");
    cout << menu_title;
    for (size_t i = 0; i < quantitySelections; ++i)
    {
        std::cout << mainMenu[i].choice << ". " << mainMenu[i].selectionText << "\n";
    }
    cout << "Enter your choice: ";
    char choice;
    cin >> choice;
    if (choice == '0')
    {
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

void home_menu(){
    const char *menu_title =
        "\n"
        "------------------------------\n"
        "    Hotel Management System\n"
        "------------------------------\n";

    MenuOption mainMenu[] =
        {
            {'1', "Manager mode", std::bind(&Admin::menu_option, &manager)},
            {'2', "Staff mode", std::bind(&Operator::room_selection, &staff)},
        };

    while (1)
    {
        if (display_menu_option(menu_title, mainMenu, 2))
            break;
    }
}

int main(){
    home_menu();
    return 0;
}