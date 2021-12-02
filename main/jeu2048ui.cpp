#include <iostream>
#include <string>
#include <vector>
#include <math.h>  
#include <SFML/Graphics.hpp>
#include "modele.cpp"

using namespace sf;
using namespace std;

typedef vector<vector<RectangleShape>> Grid;
typedef vector<RectangleShape> Row;

Grid init_grid(){
	Grid grid;
	grid = Grid(4);
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; j++){
			RectangleShape rectangle(Vector2f(290.f,290.f));
			grid[i].push_back(rectangle);		
		}	
	}
	return grid;
}

void set_positions(Grid *grid){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; i++)
		{
			(*grid)[i][j].setPosition(Vector2f(i*300.f, j*300.f));
		}
	}
}

void set_color(Grid *grid,Plateau plateau){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; i++){
			(*grid)[i][j].setFillColor(Color(max(int(log2(plateau[i][j])*64),255),0,0));
		}
	}
}

void draw_grid(RenderWindow *window ,Grid *grid){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; i++){
			(*window).draw((*grid)[i][j]);
		}
	}
}

int main() {
	Plateau init = plateauInitial();
	RenderWindow window(VideoMode(1000, 1000), "jeu2048");
	Grid grid;
	set_positions(&grid);
	window.clear(Color::White);
	while (window.isOpen()){
		set_color(&grid,init);
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		draw_grid(&window,&grid);
		}
		window.display();
	}
	return 0;
}


