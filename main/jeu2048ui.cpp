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
			RectangleShape rectangle(Vector2f(90.f,90.f));
			grid[i].push_back(rectangle);		
		}	
	}
	return grid;
}

void set_positions(Grid *grid){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; j++)
		{
			(*grid)[i][j].setPosition(Vector2f(i*100.f, j*100.f));
		}
	}
}

void set_color(Grid *grid,Plateau plateau){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; j++){
			(*grid)[i][j].setFillColor(Color(max(int(log2(plateau[i][j])*64),255),0,0));
		}
	}
}

void merge_swap(Grid *grid, Plateau plateau){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; i++){

		}
	}
}

void draw_grid(RenderWindow *window ,Grid *grid){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; j++){
			(*window).draw((*grid)[i][j]);
		}
	}
}

void set_score(int score, Plateau plateau){

}

int main() {
	Plateau init = plateauInitial();
	RenderWindow window(VideoMode(1000, 1000), "jeu2048");
	Grid grid = init_grid();
	set_positions(&grid);
	window.clear(Color::Black);
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


