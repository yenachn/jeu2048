#include <iostream>

void affichePlateau(Plateau plateau){

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
    cout<< s;
  }
  cout << endl;
  int x = 0;
  for(int i = 0; i<=3; i++){
    cout << "* ";
    for(int j = 0; j<=3; j++){
      cout << plateau[i][j];
      cout << " *";
    }
    cout << endl;
  }
}