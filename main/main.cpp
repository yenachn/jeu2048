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

bool win_game(){
  for (int i = 0; i<=3; i++){
    for (int j = 0; j <= 3; j++){
      if (minit[i][j] == 2048){
        return true;
      }
    }
  }
  return false;
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

vector<vector<int>> rgen(){
  /*
  method 1. for loop that returns all the (i, j) coordinates saved in form of tuples that contain the number 0, then a random sort that chooses an arbitrary tuple from the set.
  method 2. while loop to choose a random (i, j) for i and j in {||0, 3||}, then check if the number contained is 0. if not, choose another (i, j).
  */
}

int main(){
}