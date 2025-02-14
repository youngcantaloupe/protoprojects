#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Compare(const string &a, const string &b) {
  if (a.length() != b.length()) {
    return false;
  }

  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

int GetWordFrequency(const vector<string> &wordsList, string currWord) {
  int count = 0;
    bool match = false;
    
    for (size_t i = 0; i < wordsList.size(); ++i) {
        match = Compare(wordsList.at(i), currWord);
        if (match == true)
            count++;
    }
  
  return count;
}

int main() {
 //   vector<string> words = {"5", "hey", "Hi", "Mark", "hi", "mark"};

  int wordsLen;
  int count;
  vector<string> words;
  string search;
  string in;

  cin >> wordsLen;

  for (int i = 0; i < wordsLen; i++) {
    cin >> in;
    words.push_back(in);
  }

  for (size_t i = 0; i < words.size(); i++) {
    search = words.at(i);
    count = GetWordFrequency(words, search);
    cout << search << " - " << count << endl;
  }
}
