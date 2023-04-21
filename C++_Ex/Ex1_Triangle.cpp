#include <iostream>
#include <cmath>

//2D point class
class Point {
private:
    double x;
    double y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    double getX();
    double getY();
};

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

//Calculate distance or area of triangle class
class Calc {
private:
    double distance(Point a, Point b);
    Point p1;
    Point p2;
    Point p3;
public:
    double result;
    //calc area of triangle
    Calc(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3){
        double a = distance(p1, p2);
        double b = distance(p2, p3);
        double c = distance(p3, p1);
        double s = (a + b + c) / 2;
        result = sqrt(s * (s - a) * (s - b) * (s - c));
    }
    //calc distance
    Calc(Point p1, Point p2) : p1(p1), p2(p2) {
        result = distance(p1, p2);
    }
};

double Calc::distance(Point a, Point b) {
        return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2));
}

int main() {
    Point p1(0, 0);
    Point p2(0, 1);
    Point p3(1, 0);
    Calc t(p1, p2, p3);
    std::cout << "Result: " << t.result << std::endl;
}
