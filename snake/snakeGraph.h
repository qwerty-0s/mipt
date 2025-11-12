#ifndef SNAKEGRAPH_H
#define SNAKEGRAPH_H

#include <FL/Fl_Window.H>
#include "snakeBack.h"  

class Game_Window : public Fl_Window {
private:
    snake* player;
    int cell_size;
    SnakeBackground background; 

public:
    Game_Window(int w, int h, snake* s, int cell_size = 20);

    int handle(int event) override;
    void draw() override;
    int get_cell_size();
    snake* get_player();
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