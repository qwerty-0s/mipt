#ifndef SNAKEBACK_H
#define SNAKEBACK_H

#include <FL/Fl.H>

class food;

class snake {
public:
  enum direction { UP, DOWN, LEFT, RIGHT };
  snake(int x, int y);

  void move();
  void set_direction(direction d);
  bool grow(food *meal);
  bool check_collision(int max_width, int max_height);

  int len();
  int get_snake_coordinates_x(int n);
  int get_snake_coordinates_y(int n);

private:
  int snake_body_x[100];
  int snake_body_y[100];
  int max_length;
  direction dir = RIGHT;
  bool direction_locked = false;
};

class SnakeBackground {
private:
  int width;
  int height;
  int cellSize;

public:
  SnakeBackground(int w = 800, int h = 600, int cell = 20);
  void draw();
};

class food {
private:
  int x;
  int y;
  Fl_Color color;
  int color_timer;

public:
  food(int max_width, int max_height);

  int getX();
  int getY();
  Fl_Color getColor();

  void respawn(int max_width, int max_height);
  void update_color();
};
#endif