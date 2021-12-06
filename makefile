CC = g++
CFLAGS = -wall -g
main: 2048.o jeu2048ui.o modele.o
    $(CC)$(CFLAGS) -o main 2048.o jeu2048ui.o modele.o
2048.o: 2048.cpp
    $(CC)$(CFLAGS) -c 2048.cpp
jeu2048ui.o: jeu2048ui.cpp
    $(CC)$(CFLAGS) -c jeu2048ui.cpp
modele.o: modele.cpp
    $(CC)$(CFLAGS) -c modele.cpp