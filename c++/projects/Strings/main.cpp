#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int GetNumOfNonWSCharacters(const string &u) {
  int num = 0;
  int len = u.length();
  for (int i = 0; i < len; i++) {
    if (u.at(i) != ' ') {
      num++;
    }
  }
  return num;
}

int GetNumOfWords(const string &u) {
  int num = 0;
  //  int len = u.length();
  bool word = false;

  for (size_t i = 0; i < u.length(); ++i) {
    char c = u[i];

    if (isalpha(c) || (c == '\'' && i > 0 && isalpha(u[i - 1]))) {
      if (!word) {
        num++;
        word = true;
      }

    } else if (isspace(c) || ispunct(c)) {
      word = false;
    }
  }

  /*if (isalpha(u.at(0))) {*/
  /*  num++;*/
  /*}*/
  /*for (int i = 1; i < len; i++) {*/
  /*  if ((isalpha(u.at(i))) && (!isalpha(u.at(i - 1)))) {*/
  /*    num++;*/
  /*  }*/
  /*}*/
  return num;
}

int FindText(const string &find, const string &u) {
  int num = 0;
  auto x = u.find(find);

  while (x != string::npos) {
    num++;
    x = u.find(find, x + 1);
  }
  return num;
}

void ReplaceExclamation(string &u) {
  int len = u.length();
  for (int i = 0; i < len; i++) {
    if (u.at(i) == '!') {
      u.at(i) = '.';
    }
  }
}
void ShortenSpace(string &u) {
  auto x = u.find("  ");
  while (x != string::npos) {
    u.erase(x, 1);
    x = u.find("  ", x);
  }
}

void PrintMenu() {
  cout << "MENU" << endl;

  cout << "c - Number of non-whitespace characters" << endl;
  cout << "w - Number of words" << endl;
  cout << "f - Find text" << endl;
  cout << "r - Replace all !'s" << endl;
  cout << "s - Shorten spaces" << endl;
  cout << "q - Quit\n" << endl;
  cout << "Choose an option:" << endl;
}

void ExecuteMenu(char c, string u) {
  int num;
  string find;

  switch (c) {
  case 'c':
    num = GetNumOfNonWSCharacters(u);
    cout << "Number of non-whitespace characters: " << num << endl;
    break;
  case 'w':
    num = GetNumOfWords(u);
    cout << "Number of words: " << num << endl;
    break;
  case 'f':
    cout << "Enter a word or phrase to be found:";
    cin.ignore();
    getline(cin, find);
    num = FindText(find, u);
    cout << "\n" << "\"" << find << "\" " << "instances: " << num << endl;
    break;
  case 'r':
    ReplaceExclamation(u);
    cout << "Edited text: " << u << endl;
    break;
  case 's':
    ShortenSpace(u);
    cout << "Edited text: " << u << endl;
    break;
  case 'q':
    exit(0);
    break;
  default:
    cout << "hi";
  }
}

int main() {
  string uString;
  char uChoice;
  bool menu = true;

  cout << "Enter a sample text:" << endl;
  getline(cin, uString);
  cout << "\nYou entered: " << uString << endl;
  do {
    cout << "\n";
    PrintMenu();
    cin >> uChoice;
    switch (uChoice) {
    case 'c':
    case 'w':
    case 'f':
    case 'r':
    case 's':
      ExecuteMenu(uChoice, uString);
      // menu = false;
      break;
    case 'q':
      return 0;
      break;
    default:
      cout << "Unexpected error" << endl;
      return 0;
    }
  } while (menu == true);
  return 0;
}
