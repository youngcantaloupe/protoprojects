#include "Vector.h"
#include <iostream>
#include <stdexcept>

// CONSTRUCTORS
Vector::Vector() : capacity(CHUNK), n_elems(0), data_ptr(new int[capacity]) {}

Vector::Vector(const Vector &v) : capacity(v.capacity), n_elems(v.n_elems) {
    data_ptr = new int[capacity];
    for (size_t i = 0; i < v.n_elems; ++i) {
        data_ptr[i] = v.data_ptr[i];
    }
}

Vector &Vector::operator=(const Vector &v) {

    if (this == &v)
        return *this;

    delete[] data_ptr;

    capacity = v.capacity;
    n_elems = v.n_elems;
    data_ptr = new int[capacity];

    for (size_t i = 0; i < n_elems; ++i) {
        data_ptr[i] = v.data_ptr[i];
    }
    return *this;
}

Vector::~Vector() { delete[] data_ptr; }

void Vector::grow() {
    size_t new_capacity = (capacity * 1.6) + CHUNK;
    int *new_data_ptr = new int[new_capacity];

    for (size_t i = 0; i < n_elems; ++i) {
        new_data_ptr[i] = data_ptr[i];
    }

    delete[] data_ptr;
    data_ptr = new_data_ptr;
    capacity = new_capacity;
    std::cout << "grow" << std::endl;
}

// HELPERS
void Vector::checkEmpty() const {
    if (empty())
        throw std::range_error("Error: Empty vector.");
}

void Vector::checkPosition(size_t p) const {
    if (p > n_elems)
        throw std::range_error("Error: Invalid index. Cannot find element.");
}

// ACCESSORS
int Vector::front() const {
    checkEmpty();
    return data_ptr[0];
}

int Vector::back() const {
    checkEmpty();
    return data_ptr[n_elems - 1];
}

int Vector::at(size_t pos) const {
    checkEmpty();
    checkPosition(pos);
    return data_ptr[pos];
}

size_t Vector::size() const { return n_elems; }
bool Vector::empty() const { return (n_elems == 0) ? true : false; }

// MUTATORS
int &Vector::operator[](size_t pos) { return data_ptr[pos]; }

void Vector::push_back(int item) {
    if (n_elems == capacity)
        grow();
    data_ptr[n_elems] = item;
    ++n_elems;
}

void Vector::pop_back() {
    checkEmpty();
    data_ptr[n_elems - 1] = 0; // not needed, decrementing already excludes
    --n_elems;
}

void Vector::erase(size_t pos) {
    checkEmpty();
    checkPosition(pos);
    for (size_t i = pos; i < n_elems - 1; ++i) {
        data_ptr[i] = data_ptr[i + 1];
    }
    data_ptr[n_elems - 1] = 0; // not needed, value here already excluded
    --n_elems;
}

void Vector::insert(size_t pos, int item) {
    checkEmpty();
    checkPosition(pos);
    if (n_elems == capacity)
        grow();

    for (size_t i = pos; i < n_elems; ++i) {
        data_ptr[i + 1] = data_ptr[i];
    }
    data_ptr[pos] = item;
    ++n_elems;
}

void Vector::clear() {
    for (size_t i = 0; i < n_elems - 1; ++i) {
        data_ptr[i] = 0;
    }
    n_elems = 0;
}

// ITERATORS
int *Vector::begin() { return (n_elems > 0) ? data_ptr : nullptr; }
int *Vector::end() { return (n_elems > 0) ? data_ptr + n_elems : nullptr; }

// COMPARATORS
bool Vector::operator==(const Vector &v) const {
    if (n_elems != v.n_elems) {
        return false;
    }

    for (size_t i = 0; i < n_elems; ++i) {
        if (data_ptr[i] != v.data_ptr[i]) {
            return false;
        }
    }
    return true;
}

// negate == output
bool Vector::operator!=(const Vector &v) const { return !(*this == v); }
