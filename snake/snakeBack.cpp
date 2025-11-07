
#include "snakeBack.h"

snake::snake(int x, int y)
{
    int  i = 0; 
    snake_body_x[0] = x;
    snake_body_y[0] = y;
    max_length = 5;
    for (i=1; i<max_length; i++)
    {
        snake_body_x[i] = x-i; 
        snake_body_y[i] = y;
    }
}

void snake::move()
{
    int i = max_length; 
    for (i = max_length-1; i>0; i--)
    {
        snake_body_x[i] = snake_body_x[i-1];
        snake_body_y[i] = snake_body_y[i-1];
    }

    switch (dir)
    {
        case UP   : snake_body_y[0] ++; break;
        case DOWN : snake_body_y[0] --; break;
        case LEFT : snake_body_x[0] --; break;
        case RIGHT: snake_body_x[0] ++; break; 
    }

}

int snake::len()
{
    return max_length;
}

int snake::get_snake_coordinates_x(int n)
{
    return snake_body_x[n];
}

int snake::get_snake_coordinates_y(int n)
{
    return snake_body_y[n];
}

void snake::set_direction(direction d)
{
    dir = d;
}