#include <iostream>

void affichePlateau(){

  char s = '*';
  int n = 0;
  for(int i = 0; i<=3; i++){
    for(int j = 0; j<=3; j++){
      if(init[i][j]>n){
        n = init[i][j];
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
      cout << init[i][j];
      cout << " *";
    }
    cout << endl;
  }
}