#include "bits.h"
#include <iostream>

int main() {
  Bits b1;         // All bits set to 0
  Bits b2(0b1010); // Initialize with binary 1010

  std::cout << "Initial b1: " << b1 << std::endl;
  std::cout << "Initial b2: " << b2 << std::endl;

  // Set bit 1 in b1
  b1.set(1);
  std::cout << "After setting bit 1 in b1: " << b1 << std::endl;

  // Toggle bit 3 in b2
  b2.toggle(3);
  std::cout << "After toggling bit 3 in b2: " << b2 << std::endl;

  // Assign a new value to b1
  b1.assign(0b1111);
  std::cout << "After assigning 1111 to b1: " << b1 << std::endl;

  // Shift b2 left by 2
  b2.shift(-2);
  std::cout << "After shifting b2 left by 2: " << b2 << std::endl;

  // Rotate b1 right by 1
  b1.rotate(1);
  std::cout << "After rotating b1 right by 1: " << b1 << std::endl;

  // Compare b1 and b2
  if (b1 != b2) {
    std::cout << "b1 and b2 are different." << std::endl;
  }

  // Display number of set and reset bits in b1
  std::cout << "b1 has " << b1.ones() << " set bits and " << b1.zeroes()
            << " reset bits." << std::endl;

  b1.set(1);
  unsigned long long value = b1.to_int(); // Correct usage

  std::cout << "Value: " << value << std::endl;

  return 0;
}
