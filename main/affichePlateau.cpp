#include <iostream>

void affichePlateau(Plateau plateau){

  string res = "";
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
  c = std::to_string(n).length();
  for(int i=0; i<=17+4*(c-1); i++){
    fulline.push_back(s);
  }
  fulline.push_back('\n');
  int x = 0;
  for(int i = 0; i<=3; i++){
    res = res.append("* ");
    for(int j = 0; j<=3; j++){
      res = res.append(to_string(plateau[i][j]));
      res = res.append(" *");
    }
    res = res.append(fulline);
  }
}