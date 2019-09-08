#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

class frequency{
 private:
  ifstream fin;
  ofstream fout;
  float count;
  map <string, int> mp;
  map <string, int> :: iterator it;
  string strKey;
  char str[257] = {0};
  void checkIn(){
    count++;
    if (strKey.length()){
      it = mp.find(strKey);
      if (it == mp.end()){
        mp.insert(make_pair(strKey, 1));
      }
      else{
        it->second++;
      }
      strKey.clear();
    }
  }

  void getFrequency(){
    while (fin.getline(str, 256)){
      int length = strlen(str);
      for (int i = 0; i < length; i++){
        if (!isalpha(str[i]) && !isdigit(str[i])){
          checkIn();
        }
        else{
          strKey += str[i];
        }
      }
    }
    checkIn();
  }

 public:
  frequency(char *in, char *out){
    count = 0;
    fin.open(in);
    fout.open(out);
  };
  ~frequency(){
    fin.close();
    fout.close();
  }
  void printFrequency(){
    getFrequency();
    for (it = mp.begin(); it != mp.end(); it++){
      fout << it->first << " " << it->second << " " << it->second / count * 100 << endl;
    }
  }
};

int main(int argc, char** argv)
{
  frequency f(argv[1], argv[2]);
  f.printFrequency();
}
