#include <cmath>
#include <iostream>

class Rectangle {
  public:
    Rectangle(double length, double width) : length(length), width(width) {}
    //Area of rectangle
    double area() {
        return length * width;
    }
    //perimeter of rectangle
    double perimeter() {
        return 2 * (length + width);
    }
    //diagonal of rectangle
    double diagonal() {
        return sqrt(length * length + width * width);
    }
    //squareChecking
    bool squareChecking(){
        return (length == width);
    }

  private:
    double length;
    double width;
};

int main(){
    Rectangle t(5, 6);
    std::cout << "area of rectangle: " << t.area();
    std::cout << "\nPerimeter of rectangle: " << t.perimeter();
    std::cout << "\ndiagonal of rectangle: " <<t.diagonal();
    std::cout << "\nsquareChecking of rectangle: " << t.squareChecking();
}
