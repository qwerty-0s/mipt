#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "snakeBack.h"
#include "snakeGraph.h"


void game_tick(void* userdata) {
    Game_Window* window = static_cast<Game_Window*>(userdata);
    snake* p = window->get_player();
    int cellsize = window->get_cell_size(); 
    int max_width  = window->w() / cellsize;
    int max_height = window->h() / cellsize;
    p->move();
    if (p->check_collision(max_width, max_height)){
        printf("GAME OVER");
        return;
    }
    window->redraw();
    Fl::repeat_timeout(0.1, game_tick, userdata);
}

int main() {
    const int grid_w = 20;
    const int grid_h = 20;
    const int cell = 10;
    const int win_w = grid_w * 30;
    const int win_h = grid_h * 30;

    snake player(5, 5);
    Game_Window window(win_w, win_h, &player, cell);
    window.show();
    window.take_focus();

    Fl::add_timeout(0.1, game_tick, &window);

    return Fl::run();
}