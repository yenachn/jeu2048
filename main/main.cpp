#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>
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
      if (minit[i][j] == minit[i][j+1] || minit[i][j] == minit[i+1][j] || minit[i][j] == 0){
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

bool cont_game(){
  /* input y/n */
  if(/*input == y*/){
    return true;
  }
  return false;
}

void arrow_right(){
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
}

void arrow_left(){
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
}

void arrow_up(){
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
}

void arrow_down(){
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
}

vector<tuple<int, int>> coord;
coord = {(0,0), (0,1), (0,2), (0,3), (1,0), (1,1), (1,2), (1,3), (2,0), (2,1), (2,2), (2,3), (3,0), (3,1), (3,2), (3,3)};
void rgen(){
  int n = coord.size();
  for(int i = 0; i<n-1; i++){
    int j = i + (rand()%(n-i));
    coord[i], coord[j] = coord[j], coord[i];
  }
  for(int i=0; i<n; i++){
    int a = get<0>(coord[i]);
    int b = get<1>(coord[i]);
    int value = (1 + (rand() % 2))*2;
    if(minit[a][b] == 0){
      minit[a][b] = value;
      break;
    }
  }
}

void input(){

}

int main(){
    srand (time(NULL));
    while(!end_game){
      if(win_game){
        /* add a marker on top corner of game */
        if(!cont_game){
          end_game=true;
        }
      }
      input();
    }
    return 0;
}