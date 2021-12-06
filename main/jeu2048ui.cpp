#include <iostream>
#include <string>
#include <vector>
#include <math.h>  
#include <stdio.h>    
#include <stdlib.h>   
#include <SFML/Graphics.hpp>
#include "modele.cpp"

using namespace sf;
using namespace std;

typedef vector<vector<RectangleShape>> Grid;
typedef vector<vector<Text>> TextGrid;

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
			(*grid)[i][j].setPosition(Vector2f(i*100.f,35+j*100.f));
		}
	}
}

void set_color(Grid *grid,Plateau *plateau){
	for (int i = 0; i <= 3; i++){
		for (int j = 0; j <= 3; j++){
			int level = max(int(255 - log2((*plateau)[i][j]+1)*21),0);
			(*grid)[j][i].setFillColor(Color(255,level,level));
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

void draw_text(RenderWindow *window,Plateau *plateau){
	Text text;
	Font font;
	font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");

	string str = "score : " + to_string(score(plateau));
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(30);
	text.setString(str);
	text.setPosition(Vector2f(0,-2.5));
	(*window).draw(text);
	for(int i = 0; i <= 3;i++){
		for(int j = 0;j <=3; j++){
			Text text;
			string str = to_string((*plateau)[i][j]);
			int c = str.length();
			text.setFont(font);
			text.setFillColor(Color::Black);
			text.setCharacterSize(30);
			text.setString(str);
			text.setPosition(Vector2f(j*100.f+(90-15*c)/2,35+i*100.f+25));
			(*window).draw(text);
		}
	}
}

void draw_update(RenderWindow *window, Grid *grid, Plateau *plateau){
		window->clear(Color::Black);
		set_color(grid, plateau);
		draw_grid(window, grid);
		draw_text(window, plateau);
		window->display();
}


int main(){

	RenderWindow window(VideoMode(390,425), "jeu2048");
	Grid grid = init_grid();
	printf("grid initialised \n");
	set_positions(&grid);
	printf("positions initialised \n");
	window.clear(Color::Black);
	printf("window cleared \n");

	startagain:
	srand(time(NULL));
	printf("random initialised \n");
	Plateau init = plateauInitial();
	Plateau old = plateauVide();
	int c;
	bool cont = false;
	initscr();
	keypad(stdscr, true);
	draw_update(&window,&grid,&init);

	loop:
	printf("reached loop \n");
	do  {
		printw("went through loop !\n");
		c = getch();
		if(c!=255)clear();
		old = init;
		deplacement(&init, c);
		if(old!=init){
			rgen(&init);
		} 
		printw(dessine(&init).c_str());
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		}
		draw_update(&window,&grid,&init);
	} while (window.isOpen() && c!=113 && (cont || !estGagnant(&init)) && !estTermine(&init));
	if (estGagnant(&init)){
	
	c = getch();
	switch(c){
	
	case r:
		clear();
		goto startagain;
	case q:
		goto end;
	default:
		clear();
		cont = true;
		goto loop;
		}
	}
	if (estTermine(&init)){
		c = getch();
		if(c==r) goto startagain;
		else goto end;
	}
	end:
	endwin();
	return 0;
}