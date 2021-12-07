# jeu2048
Goncalves Joe MI1 joe.goncalves@universite-paris-saclay.fr\
Chang Yena MI1  yena.chang@universite-paris-saclay.fr

## Résumé du travail effectué :
###### Niveau 0:
(0.1) (0.2) (0.3) (0.4) (0.5) (0.6) (0.7) (0.8)
###### Niveau 1:
(1.2) (1.3) (1.4)
###### Niveau 2:
(2.2)
###### Niveau 3:
(3.2) (3.3)

## Demonstration:
**function for random generation.**\
a naive approach to the random generation would be to use the `rand();` function for both i, j coordinates of the matrice and check if the value contained is 0. however, there is a possiblity that we will fall on the same (i,j) for an indefinite time consecutively (however low the chances due to the uniform distribution).
to eliminate this possiblity, the function `rgen();` produces a random permutation of the set of all coordinates in our playing matrice (this is completed in linear time thanks to the Fisher-Yates algorithm) and goes through the set with a for loop until it finds a coordinate containing the value 0. then, with our `tireDeuxouQuatre()` function, a 2 or 4 is generated (with 0.9 and 0.1 probability respectively) and placed in the coordinate.
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
