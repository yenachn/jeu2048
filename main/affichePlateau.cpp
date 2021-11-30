#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<vector<int>> Plateau;

Plateau plateauVide(){
  Plateau init;
  init = Plateau(4);
  for (int i = 0; i <= 3; i++){
    init[i] = {0, 0, 0, 0};
  };
  return init;
};

string empty(int i){
  string res = "";
  for(int j=0;j<i;j++){
    res.push_back(' ');
  }
  return res;
}

string affichePlateau(Plateau plateau){
  string fulline = "\n";
  char s = '*';
  int n = 0;
  for(int i = 0; i<=3; i++){
    for(int j = 0; j<=3; j++){
      if(plateau[i][j]>n){
        n = plateau[i][j];
      }
    }
  }
  int c;
  c = to_string(n).length();
  cout << c << endl;
  for(int i=0; i<5+4*(c); i++){
    fulline.push_back(s);
  }
  fulline.push_back('\n');
  string res = fulline;
  for(int i = 0; i<=3; i++){
    res = res.append("*");
    for(int j = 0; j<=3; j++){
      string cur = to_string(plateau[i][j]);
      int before = (c-cur.length())/2;
      int after = c-(before+cur.length());
      res.append(empty(before));
      res = res.append(cur);
      res.append(empty(after));
      res = res.append("*");
    }
    res = res.append(fulline);
  }
  return res;
};

int main(){
  Plateau test = plateauVide();
  test[0][1] = 16;
  test[3][3] = 4096;
  string res = affichePlateau(test);
  cout << res ;
  return 0;
}

