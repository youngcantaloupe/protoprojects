#ifndef BITS_H
#define BITS_H

#include <bitset>
#include <cassert>
#include <iostream>

class Bits {
  using IType = unsigned long long; // Change type here
  enum { NBITS = sizeof(IType) * 8 };
  IType bits = 0;

public:
  // Constructors
  Bits() = default;
  Bits(IType n) : bits(n) {}

  ~Bits() = default;

  // Static func memeber
  static int size() { return NBITS; }

  // Member functions
  bool at(int pos) const {
    assert(0 <= pos && pos < NBITS);
    return bits & (IType(1) << pos);
  }

  void set(int pos) {
    assert(0 <= pos && pos < NBITS);
    bits |= (IType(1) << pos);
  }

  void set() { bits = ~IType(0); }

  void reset(int pos) {
    assert(0 <= pos && pos < NBITS);
    bits &= ~(IType(1) << pos);
  }

  void reset() { bits = 0; }

  void assign(int pos, bool val) {
    if (val)
      set(pos);
    else
      reset(pos);
  }

  void assign(IType n) { bits = n; }

  void toggle(int pos) {
    assert(0 <= pos && pos < NBITS);
    bits ^= (IType(1) << pos);
  }

  void toggle() { bits = ~bits; }

  void shift(int n) {
    if (n > 0) {
      bits >>= n;
    } else if (n < 0) {
      bits <<= -n;
    }
  }

  void rotate(int n) {
    n = n % NBITS;
    if (n > 0) {
      bits = (bits >> n) | (bits << (NBITS - n));
    } else if (n < 0) {
      n = -n;
      bits = (bits << n) | (bits >> (NBITS - n));
    }
  }

  int ones() const {
    int count = 0;
    IType temp = bits;
    while (temp) {
      count += temp & 1;
      temp >>= 1;
    }
    return count;
  }

  int zeroes() const { return NBITS - ones(); }

  IType to_int() const { return bits; }

  // Friendlies
  friend bool operator==(const Bits &b1, const Bits &b2) {
    return b1.bits == b2.bits;
  }

  friend bool operator!=(const Bits &b1, const Bits &b2) {
    return b1.bits != b2.bits;
  }

  friend std::ostream &operator<<(std::ostream &os, const Bits &b) {
    return os << std::bitset<NBITS>(b.bits);
  }
};

#endif
