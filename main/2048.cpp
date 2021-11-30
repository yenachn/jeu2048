#include <2048.cpp>

int main(){
    srand (time(NULL));
    Plateau init = plateauInitial();
    while(!estTermine(init)){
      
      if(estGagnant(init)){
        cerr << "Vous avez gagné, Bravo !" << endl;
      }
    }