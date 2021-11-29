
#include <iostream>
#include <vector>
#include <tuple>
#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>
#include <vector>
using namespace std;

typedef vector<vector<int> > Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 */



/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide(){
  Plateau init;
  for (int i = 0; i <= 3; i++){
    init[i] = {0, 0, 0, 0};
  };
  return init;
}


/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial(){
  Plateau init = plateauVide();
  int i1 = rand()%4;
  int j1 = rand()%4;
  int i2 = rand()%4;
  int j2 = rand()%4;
  init[i1][j1] = 2;
  init[i2][j2] = 2;
  return init;
}

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre(){
  int i = 2+2*(rand()%2);
  return i;
}

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau){
    Plateau newPlateau = plateau;
    for (int i = 0; i <= 2; i++){
    for (int j = 0; j <= 2; j++){
      if (newPlateau[i][j] == 0){
        newPlateau[i][j] = newPlateau[i][j+1];
        newPlateau[i][j+1] = 0;
      } else if (newPlateau[i][j] == newPlateau[i][j+1]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i][j+1] = 0;
      }
    }
  }
  return newPlateau;
};

/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plateau){
  Plateau newPlateau = plateau;
  for (int i = 0; i <= 2; i++){
    for (int j = 2; j >= 0; j--){
      if (newPlateau[i][j] == 0){
        newPlateau[i][j] = newPlateau[i][j-1];
        newPlateau[i][j-1] = 0;
      } else if (newPlateau[i][j] == newPlateau[i][j-1]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i][j-1] = 0;
      }
    }
  }
  return newPlateau;
}

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plateau){
  Plateau newPlateau = plateau;
  for (int i = 0; i <= 2; i++){
    for (int j = 0; j <= 2; j++){
      if (newPlateau[i][j] == 0){
        newPlateau[i][j] = newPlateau[i+1][j];
        newPlateau[i+1][j] = 0;
      } else if (newPlateau[i][j] == newPlateau[i+1][j]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i+1][j] = 0;
      }
    }
  }
  return newPlateau;
};

/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plateau){
  Plateau newPlateau = plateau;
  for (int i = 2; i >= 0; i--){
    for (int j = 0; j <= 2; j++){
      if (newPlateau[i][j] == 0){
        newPlateau[i][j] = newPlateau[i-1][j];
        newPlateau[i-1][j] = 0;
      } else if (newPlateau[i][j] == newPlateau[i-1][j]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i-1][j] = 0;
      }
    }
  }
  return newPlateau;
}

const int GAUCHE = 0;
const int DROITE = 1;
const int HAUT = 2;
const int BAS = 3;

/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 **/
Plateau deplacement(Plateau plateau, int direction){
  switch ( direction ) {
    case GAUCHE:
      return deplacementGauche(plateau);
    case DROITE:
      return deplacementDroite(plateau);
    case HAUT:
      return deplacementHaut(plateau);
    case BAS:
      return deplacementBas(plateau);
    default:
      cerr << "Deplacement non-autorise!" << endl;
      exit(-1);
  }
}


/** affiche un Plateau
 * @param p le Plateau
 **/
string dessine(Plateau p);

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau plateau){
  for (int i = 0; i <= 2; i++){
    for(int j = 0; j <= 2; j++){
      if (plateau[i][j] == plateau[i][j+1] || plateau[i][j] == plateau[i+1][j]){
        return false;
      }
    }
    for(int j = 0; j <= 3; j++){
      if (plateau[i][j] == 0){
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
bool estGagnant(Plateau plateau){
  for (int i = 0; i<=3; i++){
    for (int j = 0; j <= 3; j++){
      if (plateau[i][j] == 2048){
        return true;
      }
    }
  }
  return false;;
}
