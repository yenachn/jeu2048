# jeu2048
**Goncalves Joe MI1** joe.goncalves@universite-paris-saclay.fr
**Chang Yena MI1**  yena.chang@universite-paris-saclay.fr

## Résumé du travail effectué :
###### Niveau 0:

###### Niveau 1:
###### Niveau 2:
###### Niveau 3:
    
## Demonstration:
<span style = "color:red">function for random generation.</span>
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

## Organisation du travail : 
Nous avons consacré plus de 20 heures pour faire ce projet, (difficile de juger precisement beaucoup d aller retour sur les
differentes focntions du code), nous avons profité de la plateforme Github pour mettre en commun nos informations 
lorsque nous ne pouvions pas nous voir directement. 

    
## Prise de recul :

(perso joe )La principale difficulté a été pour moi de m adapter aux methodes de codage de mon binome en effet, nos manière de 
coder sont assez differentes, je prefere utiliser des codes simple etudier en classe, revisiter des methodes classique quitte a 
perdre en efficacité et en temps mais gagner en souplesse. A l inverse mon binome emploie beaucoup de methode pas encore etudier, 
de nouvelles maniere de voir les chose qui s eloigne un peu de se que j avais l habitude de voir. Un mal pour un bien cela m a 
permis de decouvrir de nouvelles methodes, mais a refaire je choisirai tout de meme un peu plus de facilitée a certains niveaux.
