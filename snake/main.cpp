#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "snakeBack.h"
#include "snakeGraph.h"


void game_tick(void* userdata) {
    Game_Window* window = static_cast<Game_Window*>(userdata);
    snake* p = window->get_player();
    p->move();
    window->redraw();
    Fl::repeat_timeout(0.2, game_tick, userdata); // повторяем
}

int main() {
    const int grid_w = 20;
    const int grid_h = 20;
    const int cell = 20;
    const int win_w = grid_w * cell;
    const int win_h = grid_h * cell;

    snake player(5, 5);
    Game_Window window(win_w, win_h, &player, cell);
    window.show();

    Fl::add_timeout(0.2, game_tick, &window);

    return Fl::run();
}