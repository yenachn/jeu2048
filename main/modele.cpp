#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>
#include <curses.h>
#include <fstream>
using namespace std;

typedef vector<vector<int> > Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 */


/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide(int s){
  Plateau init;
  init = Plateau(s);
  for (int i = 0; i < s; i++){
    init[i] = {};
    for(int j =0; j < s; j++){
      init[i].push_back(0);
    }
  }
  return init;
}

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre(){ 
  int i = rand()%10;
  if (i == 9) {
      return 4;
  }
  return 2;
}

vector<tuple<int, int>> coordGen(int s){

  vector<tuple<int, int>> coord;
  for(int i=0; i<s; i++){
    for(int j=0; j<s; j++){
      coord.push_back({i,j});
    }
  }
  return coord;
}


/** Rajoute avec soit un 2, soit un 4 avec les probabilités souhaitées d'apparition, dans l'une des cases vides.
 *  L'algorithme utilisé écrit se base sur l'algorithme de permutation aléatoire de Fisher-Yates
 *  @param plateau un Plateau
 *  @return un nouveau plateau res, correspondant à plateau dans lequel a été ajouté un 2 ou un 4 dans l'une des cases vides.
 **/
void rgen(Plateau *plateau){
  int s = size(*plateau);
  vector<tuple<int, int>> coord = coordGen(s);
  int n = coord.size();
  for(int i = 0; i<n-1; i++){
    int j = i + (rand()%(n-i));
    const tuple<int,int> temp = coord[i];
    coord[i] = coord[j];
    coord[j] = temp;
  }
  int value = tireDeuxOuQuatre();
  int a;
  int b;
  for(int i=0; i<n; i++){
    a = get<0>(coord[i]);
    b = get<1>(coord[i]);
    if((*plateau)[a][b] == 0){
      (*plateau)[a][b] = value;
      break;
    }
  }
}

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial(int s){
  Plateau init = plateauVide(s);
  rgen(&init);
  rgen(&init);
  return init;
}

int res = 0;

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/void deplacementGauche(Plateau *plateau){
   int s = size(*plateau);
  for(int k = 0; k<=s-2;k++){
    for (int i = 0; i <= s-1; i++){
      for (int j = s-2; j >= 0; j--){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i][j+1];
          (*plateau)[i][j+1] = 0;
        }
      }
    }
  } 
  for (int i = 0; i <= s-1; i++){
    for (int j = 0; j <= s-2; j++){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i][j+1]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        res += (*plateau)[i][j];
        (*plateau)[i][j+1] = 0;
      }
    } 
  }
  for(int k = 0; k<=s-2;k++){
    for (int i = 0; i <= s-1; i++){
      for (int j = s-2; j >= 0; j--){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i][j+1];
          (*plateau)[i][j+1] = 0;
        }
      }
    }
  } 
};



/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
void deplacementDroite(Plateau *plateau){
  int s = size(*plateau);
  for(int k = 0; k<=s-2;k++){
    for (int i = 0; i <= s-1; i++){
      for (int j = 1; j <= s-1; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i][j-1];
          (*plateau)[i][j-1] = 0;
        }
      }
    }
  } 
  for (int i = 0; i <= s-1; i++){
    for (int j = s-1; j >= 1; j--){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i][j-1]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        res += (*plateau)[i][j];
        (*plateau)[i][j-1] = 0;
      }
    } 
  }
  for(int k = 0; k<=s-2;k++){
    for (int i = 0; i <= s-1; i++){
      for (int j = 1; j <= s-1; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i][j-1];
          (*plateau)[i][j-1] = 0;
        }
      }
    }
  }  
}

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
void deplacementHaut(Plateau *plateau){
  int s = size(*plateau);
  for(int k = 0; k<=s-2; k++) {
    for (int i = 0; i <= s-2; i++){
      for (int j = 0; j <= s-1; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i+1][j];
          (*plateau)[i+1][j] = 0;
        } 
      }
    }
  }
  for (int i = 0; i <= s-2; i++){
    for (int j = 0; j <= s-1; j++){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i+1][j]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        res += (*plateau)[i][j];
        (*plateau)[i+1][j] = 0;
      }
    } 
  }
  for(int k = 0; k<=s-2; k++) {
    for (int i = 0; i <= s-2; i++){
      for (int j = 0; j <= s-1; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i+1][j];
          (*plateau)[i+1][j] = 0;
        } 
      }
    }
  } 
};



/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
void deplacementBas(Plateau *plateau){
  int s = size(*plateau);
  for(int k = 0; k<=s-2; k++) {
    for (int i = s-1; i >= 1; i--){
      for (int j = 0; j <= s-1; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i-1][j];
          (*plateau)[i-1][j] = 0;
        } 
      }
    }
  }
  for (int i = s-1; i >= 1; i--){
    for (int j = 0; j <= s-1; j++){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i-1][j]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        res += (*plateau)[i][j];
        (*plateau)[i-1][j] = 0;
      }
    } 
  }
  for(int k = 0; k<=s-2; k++) {
    for (int i = s-1; i >= 1; i--){
      for (int j = 0; j <= s-1; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i-1][j];
          (*plateau)[i-1][j] = 0;
        } 
      }
    }
  }
};



/* keycodes associés aux touches utilisées*/
const int GAUCHE = 260;
const int DROITE = 261;
const int HAUT = 259;
const int BAS = 258;
const int ENTER = 13;
const int SPACE = 32;
const int r = 114;
const int q = 113;


/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 **/
void deplacement(Plateau *plateau, int direction){
  switch ( direction ) {
    case GAUCHE:
      printw("last played: LEFT");
      deplacementGauche(plateau);
      break;
    case DROITE:
      printw("last played: RIGHT");
      deplacementDroite(plateau);
      break;
    case HAUT:
      printw("last played: UP");
      deplacementHaut(plateau);
      break;
    case BAS:
      printw("last played: DOWN");
      deplacementBas(plateau);
      break;
    default:
      printw("i can only read arrow-key inputs, sorry !");
      break;
  }
}
/**  construit un string contenant i espaces
 *  @param i un entier
 *  @return un string contenant i esaces
 **/
string empty(int i){
  string res = "";
  for(int j=0;j<i;j++){
    res.push_back(' ');
  }
  return res;
}


/** affiche un Plateau
 * @param p le Plateau
 **/

/* int k ~ int s in the previous functions */
string dessine(Plateau *plateau){
  int k = size(*plateau);
  string fulline = "\n";
  char s = '*';
  int n = 0;
  for(int i = 0; i<k; i++){
    for(int j = 0; j<k; j++){
      if((*plateau)[i][j]>n){
        n = (*plateau)[i][j];
      }
    }
  }
  int c;
  c = to_string(n).length();
  for(int i=0; i<1+k*(5+c); i++){
    fulline.push_back(s);
  }
  fulline.push_back('\n');
  string res = fulline;
  for(int i = 0; i<k; i++){
    res = res.append("*  ");
    for(int j = 0; j<k; j++){
      string cur = to_string((*plateau)[i][j]);
      int before = (c-cur.length())/2;
      int after = c-(before+cur.length());
      res.append(empty(before));
      res = res.append(cur);
      res.append(empty(after));
      res = res.append("  *  ");
    }
    res = res.append(fulline);
  }
  return res;
}

/**
  void saveLast(Plateau *plateau){
  int s = size(*plateau);
  ofstream fichier;
  fichier.open("savelastgame.txt");
  for (int i = 0; i <= (s-1); i++){
    for (int j = 0; j<= (s-1); j++){
      fichier << plateau[i][j];
    }
    fichier << endl;
  }
  fichier.close();
  return;
}
**/

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau *plateau){
  int s = size(*plateau);
  for (int i = 0; i <= (s-2); i++){
    for(int j = 0; j <= (s-2); j++){
      if ((*plateau)[i][j] == (*plateau)[i][j+1] || (*plateau)[i][j] == (*plateau)[i+1][j] || (*plateau)[s-1][s-1] == (*plateau)[s-2][s-1] || (*plateau)[s-1][s-1] == (*plateau)[s-1][s-2]){
        return false;
      }
    }
    for(int j = 0; j <= (s-1); j++){
      if ((*plateau)[i][j] == 0 || (*plateau)[s-1][s-1] == 0){
        return false;
      }
    }
  }
  for(int i = 0; i<=(s-2); i++){
    if((*plateau)[i][s-1] == (*plateau)[i+1][s-1]){
      return false;
    }
  }
    for(int i = 0; i<=(s-2); i++){
    if((*plateau)[s-1][i] == (*plateau)[s-1][i+1]){
      return false;
    }
  }
  /*saveLast(*plateau);*/
  return true;
}
;

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau *plateau){
  int s = size(*plateau);
  for (int i = 0; i<=(s-1); i++){
    for (int j = 0; j <= (s-1); j++){
      if ((*plateau)[i][j] == 2048){
        return true;
      }
    }
  }
  return false;;
}
  

/** Calcule le score associé à un tableau
 * sachant que tout chiffre plus gros que 2 est forcément combinaison 
 * d'autres chiffres (sauf 4 en cas d'apparition spontanée, cas non pris en compte --> solution: 3 that behaves like 4),
 *  il suffit d'additionner tous les chiffres plus gros que 2 pour obtenir le score de la partie
 * @param plateau un Plateau
 * @return un entier correspondant au score associé au plateau 
 **/
int score(Plateau *plateau){
  return res;
}