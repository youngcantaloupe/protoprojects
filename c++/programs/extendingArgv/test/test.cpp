
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  ifstream inFS;
  string file;

  std::cout << "Opening " << argv[1] << std::endl;
  inFS.open(argv[1]);

  if (!inFS.is_open()) {
    std::cout << "Error opening file: " << argv[1] << "." << std::endl;
    return 1;
  }

  std::cout << "Parsing data" << std::endl;
  inFS >> file;

  while (!inFS.fail()) {
    std::cout << file << std::endl;
    inFS >> file;
  }

  if (!inFS.eof()) {
    std::cout << "Error before EOF" << std::endl;
  }

  std::cout << "Closing " << argv[1] << std::endl;

  inFS.close();

  return 0;
}
