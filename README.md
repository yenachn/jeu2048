# jeu2048
Goncalves Joe MI1 joe.goncalves@universite-paris-saclay.fr\
Chang Yena MI1  yena.chang@universite-paris-saclay.fr

## Résumé du travail effectué :
###### Niveau 0:
(0.1), (0.2) (0.3), (0.4), (0.5), (0.6), (0.7)\
La fonctionnalité a été démontrée pendant la soutenance.
###### Niveau 1:
(1.2): Nous avons utilisé la bibliothèque `ncurses` pour recevoir les entrées du clavier en utilisant `getch()` et utilisé un switch case pour différencier les différentes actions correspondant à chaque touche fléchée.\
(1.3): La fonctionnalité a été démontrée pendant la soutenance.\
(1.4): Le score du jeu 2048 est calculé en ajoutant la valeur additionnée des fusions à chaque fois qu'il y a une fusion. Notre première approche était donc d'utiliser une variable globale `int score` à laquelle nous ajouterions la valeur fusionnée après chaque fusion. Cependant, en raison des contraintes du projet, nous avons dû trouver une méthode pour le calculer sans variable globale.\
Pour cela, nous devons noter que chaque nombre sur la grille du jeu peut être réécrit sous la forme `2^n`, ou `((((2+2)+4)+8)+...)`. Par conséquent, en supposant que la génération aléatoire ne génère que des 2, nous pouvons calculer le score en ajoutant `(2+2) + ((2+2)+4) + (2+2) + (((2+2)+4)+8) + (2+2) + ((2+2)+4). ...` qui peut être réécrit comme `2^2 + 2^3 + 2^2 + 2^4 + 2^2 + 2^3 + ...` puis simplifié comme `(n-1)2^2 + (n-2)2^3 + ...`. Cependant, nous devons prendre en compte les 4 générés aléatoirement. La méthode simple serait de compter le nombre de fois qu'un 4 a été généré et de simplement soustraire ce nombre de `(2^2)` de notre somme précédente, et pour ce faire nous devons considérer 2 cas : un où il y avait un 4 généré aléatoirement fusionné avec un 4 qui était une fusion entre 2 2s, et un où il y a deux 4 générés aléatoirement qui fusionnent ensemble.\
Intuitivement, ma première solution était de baliser ces valeurs : `4' -> 8'` et `4' -> 8''` dans le dernier cas où il y a deux 4 générés aléatoirement. Pour écrire cela en code, mon idée était de changer les nombres : quand un 4 est généré aléatoirement, ce serait en fait un 3 qui se comporte simplement comme un 4. Par conséquent, nous enregistrerions deux valeurs pour les valeurs de fusion qui partent d'un 4 généré aléatoirement : `3 + 4 -> 7` et `4 + 4 -> 8`. Cela permet de vérifier facilement l'origine de nos valeurs de fusion sur notre `plateau` actuel. Pour les nombres qui peuvent être décomposés en `2^n-1 (n \in N)`, cela a commencé à partir d'un 4 généré aléatoirement fusionné avec un 4 fusionné 2+2, et pour les nombres qui peuvent être décomposés en `2^n-2`, les 2 4 ayant été générés aléatoirement.
###### Niveau 2:
(2.1): Nous avons essayé de créer un Makefile pour réaliser l'intégralité du projet (les deux jeux), mais nous avons été bloqués par quelques problèmes que nous n'avons pas pu résoudre dans les délais impartis. Cependant, nous avons écrit 2 fichiers `.sh` séparés pour le jeu avec l'interface utilisateur et le jeu sur console (fonctionnalité testée pendant la soutenance).\
(2.2): Nous avons utilisé `github` pour notre projet. https://github.com/yenachn/jeu2048
###### Niveau 3:
(3.2): Notre jeu comportait plusieurs variantes, le plateau de jeu étant de `n` tailles différentes. (Fonctionnalité testée en soutenance.)\
(3.3): Nous avons utilisé `SFML` pour l'interface utilisateur. (Fonctionnalité testée en soutenance.)\
![4x4 and 5x5](https://github.com/yenachn/jeu2048/blob/main/variants.png)

## Demonstration:
**Fonction pour la génération aléatoire.**\
Une approche naïve de la génération aléatoire serait d'utiliser la fonction `rand();` pour les deux coordonnées `i, j` de la matrice et de vérifier si la valeur contenue est 0. Cependant, il y a une possibilité que nous tombions sur le même `(i,j)` pour un temps indéfini consécutivement (même si les chances sont faibles en raison de la distribution uniforme).\
Pour éliminer cette possibilité, la fonction `rgen();` produit une permutation aléatoire de l'ensemble de toutes les coordonnées de notre matrice de jeu - ceci est réalisé en temps linéaire grâce à l'algorithme de Fisher-Yates (en expérimentant, nous avons aussi expérimenté l'algorithme de Sattolo, qui renvoie des permutations cycliques en temps linéaire mais nous avons décidé de ne pas l'utiliser car il n'est pas complet) et parcourt l'ensemble avec une boucle for jusqu'à ce qu'il trouve une coordonnée contenant la valeur 0. Ensuite, avec notre fonction `tireDeuxouQuatre()`, un 2 ou un 4 est généré (avec une probabilité de 0,9 et 0,1 respectivement) et placé dans la coordonnée.\
En écrivant mon code, je savais qu'avec la distribution uniforme de `rand()`, le simple fait de choisir des coordonnées aléatoires permettrait d'accomplir la tâche en un temps constant. Cependant, j'ai choisi d'utiliser ma méthode avec la permutation de mon ensemble de coordonnées pour des raisons de complétude mathématique. Comme cela permet d'accomplir la tâche en temps linéaire, j'ai pensé que c'était un sacrifice raisonnable de complexité. J'ai passé quelques heures à essayer de penser à des méthodes de permutation qui accompliraient la tâche en temps linéaire ; cependant, je n'ai pu trouver que quelques méthodes naïves qui l'accompliraient en temps quadratique en faisant une liste liée de taille n, contenant `0,...,n-1`, faire un tableau de taille `n`. Pour `i=0 à n-1`, prendre un nombre aléatoire `k` entre `0 et n-1-i`, puis prendre le kième nombre de la liste liée. Et `permutation[i]` sera la valeur de la kième cellule de la liste. De cette façon, on aura une complexité de somme `k=0 à n-1 de k`, donc `k(k-1)/2` -> `k^2` en complexité. J'ai fait des recherches sur différentes méthodes et j'ai trouvé la méthode de Fisher-Yates, que j'ai intégrée dans mon code.
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
**Un exemple de la fonction de déplacement (à droite)**\
La fonction de déplacement est divisée en 3 actions principales : glisser sur toutes les coordonnées de valeur 0, puis fusionner les valeurs adjacentes identiques, puis glisser à nouveau sur tous les 0. les actions de glissement sont imbriquées dans une boucle for de `k=0 à s-2`. La valeur `s-2` a été choisie parce que le nombre maximum de glissements nécessaires à une coordonnée non nulle pour atteindre la coordonnée nulle la plus éloignée ([1 0 0 0 0 0]) dans un vecteur de n variables est `n-1`.
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
**Function to check game end.**\
La partie se termine à la satisfaction de la condition suivante :\
Toutes les coordonnées dans la matrice ont des valeurs adjacentes différentes qui ne sont pas égales à zéro (aucun autre glissement n'est possible).\
Dans cette fonction j'ai utilisé une méthode simple : vérifier la matrice de 0 à (s-2) si la valeur à i+1 ou j+1 a la même valeur que la coordonnée vérifiée et n'est pas égale à 0. Nous avons rencontré une petite erreur : nous ne vérifions pas la matrice pour des adjacents égaux dans plateau[i][s-1] et dans plateau[s-1][i] (i de 0 à s-2). De plus, notre code ne touchait pas du tout la valeur de plateau[s-1][s-1] (si elle est égale à 0 et si elle a des adjacents égaux). Nous avons alors inclus des conditions supplémentaires (glissements unidirectionnels sur les coordonnées [i][(s-1)] et [(s-1)][i] de la matrice) dans notre fonction pour inclure ces négligences.
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
