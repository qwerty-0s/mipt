

#ifndef SNAKEBACK_H
#define SNAKEBACK_H

class snake {
public:
    enum direction {UP, DOWN, LEFT, RIGHT};
    snake(int x, int y);

    void move();
    void set_direction(direction d);
    bool check_collision(int max_width, int max_height);

    int len();
    int get_snake_coordinates_x(int n);
    int get_snake_coordinates_y(int n);

private:
    int snake_body_x[100];
    int snake_body_y[100];
    int max_length;
    direction dir = RIGHT;
};

#endif 

