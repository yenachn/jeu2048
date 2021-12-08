# jeu2048
Goncalves Joe MI1 joe.goncalves@universite-paris-saclay.fr\
Chang Yena MI1  yena.chang@universite-paris-saclay.fr

## Résumé du travail effectué :
###### Niveau 0:
(0.1), (0.2) (0.3), (0.4), (0.5), (0.6), (0.7)\
La fonctionnalité a été démontrée pendant la soutenance.
###### Niveau 1:
(1.2): Nous avons utilisé la bibliothèque `ncurses` pour recevoir les entrées du clavier en utilisant `getch()` et utilisé un switch case pour différencier les différentes actions correspondant à chaque touche fléchée.\
(1.3): La fonctionnalité a été démontrée pendant la soutenance.
(1.4): Le score du jeu 2048 est calculé en ajoutant la valeur additionnée des fusions à chaque fois qu'il y a une fusion. Notre première approche était donc d'utiliser une variable globale `int score` à laquelle nous ajouterions la valeur fusionnée après chaque fusion. Cependant, en raison des contraintes du projet, nous avons dû trouver une méthode pour le calculer sans variable globale.\
Pour cela, nous devons noter que chaque nombre sur la grille du jeu peut être réécrit sous la forme `2^n`, ou `((((2+2)+4)+8)+...)`. Par conséquent, en supposant que la génération aléatoire ne génère que des 2, nous pouvons calculer le score en ajoutant `(2+2) + ((2+2)+4) + (2+2) + (((2+2)+4)+8) + (2+2) + ((2+2)+4). ...` qui peut être réécrit comme `2^2 + 2^3 + 2^2 + 2^4 + 2^2 + 2^3 + ...` puis simplifié comme `(n-1)2^2 + (n-2)2^3 + ...`. Cependant, nous devons prendre en compte les 4 générés aléatoirement. La méthode simple serait de compter le nombre de fois qu'un 4 a été généré et de simplement soustraire ce nombre de `(2^2)` de notre somme précédente, et pour ce faire nous devons considérer 2 cas : un où il y avait un 4 généré aléatoirement fusionné avec un 4 qui était une fusion entre 2 2s, et un où il y a deux 4 générés aléatoirement qui fusionnent ensemble.\
Intuitivement, ma première solution était de baliser ces valeurs : `4' -> 8'` et `4' -> 8''` dans le dernier cas où il y a deux 4 générés aléatoirement. Pour écrire cela en code, mon idée était de changer les nombres : quand un 4 est généré aléatoirement, ce serait en fait un 3 qui se comporte simplement comme un 4. Par conséquent, nous enregistrerions deux valeurs pour les valeurs de fusion qui partent d'un 4 généré aléatoirement : `3 + 4 -> 7` et `4 + 4 -> 8`. Cela permet de vérifier facilement l'origine de nos valeurs de fusion sur notre `plateau` actuel. Pour les nombres qui peuvent être décomposés en `2^n-1 (n \in N)`, cela a commencé à partir d'un 4 généré aléatoirement fusionné avec un 4 fusionné 2+2, et pour les nombres qui peuvent être décomposés en `2^n-2`, les 2 4 ayant été générés aléatoirement.
###### Niveau 2:
(2.1): Nous avons essayé de créer un Makefile pour réaliser l'intégralité du projet (les deux jeux), mais nous avons été bloqués par quelques problèmes que nous n'avons pas pu résoudre dans les délais impartis. Cependant, nous avons écrit 2 fichiers `.sh` séparés pour le jeu avec l'interface utilisateur et le jeu sur console (fonctionnalité testée pendant la soutenance).
(2.2): We used `github` for our project. https://github.com/yenachn/jeu2048
###### Niveau 3:
(3.2): Notre jeu comportait plusieurs variantes, le plateau de jeu étant de `n` tailles différentes. (Fonctionnalité testée en soutenance.)\
(3.3): Nous avons utilisé `SFML` pour l'interface utilisateur. (Fonctionnalité testée en soutenance.)\
![4x4 and 5x5](https://github.com/yenachn/jeu2048/blob/main/variants.png)

## Demonstration:
**function for random generation.**\
a naive approach to the random generation would be to use the `rand();` function for both i, j coordinates of the matrice and check if the value contained is 0. however, there is a possiblity that we will fall on the same (i,j) for an indefinite time consecutively (however low the chances due to the uniform distribution).
to eliminate this possiblity, the function `rgen();` produces a random permutation of the set of all coordinates in our playing matrice - this is completed in linear time thanks to the Fisher-Yates algorithm (while experimenting we also experimented with sattolo's algorithm, which returns cyclic permutations in linear time but decided against using it as it isn't complete) and goes through the set with a for loop until it finds a coordinate containing the value 0. then, with our `tireDeuxouQuatre()` function, a 2 or 4 is generated (with 0.9 and 0.1 probability respectively) and placed in the coordinate.
```c++
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
```
**an example of the deplacement function (right)**\
the deplacement function is divided into 3 main actions: slide over all coordinates with value 0, then merge identical adjacent values, then slide over all 0s again. the slide actions are nested in a for loop of `k=0 to s-2`. this is because the nested loop, which deplaces the nonzero coordinates over zero coordinates, has a maximum reach of one block (it only moves 1 block at a time). the value `s-2` was chosen because the maximum amount of slides it would require a nonzero coordinate to slide to the furthest zero coordinate ([1 0 0 0 0 0]) in a vector of n variables is `n-1`.
```c++
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
```
**function to check game end.**\
the game ends at the satisfaction the following condition:\
all coordinates in the matrice have different adjacent values that are not equal to zero (no further slides are possible).\
in this function i used a simple method: check the matrice from 0 to (s-2) if the value at i+1 or j+1 has the same value to the checked coordinate and is not equal to 0. we came across a small error: we weren't checking the matrice for equal adjacents in plateau[i][s-1] and in plateau[s-1][i] (i from 0 to s-2). also, our code did not touch the plateau[s-1][s-1] value at all (if it is 0 and if it has equal adjacents). we then included further conditions in our function to include these negligences.
```c++
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
```
(to continue)

## Organisation du travail : 
We spent around 20 hours to make this project (however the work wasn't at a regular pace so it is hard to be sure). We used GitHub to work together on the project when we weren't working together on place. 

    
## Prise de recul :

(joe) La principale difficulté a été pour moi de m adapter aux methodes de codage de mon binome en effet, nos manière de 
coder sont assez differentes, je prefere utiliser des codes simple etudier en classe, revisiter des methodes classique quitte a 
perdre en efficacité et en temps mais gagner en souplesse. A l inverse mon binome emploie beaucoup de methode pas encore etudier, 
de nouvelles maniere de voir les chose qui s eloigne un peu de se que j avais l habitude de voir. Un mal pour un bien cela m a 
permis de decouvrir de nouvelles methodes, mais a refaire je choisirai tout de meme un peu plus de facilitée a certains niveaux.

(yena) Before I started this project I barely knew any c++ other than how to construct loops. By working on this project I was able to vastly enlargen my skillset and gain a decent fluency in this language.
