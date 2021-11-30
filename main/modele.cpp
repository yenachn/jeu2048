
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

Plateau rgen(Plateau plateau){
  Plateau res = plateau;
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
    if(res[a][b] == 0){
      res[a][b] = value;
      break;
    }
  }
  return res;
}

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial(){
  Plateau init = plateauVide();
  init = rgen(init);
  init = rgen(init);
  return init;
}


/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plateau){
  Plateau newPlateau = plateau;
  for (int i = 0; i <= 2; i++){
    for (int j = 0; j <= 2; j++){
      if (newPlateau[i][j] != 0 && newPlateau[i][j] == newPlateau[i][j+1]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i][j+1] = 0;
      }
    } 
  };
  for(int k = 0; k<=2;k++){
    for (int i = 0; i <= 3; i++){
      for (int j = 2; j >= 0; j--){
        if (newPlateau[i][j] == 0){
          newPlateau[i][j] = newPlateau[i][j+1];
          newPlateau[i][j+1] = 0;
        }
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
      if (newPlateau[i][j] != 0 && newPlateau[i][j] == newPlateau[i][j-1]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i][j-1] = 0;
      }
    } 
  }
  for(int k = 0; k<=2;k++){
    for (int i = 0; i <= 3; i++){
      for (int j = 1; j <= 3; j++){
        if (newPlateau[i][j] == 0){
          newPlateau[i][j] = newPlateau[i][j-1];
          newPlateau[i][j-1] = 0;
        }
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
    for (int j = 0; j <= 3; j++){
      if (newPlateau[i][j] != 0 && newPlateau[i][j] == newPlateau[i+1][j]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i+1][j] = 0;
      }
    } 
  };
  for(int k = 0; k<=2; k++) {
    for (int i = 0; i <= 2; i++){
      for (int j = 0; j <= 3; j++){
        if (newPlateau[i][j] == 0){
          newPlateau[i][j] = newPlateau[i+1][j];
          newPlateau[i+1][j] = 0;
        } 
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
  for (int i = 3; i >= 1; i--){
    for (int j = 0; j <= 3; j++){
      if (newPlateau[i][j] != 0 && newPlateau[i][j] == newPlateau[i-1][j]){
        newPlateau[i][j] = 2*newPlateau[i][j];
        newPlateau[i-1][j] = 0;
      }
    } 
  };
  for(int k = 0; k<=2; k++) {
    for (int i = 3; i >= 1; i--){
      for (int j = 0; j <= 3; j++){
        if (newPlateau[i][j] == 0){
          newPlateau[i][j] = newPlateau[i-1][j];
          newPlateau[i-1][j] = 0;
        } 
      }
    }
  }
  return newPlateau;
};

const int CHAR1 = 224;
const int GAUCHE = 72;
const int DROITE = 80;
const int HAUT = 75;
const int BAS = 77;
const int ENTER = 13;
const int SPACE = 32;

int direction(){
  unsigned char ch1 = getch();
  if (ch1 == CHAR1){
    ch1 = getch();}
return ch1;
}
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
/*construit un string contenant i espaces*/
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
string dessine(Plateau plateau){
  string fulline = "\n";
  char s = '*';
  int n = 0;
  for(int i = 0; i<=3; i++){
    for(int j = 0; j<=3; j++){
      if(plateau[i][j]>n){
        n = plateau[i][j];
      }
    }
  }
  int c;
  c = to_string(n).length();
  for(int i=0; i<5+4*(c); i++){
    fulline.push_back(s);
  }
  fulline.push_back('\n');
  string res = fulline;
  for(int i = 0; i<=3; i++){
    res = res.append("*");
    for(int j = 0; j<=3; j++){
      string cur = to_string(plateau[i][j]);
      int before = (c-cur.length())/2;
      int after = c-(before+cur.length());
      res.append(empty(before));
      res = res.append(cur);
      res.append(empty(after));
      res = res.append("*");
    }
    res = res.append(fulline);
  }
  return res;
}

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

int main(){
  Plateau init = 
  {{0, 2, 2, 0 },
   {2, 4, 2, 0},
   {0, 0, 0, 2},
   {0, 0, 2, 0}
  };
  cout << dessine(init) << endl;
  cout << "move haut" << endl << dessine(deplacementHaut(init));
  while(true){
    cout << direction() << endl;
  }
  return 0;
  }