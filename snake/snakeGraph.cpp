
#include "snakeGraph.h"
#include <FL/Fl.H>

Game_Window::Game_Window(int w, int h, snake* s, int cell_size_)
    : Fl_Window(w, h, "Snake"), player(s), cell_size(cell_size_) {}


int Game_Window::handle(int event) {
    if(event == FL_KEYDOWN) {
        switch(Fl::event_key()) {
            case FL_Up:    player->set_direction(snake::UP); break;
            case FL_Down:  player->set_direction(snake::DOWN); break;
            case FL_Left:  player->set_direction(snake::LEFT); break;
            case FL_Right: player->set_direction(snake::RIGHT); break;
        }
        return 1;
    }
    return Fl_Window::handle(event);
}

void Game_Window::draw() {
    Fl_Window::draw();

    for(int i = 0; i < player->len(); ++i) {
        int x = player->get_snake_coordinates_x(i) * cell_size;
        int y = player->get_snake_coordinates_y(i) * cell_size;
        fl_rectf(x, y, cell_size, cell_size);
    }
}

snake* Game_Window::get_player() {
    return player;
}