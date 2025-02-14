#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void ParseFile(const std::string &file, std::vector<std::string> &vec, int &c) {
  std::ifstream inFS;

  //  std::cout << "Opening " << file << std::endl;

  inFS.open(file);

  if (!inFS.is_open()) {
    std::cout << "Error opening file: " << file << "." << std::endl;
    return;
  }

  // std::cout << "Parsing data" << std::endl;

  std::string word;
  inFS >> word;

  while (!inFS.fail()) {
    if (!word.empty() && word.at(0) == '@') {
      std::string nestedFile = word.substr(1);
      ParseFile(nestedFile, vec, c);
      inFS >> word;
      ++c;
    }
    vec.push_back(word);
    // std::cout << word << std::endl;
    inFS >> word;
    ++c;
  }

  if (!inFS.eof()) {
    std::cout << "Error before EOF" << std::endl;
  }

  // std::cout << "Closing " << file << std::endl;
  inFS.close();
}

int main(int argc, char *argv[]) {

  if (argc < 4) {
    std::cerr << "Invalid arguments" << std::endl;
    return 1;
  }

  std::string starting;
  std::string file;
  std::string ending;
  std::vector<std::string> vecStr = {};
  int numWords = 0;

  starting = argv[1];
  file = argv[2];
  ending = argv[3];

  ParseFile(file, vecStr, numWords);

  std::cout << numWords << " items:\n" << std::endl;
  std::cout << starting << std::endl;
  for (size_t i = 0; i < vecStr.size(); ++i) {
    std::cout << vecStr[i] << std::endl;
  }
  std::cout << ending << std::endl;

  return 0;
}
