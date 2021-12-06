
#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>
#include <vector>
#include <curses.h>
using namespace std;

typedef vector<vector<int> > Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 */


/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide(){
  Plateau init;
  init = Plateau(4);
  for (int i = 0; i <= 3; i++){
    init[i] = {0, 0, 0, 0};
  };
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

vector<tuple<int, int>> coord =
  {{0,0},{0,1}, {0,2}, {0,3},
   {1,0}, {1,1}, {1,2}, {1,3},
   {2,0}, {2,1}, {2,2}, {2,3}, 
   {3,0}, {3,1}, {3,2}, {3,3}};


/** Rajoute avec soit un 2, soit un 4 avec les probabilités souhaitées d'apparition, dans l'une des cases vides.
 *  L'algorithme utilisé écrit se base suyr l'algorithme de permutation aléatoire de Fisher-Yates
 *  @param plateau un Plateau
 *  @return un nouveau plateau res, correspondant à plateau dans lequel a été ajouté un 2 ou un 4 dans l'une des cases vides.
 **/
void rgen(Plateau *plateau){
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
Plateau plateauInitial(){
  Plateau init = plateauVide();
  rgen(&init);
  rgen(&init);
  return init;
}


/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
void deplacementGauche(Plateau *plateau){
  for(int k = 0; k<=2;k++){
    for (int i = 0; i <= 3; i++){
      for (int j = 2; j >= 0; j--){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i][j+1];
          (*plateau)[i][j+1] = 0;
        }
      }
    }
  } 
  for (int i = 0; i <= 3; i++){
    for (int j = 0; j <= 2; j++){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i][j+1]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        (*plateau)[i][j+1] = 0;
      }
    } 
  }
  for(int k = 0; k<=2;k++){
    for (int i = 0; i <= 3; i++){
      for (int j = 2; j >= 0; j--){
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
  for(int k = 0; k<=2;k++){
    for (int i = 0; i <= 3; i++){
      for (int j = 1; j <= 3; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i][j-1];
          (*plateau)[i][j-1] = 0;
        }
      }
    }
  } 
  for (int i = 0; i <= 3; i++){
    for (int j = 3; j >= 1; j--){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i][j-1]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        (*plateau)[i][j-1] = 0;
      }
    } 
  }
  for(int k = 0; k<=2;k++){
    for (int i = 0; i <= 3; i++){
      for (int j = 1; j <= 3; j++){
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
  for(int k = 0; k<=2; k++) {
    for (int i = 0; i <= 2; i++){
      for (int j = 0; j <= 3; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i+1][j];
          (*plateau)[i+1][j] = 0;
        } 
      }
    }
  }
  for (int i = 0; i <= 2; i++){
    for (int j = 0; j <= 3; j++){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i+1][j]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        (*plateau)[i+1][j] = 0;
      }
    } 
  }
  for(int k = 0; k<=2; k++) {
    for (int i = 0; i <= 2; i++){
      for (int j = 0; j <= 3; j++){
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
  for(int k = 0; k<=2; k++) {
    for (int i = 3; i >= 1; i--){
      for (int j = 0; j <= 3; j++){
        if ((*plateau)[i][j] == 0){
          (*plateau)[i][j] = (*plateau)[i-1][j];
          (*plateau)[i-1][j] = 0;
        } 
      }
    }
  }
  for (int i = 3; i >= 1; i--){
    for (int j = 0; j <= 3; j++){
      if ((*plateau)[i][j] != 0 && (*plateau)[i][j] == (*plateau)[i-1][j]){
        (*plateau)[i][j] = 2*(*plateau)[i][j];
        (*plateau)[i-1][j] = 0;
      }
    } 
  }
  for(int k = 0; k<=2; k++) {
    for (int i = 3; i >= 1; i--){
      for (int j = 0; j <= 3; j++){
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
      printw("Déplacement vers la GAUCHE");
      deplacementGauche(plateau);
      break;
    case DROITE:
      printw("Déplacement vers la DROITE");
      deplacementDroite(plateau);
      break;
    case HAUT:
      printw("Déplacement vers le HAUT");
      deplacementHaut(plateau);
      break;
    case BAS:
      printw("Déplacement vers le BAS");
      deplacementBas(plateau);
      break;
    default:
      printw("Déplacement non-autorise!");
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
string dessine(Plateau *plateau){
  string fulline = "\n";
  char s = '*';
  int n = 0;
  for(int i = 0; i<=3; i++){
    for(int j = 0; j<=3; j++){
      if((*plateau)[i][j]>n){
        n = (*plateau)[i][j];
      }
    }
  }
  int c;
  c = to_string(n).length();
  for(int i=0; i<21+4*(c); i++){
    fulline.push_back(s);
  }
  fulline.push_back('\n');
  string res = fulline;
  for(int i = 0; i<=3; i++){
    res = res.append("*  ");
    for(int j = 0; j<=3; j++){
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

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau *plateau){
  for (int i = 0; i <= 2; i++){
    for(int j = 0; j <= 2; j++){
      if ((*plateau)[i][j] == (*plateau)[i][j+1] || (*plateau)[i][j] == (*plateau)[i+1][j]){
        return false;
      }
    }
    for(int j = 0; j <= 3; j++){
      if ((*plateau)[i][j] == 0){
        return false;
      }
    }
  }
  return true;
}
;

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau *plateau){
  for (int i = 0; i<=3; i++){
    for (int j = 0; j <= 3; j++){
      if ((*plateau)[i][j] == 2048){
        return true;
      }
    }
  }
  return false;;
}
  

/** Calcule le score associé à un tableau
 * sachant que tout chiffre plus gros que 2 est forcément combinaison 
 * d'autres chiffres (sauf 4 en cas d'apparition spontanée, cas non pris en compte),
 *  il suffit d'additionner tous les chiffres plus gros que 2 pour obtenir le score de la partie
 * @param plateau un Plateau
 * @return un entier correspondant au score associé au plateau 
 **/
int score(Plateau *plateau){
  int res = 0;
  for(int i=0;i<=3;i++){
    for (int j = 0; j<= 3; j++)
    {
      if((*plateau)[i][j]>2){
        res+=(*plateau)[i][j];
      }
    }
  }
  return res;
}