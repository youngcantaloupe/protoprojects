#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

bool isPalindrome(const string &str) {
  int left = 0;
  int right = str.length() - 1;

  while (left < right) {

    while (left < right && !isalnum(str[left])) {
      left++;
    }
    while (left < right && !isalnum(str[right])) {
      right--;
    }

    if (tolower(str[left]) != tolower(str[right])) {
      return false;
    }

    left++;
    right--;
  }

  return true;
}

int main() {
  string input;
  getline(cin, input);

  if (isPalindrome(input)) {
    cout << "palindrome: " << input << endl;
  } else {
    cout << "not a palindrome: " << input << endl;
  }

  return 0;
}

/*for (int i = str1.length() - 1; i >= 0; i--) {*/
/*  str2[j] = str1.at(i);*/
/**/
/*  cout << str2[5];*/
/*  // cout << str2[j] << endl;*/
/*  cout << str2 << endl;*/
/*  j++;*/
/*}*/
/**/
/*cout << str2.length() << endl;*/
/*cout << str2 << endl;*/
/**/
/*string input;*/
/*getline(cin, input);*/
/*bool pal = true;*/
/*int l = 0;*/
/*int r = input.length() - 1;*/
/**/
/*while (l < r) {*/
/*  while (l < r && !isalnum(input[l])) {*/
/*    l++;*/
/*  }*/
/*  while (l < r && !isalnum(input[r])) {*/
/*    r--;*/
/*  }*/
/*  if (input[l] != input[r]) {*/
/*    pal = false;*/
/*  }*/
/**/
/*  l++;*/
/*  r++;*/
/*}*/
/*if (pal)*/
/*  cout << "palindrome: " << input << endl;*/
/*else*/
/*  cout << "not a palindrome: " << input << endl;*/
