#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
using std::size_t;

template <typename T> class Vector {
  enum { CHUNK = 10 };
  size_t capacity; // Size of the current array (in use or not)
  size_t n_elems;  // Number spaces in use, starting from pos 0
  T *data_ptr;     // Pointer to the heap array
  void grow();

public:
  // Object Mgt.
  Vector();
  Vector(const Vector &v);            // Copy constructor
  Vector &operator=(const Vector &v); // Copy assignment operator
  ~Vector();

  // Helpers
  void checkEmpty() const;            // Checks if obj. is empty
  void checkPosition(size_t p) const; // Checks if index is valid

  // Accessors
  T front() const;        // Return the int in position 0, if any
  T back() const;         // Return last element (position n_elems-1)
  T at(size_t pos) const; // Return element in position "pos" (0-based)
  size_t size() const;    // Return n_elems
  bool empty() const;     // Return n_elems == 0

  // Mutators
  T &operator[](size_t pos); // Same as at but no bounds checking
  void push_back(T item);    // Append a new element at the end of the array
  void pop_back();           // --n_elems (nothing else; returns nothing)
  void erase(size_t pos);    // Remove item in pos and shuffles elems left
  void insert(size_t pos, T item); // Shuffle elems right insert item at pos
  void clear();                    // if n_elems = 0 no cap change

  // Iterators
  T *begin(); // Return a pointer to 1st element, or nullptr if n_elems == 0
  T *end();   // Return pointer to n_elem, or nullptr if n_elems == 0

  // Comparators
  bool operator==(const Vector &v) const;
  bool operator!=(const Vector &v) const;
};

#include "Vector.tpp"

#endif
