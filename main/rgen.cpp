#include<modele.h>
#include<vector>
#include<tuple>

vector<tuple<int, int>> coord = {{0,0},{0,1}, {0,2}, {0,3}, {1,0}, {1,1}, {1,2}, {1,3}, {2,0}, {2,1}, {2,2}, {2,3}, {3,0}, {3,1}, {3,2}, {3,3}};
void rgen(Plateau plateau){
  int n = coord.size();
  for(int i = 0; i<n-1; i++){
    int j = i + (rand()%(n-i));
    const tuple<int,int> temp = coord[i];
    coord[i] = coord[j];
    coord[j] = temp;
  }
  for(int i=0; i<n; i++){
    int a = get<0>(coord[i]);
    int b = get<1>(coord[i]);
    int value = tireDeuxOuQuatre();
    if(plateau[a][b] == 0){
      plateau[a][b] = value;
      break;
    }
  }
}
