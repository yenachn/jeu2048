#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>
#include <vector>
#include <curses.h>
#include "modele.cpp"

using namespace std;

int main() {
  startagain:
  srand(time(NULL));
  Plateau init = plateauInitial();
  Plateau old = plateauVide();
  int c;
  bool cont = false;
  initscr();
  keypad(stdscr, true);  
  printw("%d\n",estTermine(&init));
  printw("%d\n",estGagnant(&init));
  printw("Voici la configuration initiale, merci de presser une touche directionnelle.\nPour arrêter le jeu, pressez q à tout moment");
  printw(dessine(&init).c_str());
  loop:
  do {
      c = getch();
      if(c != 255)clear();
      old = init;
      deplacement(&init,c);
      if (old != init){
        rgen(&init);
      }
      printw(dessine(&init).c_str());
  } while (c != 113 && (cont || !estGagnant(&init)) && !estTermine(&init));
  if (estGagnant(&init))
  {
    printw("Vous avez gagné, BRAVO !, pour recommencer une partie, appuyez sur r, pour quitter, sur q.\nSi vous souhaitez continuer votre partie actuelle, cliquez sur n \'importe quelle autre touche");
    c = getch();
      switch(c) {
        case r:
          clear();
          goto startagain;
        case q:
          goto end;
        default:     
          clear();
          printw("partie en cours :\n");
          printw(dessine(&init).c_str());
          cont = true;     
          goto loop;
      }
    
  }
  if (estTermine(&init))
  {
    printw("partie terminée ! pour recommencer, pressez r, sinon, pressez n'importe quelle autre touche");
    c = getch();
    if(c==r)goto startagain;
    else goto end;
  }

  end:
  endwin();
  return 0;
}