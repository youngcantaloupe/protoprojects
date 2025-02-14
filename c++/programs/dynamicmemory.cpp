#include <iostream>
using namespace std;

class Point {
    public:
    double x;
    double y; 
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

int main() {
    Point p1;
    Point p2(2.0, 3.0);
    Point *ptr = new Point(3.0, 4.0);
    
    
    cout << "p1.x      " << p1.x << endl;
    cout << "&p1.x     " << &p1.x << endl;
    cout << "p2.x      " << p2.x << endl;
    cout << "&p2.x     " << &p2.x << endl;
    cout << "&ptr      " << &ptr << endl;
    cout << "ptr       " << ptr << endl;
    cout << "(*ptr).x  " << (*ptr).x << endl;
    //cout << "*ptr.x  " << *ptr.x << endl;
    cout << "ptr->x:   " << ptr ->x << endl;

    //free up heap
    delete ptr;
    
return 0;
}
