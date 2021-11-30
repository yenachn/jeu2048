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
  for(int i=0; i<=17+4*(c-1); i++){
    fulline.push_back(s);
  }
  fulline.push_back('\n');
  string res = fulline;
  for(int i = 0; i<=3; i++){
    res = res.append("* ");
    for(int j = 0; j<=3; j++){
      res = res.append(to_string(plateau[i][j]));
      res = res.append(" *");
    }
    res = res.append(fulline);
  }
  return res;
};

int main(){
  Plateau test = plateauVide();
  test[0][1] = 12;
  string res = affichePlateau(test);
  cout << res ;
  return 0;
}

