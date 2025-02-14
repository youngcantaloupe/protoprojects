#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void ParseFile(const string &file, vector<string> &vec, int &c) {
  int depth = 0;
  int maxDepth = 3;

  if (depth > maxDepth) {
    cout << "Max recursion depth reached for file: " << file << endl;
    return;
  }

  ifstream inFS;

  //  cout << "Opening " << file << std::endl;

  inFS.open(file);

  if (!inFS.is_open()) {
    cout << "Error opening file: " << file << "." << std::endl;
    return;
  }

  // cout << "Parsing data" << std::endl;

  string word;
  inFS >> word;

  while (!inFS.fail()) {
    if (!word.empty() && word.at(0) == '@') {
      string nestedFile = word.substr(1);
      ParseFile(nestedFile, vec, c);
      inFS >> word;
      ++c;
    }
    vec.push_back(word);
    // cout << word << std::endl;
    inFS >> word;
    ++c;
  }

  if (!inFS.eof()) {
    cout << "Error before EOF" << std::endl;
  }

  // cout << "Closing " << file << std::endl;
  inFS.close();
}

int main() {

  // if (argc < 4) {
  // cerr << "Invalid arguments" << endl;
  // return 1;
  //}
  string aout;
  string starting;
  string file;
  string ending;

  cin >> aout;
  cin >> starting;
  cin >> file;
  cin >> ending;

  vector<string> vecStr = {};
  int numWords = 0;

  ParseFile(file, vecStr, numWords);

  cout << numWords << " items:\n" << std::endl;
  cout << starting << endl;
  for (const auto &word : vecStr) {
    cout << word << endl;
  }
  cout << ending << endl;

  return 0;
}
