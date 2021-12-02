g++ -Wall -c -g ./main/jeu2048ui.cpp -lncurses &&
g++ jeu2048ui.o -o 2048ui -lsfml-graphics -lsfml-window -lsfml-system -lncurses &&
./2048ui