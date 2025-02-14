#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
using std::size_t;

class Vector {
    enum { CHUNK = 10 };
    size_t capacity; // size of the current array (in use or not)
    size_t n_elems;  // number spaces in use, starting from pos 0
    int *data_ptr;   // pointer to the heap array
    void grow();

  public:
    // OBJECT MGT.
    Vector();
    Vector(const Vector &v);            // copy Constructor
    Vector &operator=(const Vector &v); // copy assignment operator
    ~Vector();

    // HELPERS
    void checkEmpty() const;            // checks if obj. is empty
    void checkPosition(size_t p) const; // checks if index is valid

    // ACCESSORS
    int front() const;        // return the int in position 0, if any
    int back() const;         // return last element (position n_elems-1)
    int at(size_t pos) const; // return element in position "pos" (0-based)
    size_t size() const;      // return n_elems
    bool empty() const;       // return n_elems == 0

    // MUTATORS
    int &operator[](size_t pos);       // same as at but no bounds checking
    void push_back(int item);          // append a new element at the end of the array
    void pop_back();                   // --n_elems (nothing else; returns nothing)
    void erase(size_t pos);            // remove item in pos and shuffles elems left
    void insert(size_t pos, int item); // shuffle elems right insert item at pos
    void clear();                      // if n_elems = 0 no cap change

    // ITERATORS
    int *begin(); // return a pointer to 1st element, or nullptr if n_elems == 0
    int *end();   // return pointer to n_elem, or nullptr if n_elems == 0

    // COMPARATORS
    bool operator==(const Vector &v) const;
    bool operator!=(const Vector &v) const;
};

#endif
