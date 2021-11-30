#include <iostream>

void affichePlateau(Plateau plateau){
  string res = "";
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
  c = std::to_string(n).length();
  for(int i=0; i<=17+4*(c-1); i++){
    res = res.append(s);
  }
  res = res.append("\n");
  int x = 0;
  for(int i = 0; i<=3; i++){
    res = res.append("* ");
    for(int j = 0; j<=3; j++){
      res = res.append(to_string(plateau[i][j]);
      res = res.append(" *");
    }
    res.append("\n");
  }
}