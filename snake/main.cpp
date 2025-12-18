#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "snakeBack.h"
#include "snakeGraph.h"

int global_time = 0;

void game_tick(void* userdata) {
    Game_Window* window = static_cast<Game_Window*>(userdata);
    snake* p1 = window->get_player1();
    snake* p2 = window->get_player2();
    food* meal = window->get_meal();
    int cellsize = window->get_cell_size(); 
    int max_width  = window->w() / cellsize;
    int max_height = window->h() / cellsize;
    int Time;
    global_time += 1;
    Time = global_time / 10; 
      
    if (p1) p1->move();
    if (p2) p2->move();

    bool grow1 = p1 && p1->grow(meal);
    bool grow2 = p2 && p2->grow(meal);
    if ((grow1 || grow2) && meal) {
        meal->respawn(max_width, max_height);
    }

    auto head_hits_other = [](snake* headSnake, snake* other) -> bool {
        if (!headSnake || !other) return false;
        int hx = headSnake->get_snake_coordinates_x(0);
        int hy = headSnake->get_snake_coordinates_y(0);
        for (int i = 0; i < other->len(); ++i) {
            if (hx == other->get_snake_coordinates_x(i) &&
                hy == other->get_snake_coordinates_y(i)) {
                return true;
            }
        }
        return false;
    };

    bool collision_win_p1 = (p2 && p2->check_collision(max_width, max_height)) || head_hits_other(p2, p1);
    bool collision_win_p2 = (p1 && p1->check_collision(max_width, max_height)) || head_hits_other(p1, p2);

    if (collision_win_p1 && collision_win_p2)
    {
        printf("GAME OVER \n");
        printf("no one win\n");
        Fl::remove_timeout(game_tick, userdata);
        return;
    }

    if (collision_win_p1){
        printf("GAME OVER \n");
        printf("player WHITE win\n");
        Fl::remove_timeout(game_tick, userdata);
        return;
    }

    if (collision_win_p2){
        printf("GAME OVER \n");
        printf("player GREEN win\n");
        Fl::remove_timeout(game_tick, userdata);
        return;
    }

    if(Time >= 60){
        printf("GAME OVER \n");
        if (p1->len() > p2->len()){
            printf("player WHITE win\n");
        }
        else if (p2->len() > p1->len()){
            printf("player GREEN win\n");
        }
        else{
            printf("no one win\n");
        }
        Fl::remove_timeout(game_tick, userdata);
        return;
    }
    
    window->redraw();
    printf("Time: %d seconds\n", global_time / 10);
    Fl::repeat_timeout(0.1, game_tick, userdata);
}

int main() {
    const int grid_w = 40;
    const int grid_h = 30;
    const int cell_size = 20;
    const int win_w = grid_w * cell_size;
    const int win_h = grid_h * cell_size;

    snake player1(grid_w - 6, grid_h / 2);   
    snake player2(grid_w / 4,    grid_h / 2); 
    player1.set_direction(snake::UP);
    
    Game_Window window(win_w, win_h, &player1, &player2, cell_size);
    window.show();
    window.take_focus();

    Fl::add_timeout(0.1, game_tick, &window);

    return Fl::run();
}