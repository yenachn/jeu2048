g++ -Wall -c -g ./main/jeu2048ui.cpp -lncurses &&
g++ jeu2048ui.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lncurses