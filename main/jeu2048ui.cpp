#include <SFML/Graphics.hpp>
using namespace sf;
int main(){

	RenderWindow window(VideoMode(700, 1100), "jeu2048");
	
	while (window.isOpen()){
	
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		
		window.clear(Color::Black);
		
		RectangleShape grid(Vector2f(500.f, 500.f));
		grid.setFillColor(Color(255,182,193));
		window.draw(grid);
	
		}
		
		window.display();
	
	}
	
	return 0;

}


