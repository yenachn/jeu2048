#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> minit;

void start_game(){
  minit = vector<vector<int>>(4);
  for (int i = 0; i <= 3; i++){
    minit[i] = {0, 0, 0, 0};
  }
}

bool end_game(){
  for (int i = 0; i <= 2; i++){
    for(int j = 0; j <= 2; j++){
      if (minit[i][j] != minit[i][j+1] && minit[i][j] != minit[i+1][j]){
        return false;
      }
    }
  }
  return true;
}

vector<vector<int>> arrow_right(){
  for (int i = 0; i <= 2; i++){
    for (int j = 2; j >= 0; j--){
      if (minit[i][j] == 0){
        minit[i][j] = minit[i][j-1];
        minit[i][j-1] = 0;
      } else if (minit[i][j] == minit[i][j-1]){
        minit[i][j] = 2*minit[i][j];
        minit[i][j-1] = 0;
      }
    }
  }
  return minit;
}

vector<vector<int>> arrow_left(){
  for (int i = 0; i <= 2; i++){
    for (int j = 0; j <= 2; j++){
      if (minit[i][j] == 0){
        minit[i][j] = minit[i][j+1];
        minit[i][j+1] = 0;
      } else if (minit[i][j] == minit[i][j+1]){
        minit[i][j] = 2*minit[i][j];
        minit[i][j+1] = 0;
      }
    }
  }
  return minit;
}

vector<vector<int>> arrow_up(){
  for (int i = 0; i <= 2; i++){
    for (int j = 0; j <= 2; j++){
      if (minit[i][j] == 0){
        minit[i][j] = minit[i+1][j];
        minit[i+1][j] = 0;
      } else if (minit[i][j] == minit[i+1][j]){
        minit[i][j] = 2*minit[i][j];
        minit[i+1][j] = 0;
      }
    }
  }
  return minit;
}

vector<vector<int>> arrow_down(){
  for (int i = 2; i >= 0; i--){
    for (int j = 0; j <= 2; j++){
      if (minit[i][j] == 0){
        minit[i][j] = minit[i-1][j];
        minit[i-1][j] = 0;
      } else if (minit[i][j] == minit[i-1][j]){
        minit[i][j] = 2*minit[i][j];
        minit[i-1][j] = 0;
      }
    }
  }
  return minit;
}


int main(){
}