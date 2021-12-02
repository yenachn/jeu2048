#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "modele.cpp"

using namespace sf;
using namespace std;

typedef vector<vector<RectangleShape>> Grid;

void set_positions(Grid grid){
	
}

int main() {


	RenderWindow window(VideoMode(700, 1100), "jeu2048");
	window.clear(Color::White);
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		RectangleShape grid(Vector2f(500.f, 500.f));
		grid.setFillColor(Color(255,255,255));
		window.draw(grid);
		}
		window.display();
	}
	return 0;
}


