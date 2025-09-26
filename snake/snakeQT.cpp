#include <iostream>
#include <unistd.h>

class snake
{
    private:
        int snake_body_x[100];
        int snake_body_y[100];
        int max_length;
    public:
        snake (int x, int y); //start of snake 

        int len();
        int get_snake_coordinates(int n);

        void move();
        void move_head_right();
        void move_head_left();
        void move_head_up();
        void move_head_down(); 

};

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
}

int snake::len()
{
    return max_length;
}

int snake::get_snake_coordinates(int n)
{
    return snake_body_x[n];
}

int main()
{
    snake player1(10,10);
    int  i = 0; 
    for(i = 0;i<player1.len(); i++)
    {
        std::cout<<player1.get_snake_coordinates(i)<<"\n"; 
    }

}