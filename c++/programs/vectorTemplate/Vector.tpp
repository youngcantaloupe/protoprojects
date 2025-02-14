#include "Vector.h"
#include <iostream>
#include <stdexcept>

template <typename T>
// CONSTRUCTORS
Vector<T>::Vector() : capacity(CHUNK), n_elems(0), data_ptr(new T[capacity]) {}

template <typename T>
Vector<T>::Vector(const Vector &v) : capacity(v.capacity), n_elems(v.n_elems) {
  data_ptr = new T[capacity];
  for (size_t i = 0; i < v.n_elems; ++i) {
    data_ptr[i] = v.data_ptr[i];
  }
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  if (this == &v)
    return *this;

  delete[] data_ptr;

  capacity = v.capacity;
  n_elems = v.n_elems;
  data_ptr = new T[capacity];

  for (size_t i = 0; i < n_elems; ++i) {
    data_ptr[i] = v.data_ptr[i];
  }
  return *this;
}

template <typename T> 
Vector<T>::~Vector() { delete[] data_ptr; }

template <typename T> 
void Vector<T>::grow() {
  size_t new_capacity = (capacity * 1.6) + CHUNK;
  T *new_data_ptr = new T[new_capacity];

  for (size_t i = 0; i < n_elems; ++i) {
    new_data_ptr[i] = data_ptr[i];
  }

  delete[] data_ptr;
  data_ptr = new_data_ptr;
  capacity = new_capacity;
  //std::cout << "grow" << std::endl;
}

// HELPERS
template <typename T> 
void Vector<T>::checkEmpty() const {
  if (empty())
    throw std::range_error("Error: Empty vector.");
}

template <typename T> 
void Vector<T>::checkPosition(size_t p) const {
  if (p > n_elems)
    throw std::range_error("Error: Invalid index. Cannot find element.");
}

// ACCESSORS
template <typename T> 
T Vector<T>::front() const {
  checkEmpty();
  return data_ptr[0];
}

template <typename T> 
T Vector<T>::back() const {
  checkEmpty();
  return data_ptr[n_elems - 1];
}

template <typename T> 
T Vector<T>::at(size_t pos) const {
  checkEmpty();
  checkPosition(pos);
  return data_ptr[pos];
}

template <typename T> 
size_t Vector<T>::size() const { return n_elems; }

template <typename T> 
bool Vector<T>::empty() const {
  return (n_elems == 0) ? true : false;
}

// MUTATORS
template <typename T> 
T &Vector<T>::operator[](size_t pos) {
  return data_ptr[pos];
}

template <typename T> 
void Vector<T>::push_back(T item) {
  if (n_elems == capacity)
    grow();
  data_ptr[n_elems] = item;
  ++n_elems;
}

template <typename T> 
void Vector<T>::pop_back() {
  checkEmpty();
  data_ptr[n_elems - 1] = 0; // not needed, decrementing already excludes
  --n_elems;
}
template <typename T> 
void Vector<T>::erase(size_t pos) {
  checkEmpty();
  checkPosition(pos);
  for (size_t i = pos; i < n_elems - 1; ++i) {
    data_ptr[i] = data_ptr[i + 1];
  }
  // data_ptr[n_elems - 1] = 0; // not needed, value here already excluded
  --n_elems;
}

template <typename T> 
void Vector<T>::insert(size_t pos, T item) {
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

template <typename T> 
void Vector<T>::clear() {
  for (size_t i = 0; i < n_elems - 1; ++i) {
    data_ptr[i] = 0;
  }
  n_elems = 0;
}

// ITERATORS
template <typename T> 
T *Vector<T>::begin() { return (n_elems > 0) ? data_ptr : nullptr; }

template <typename T> 
T *Vector<T>::end() { return (n_elems > 0) ? data_ptr + n_elems : nullptr; }

// COMPARATORS
template <typename T> 
bool Vector<T>::operator==(const Vector &v) const {
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
template <typename T> 
bool Vector<T>::operator!=(const Vector &v) const { return !(*this == v); }
