



#ifndef SNAKEGRAPH_H
#define SNAKEGRAPH_H

#include <FL/Fl_Window.H>
#include "snakeBack.h"  
#include <FL/fl_draw.H>

class Game_Window : public Fl_Window {
private:
    snake* player;
    int cell_size = 20;

public:
    Game_Window(int w, int h, snake* s, int cell_size = 20);

    int handle(int event) override;
    void draw() override;

    snake* get_player();
};

#endif 
