



#ifndef SNAKEGRAPH_H
#define SNAKEGRAPH_H

#include <FL/Fl_Window.H>
#include "snakeBack.h"  
#include <FL/fl_draw.H>

class Game_Window : public Fl_Window {
private:
    snake* player;
    int cell_size = 10;

public:
    Game_Window(int w, int h, snake* s, int cell_size = 10);

    int handle(int event) override;
    void draw() override;
    int get_cell_size();

    snake* get_player();
};

#endif 
