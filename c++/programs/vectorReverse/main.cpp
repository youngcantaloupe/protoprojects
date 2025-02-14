#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int size;
  cin >> size;
  vector<int> userInts(size);
  for (int i = 0; i < size; i++) {
    cin >> userInts[i];
  }
  reverse(userInts.begin(), userInts.end());
  for (int i = 0; i < userInts.size(); i++) {
    cout << userInts.at(i) << ", ";
  }
  cout << endl;
  return 0;
}
