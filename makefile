CC = g++
CFLAGS = -wall -o
main : 2048.o modele.o
	$(CC) -wall -g main 2048.o modele.o
modele.o: modele.cpp
	$(CC)$(CFLAGS) -g ./main/modele.cpp -lncurses -c++20
2048.o: 2048.cpp
	$(CC)$(CFLAGS) -g ./main/2048.cpp -lncurses -c++20
