#include "snakeGraph.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <cctype>

Game_Window::Game_Window(int w, int h, snake* p1, snake* p2, int cell_size_)
    : Fl_Window(w, h, "Snake Game"), player1(p1), player2(p2), cell_size(cell_size_), meal(new food(w / cell_size_, h / cell_size_))
{
    end();
    take_focus();
}

Game_Window::~Game_Window() {
    delete meal;
}

int Game_Window::handle(int event) {
    if(event == FL_KEYDOWN || event == FL_SHORTCUT) {
        int key = Fl::event_key();
        const char* txt = Fl::event_text();
        char ch = (txt && txt[0]) ? static_cast<char>(std::tolower(static_cast<unsigned char>(txt[0]))) : 0;

        switch(key) {
            case FL_Up:    if (player1) player1->set_direction(snake::UP);    return 1;
            case FL_Down:  if (player1) player1->set_direction(snake::DOWN);  return 1;
            case FL_Left:  if (player1) player1->set_direction(snake::LEFT);  return 1;
            case FL_Right: if (player1) player1->set_direction(snake::RIGHT); return 1;
            case FL_Escape: hide(); return 1;
            default:
                break;
        }

        if (ch) {
            switch (ch) {
                case 'w': if (player2) player2->set_direction(snake::UP);    return 1;
                case 's': if (player2) player2->set_direction(snake::DOWN);  return 1;
                case 'a': if (player2) player2->set_direction(snake::LEFT);  return 1;
                case 'd': if (player2) player2->set_direction(snake::RIGHT); return 1;
                default: break;
            }
        }

        printf("Key pressed: key=%d orig=%d text='%c' (code %d)\n",
               key, Fl::event_original_key(),
               ch ? ch : '?', ch ? static_cast<int>(ch) : -1);
        return 0;
    }
    return Fl_Window::handle(event);
}

void Game_Window::draw() {
    Fl_Window::draw();
    
    
    fl_color(8, 5, 26);
    fl_rectf(0, 0, w(), h());
   
    fl_color(25, 25, 50); 
    for (int x = 0; x <= w(); x += cell_size) {
        fl_line(x, 0, x, h());
    }
    for (int y = 0; y <= h(); y += cell_size) {
        fl_line(0, y, w(), y);
    }

    if (meal) {
        fl_color(FL_RED);
        int meal_x = meal->getX() * cell_size;
        int meal_y = meal->getY() * cell_size;
        fl_rectf(meal_x, meal_y, cell_size, cell_size);
    }
    

    if (player1) {
        fl_color(FL_GRAY);
        for(int i = 0; i < player1->len(); ++i) {
            int x = player1->get_snake_coordinates_x(i) * cell_size;
            int y = player1->get_snake_coordinates_y(i) * cell_size;
            fl_rectf(x, y, cell_size, cell_size);
        }
        if (player1->len() > 0) {
            fl_color(FL_WHITE);
            int x = player1->get_snake_coordinates_x(0) * cell_size;
            int y = player1->get_snake_coordinates_y(0) * cell_size;
            fl_rectf(x, y, cell_size, cell_size);
        }
    }

    if (player2) {
        fl_color(FL_GREEN);
        for(int i = 0; i < player2->len(); ++i) {
            int x = player2->get_snake_coordinates_x(i) * cell_size;
            int y = player2->get_snake_coordinates_y(i) * cell_size;
            fl_rectf(x, y, cell_size, cell_size);
        }
        if (player2->len() > 0) {
            fl_color(FL_YELLOW);
            int x = player2->get_snake_coordinates_x(0) * cell_size;
            int y = player2->get_snake_coordinates_y(0) * cell_size;
            fl_rectf(x, y, cell_size, cell_size);
        }
    }
}

int Game_Window::get_cell_size() {
    return cell_size;
}

snake* Game_Window::get_player1() {
    return player1;
}

snake* Game_Window::get_player2() {
    return player2;
}

food* Game_Window::get_meal() {
    return meal;
}

BackgroundWindow::BackgroundWindow(int w, int h, const char* title) 
    : Fl_Window(w, h, title), background(w, h)
{
    end();
}

void BackgroundWindow::draw() {
    Fl_Window::draw();
    background.draw();
}

int BackgroundWindow::handle(int event) {
    if (event == FL_KEYDOWN && Fl::event_key() == FL_Escape) {
        hide();
        return 1;
    }
    return Fl_Window::handle(event);  
}