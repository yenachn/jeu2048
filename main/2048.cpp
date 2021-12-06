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
  int s;
  cout << "taille du plateau :";
  cin >> s;
  startagain:
  srand(time(NULL));
  Plateau init = plateauInitial(s);
  Plateau old = plateauVide(s);
  int c;
  bool cont = false;
  initscr();
  keypad(stdscr, true);  
  printw("%d\n",estTermine(&init,s));
  printw("%d\n",estGagnant(&init,s));
  printw("Voici la configuration initiale, merci de presser une touche directionnelle.\nPour arrêter le jeu, pressez q à tout moment");
  printw(dessine(&init,s).c_str());
  loop:
  do {
      c = getch();
      if(c != 255)clear();
      old = init;
      deplacement(&init,c,s);
      if (old != init){
        rgen(&init,s);
      }
      printw(dessine(&init,s).c_str());
  } while (c != 113 && (cont || !estGagnant(&init,s)) && !estTermine(&init,s));
  if (estGagnant(&init,s))
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
          printw(dessine(&init,s).c_str());
          cont = true;     
          goto loop;
      }
    
  }
  if (estTermine(&init,s))
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