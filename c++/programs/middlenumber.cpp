#include <iostream>
#include <vector>
using namespace std;

int main() {
  int s;
  int l;
  int e;
  int in;
  cin >> s;
  vector<int> list(s);

  if (s > 10) {
    cout << "Too many numbers" << endl;
  } else {
    for (int i = 0; i < list.size(); i++) {
      cin >> in;
      list.push_back(in);
    }

    for (int i = 0; i < list.size(); i++) {
      if (list.at(i) < 0) {
        l = i - 1;
        break;
      }
    }
  }
  e = (l / 2);
  cout << "Middle item: " << list.at(e) << endl;

  return 0;
}
