g++ -Wall -c -g ./main/jeu2048ui.cpp -lncurses  -std=c++20 &&
g++ jeu2048ui.o -o 2048ui -lsfml-graphics -lsfml-window -lsfml-system -lncurses -std=c++20 &&
./2048ui