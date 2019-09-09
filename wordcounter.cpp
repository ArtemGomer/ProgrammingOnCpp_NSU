//
// Created by Gomer on 09.09.2019.
//

#include "wordcounter.h"

void frequency::isEmpty(string &strKey, map<string, int> & mp) {
  if (!strKey.empty()) {
    mp[strKey]++;
    count++;
    strKey.clear();
  }
}

frequency::frequency() {
  count = 0;
}

void frequency::countFrequency() {
  ifstream fin("in.txt");
  string str, strKey;
  map<string, int> mp;
  map<string, int>::iterator it;
  while (getline(fin, str)) {
    int length = str.length();
    for (int i = 0; i < length; i++) {
      if (isdigit(str[i]) || isalpha(str[i])) {
        strKey += str[i];
      } else {
        isEmpty(strKey, mp);
      }
    }
  }
  isEmpty(strKey, mp);
  for (pair<string, int> pair : mp) {
    items.emplace_back(pair.second, pair.first);
  }
  fin.close();
}

void frequency::writeFrequency(){
  ofstream fout{"out.csv"};
  sort(items.begin(), items.end());
  reverse(items.begin(), items.end());
  for (const pair<int, string> & pair : items){
    fout << pair.second + ";" + to_string(pair.first) + ";" + to_string(pair.first/ (float)count * 100) + "\n";
  }
  fout.close();
}