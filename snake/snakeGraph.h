#ifndef SNAKEGRAPH_H
#define SNAKEGRAPH_H

#include <FL/Fl_Window.H>
#include "snakeBack.h"  

class Game_Window : public Fl_Window {
private:
    snake* player1;
    snake* player2;
    int cell_size;
    food* meal; 
    SnakeBackground background; 

public:
    Game_Window(int w, int h, snake* p1, snake* p2, int cell_size = 20);
    ~Game_Window();

    int handle(int event) override;
    void draw() override;
    int get_cell_size();
    snake* get_player1();
    snake* get_player2();
    food* get_meal();
};

class BackgroundWindow : public Fl_Window {
private:
    SnakeBackground background;
    
public:
    BackgroundWindow(int w, int h, const char* title = nullptr);
    void draw() override;
    int handle(int event) override;
};

#endif