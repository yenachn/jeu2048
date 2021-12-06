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

Grid init_grid(int s){
	Grid grid;
	grid = Grid(s);
	for (int i = 0; i < s; i++){
		for (int j = 0; j < s; j++){
			RectangleShape rectangle(Vector2f(90.f,90.f));
			grid[i].push_back(rectangle);		
		}	
	}
	return grid;
}

void set_positions(Grid *grid){
	int s = size(*grid);
	for (int i = 0; i < s; i++){
		for (int j = 0; j < s; j++)
		{
			(*grid)[i][j].setPosition(Vector2f(i*100.f,35+j*100.f));
		}
	}
}

void set_color(Grid *grid,Plateau *plateau){
	int s = size(*plateau);
	for (int i = 0; i < s; i++){
		for (int j = 0; j < s; j++){
			int level = max(int(255 - log2((*plateau)[i][j]+1)*21),0);
			(*grid)[j][i].setFillColor(Color(255,level,level));
		}
	}
}



void draw_grid(RenderWindow *window ,Grid *grid){
	int s = size(*grid);
	for (int i = 0; i < s; i++){
		for (int j = 0; j < s; j++){
			(*window).draw((*grid)[i][j]);
		}
	}
}

void draw_text(RenderWindow *window,Plateau *plateau){
	int s = size(*plateau);
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
	for(int i = 0; i < s;i++){
		for(int j = 0;j < s; j++){
			Text text;
			string str;

			int val = (*plateau)[i][j];
			if(val==0){
				str = " ";
			} else{str = to_string(val);}
		
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
	int s;
  	cout << "taille du plateau :";
  	cin >> s;

	RenderWindow window(VideoMode(100*s-10,100*s+25), "jeu2048");
	Grid grid = init_grid(s);
	set_positions(&grid);
	window.clear(Color::Black);

	startagain:
	srand(time(NULL));
	Plateau init = plateauInitial(s);
	Plateau old = plateauVide(s);
	int c;
	bool cont = false;
	draw_update(&window,&grid,&init);
	initscr();
	keypad(stdscr, true);

	loop:
	do  {
		c = getch();
		if(c!=255)clear();
		old = init;
		deplacement(&init, c);
		if(old!=init){
			rgen(&init);
		} 
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			}
		}
		draw_update(&window,&grid,&init);
	} while (window.isOpen() && c!=113 && (cont || !estGagnant(&init)) && !estTermine(&init));

	if (estGagnant(&init)){
		window.clear(Color::Black);
		Text text;
		Font font;
		font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");

		string str = "Vous avez gagne, BRAVO ! \nPour recommencer une partie, \nappuyez sur r,\nPour quitter, appyez sur q.\nSi vous souhaitez continuer votre partie \nactuelle, cliquez sur n \'importe quelle autre \ntouche";
		text.setFont(font);
		text.setFillColor(Color::White);
		text.setCharacterSize(20);
		text.setString(str);
		text.setPosition(Vector2f(0,130));
		window.draw(text);
		window.display();

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

			window.clear(Color::Black);
			Text text;
				Font font;
			font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf");

			string str = "Partie terminee ! _\nPour recommencer, pressez r\nSinon, pressez n'importe quelle \nautre touche";
			text.setFont(font);
			text.setFillColor(Color::White);
			text.setCharacterSize(20);
			text.setString(str);
			text.setPosition(Vector2f(0,130));
			window.draw(text);
			window.display();

			c = getch();
			if(c==r) goto startagain;
			else goto end;
		}
	
	end:
	endwin();
	return 0;
}