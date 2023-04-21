#include <iostream>
#include <string>

class Book {
public:
    Book(std::string title, std::string author, int yearOfPublication, int quantity)
        : title(title), author(author), yearOfPublication(yearOfPublication), quantity(quantity) {}

    void printBookInfo() const;
    void borrowBook();
    void returnBook();
private:
    std::string title;
    std::string author;
    int yearOfPublication;
    int quantity;
};

void Book::printBookInfo() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Year of publication: " << yearOfPublication << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
}

void Book::borrowBook() {
    if (quantity > 0) {
        --quantity;
        std::cout << "Book borrowed successfully." << std::endl;
    } else {
        std::cout << "Sorry, this book is currently out of stock." << std::endl;
    }
}

void Book::returnBook() {
    ++quantity;
    std::cout << "Book returned successfully." << std::endl;
}

int main() {
    Book myBook("Calculus", "Nguyen Xuan Thao", 2000, 2);
    myBook.printBookInfo();
    myBook.borrowBook();
    myBook.borrowBook();
    myBook.borrowBook();
    myBook.returnBook();
    return 0;
}
