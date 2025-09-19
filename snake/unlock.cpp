#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

void setNonBlocking(bool enable) {
    termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (enable) {
        ttystate.c_lflag &= ~(ICANON | ECHO); // без буфера и эха
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // неблокирующий ввод
    } else {
        ttystate.c_lflag |= ICANON | ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
        fcntl(STDIN_FILENO, F_SETFL, 0);
    }
}

int main() {
    int i,j,g = 0;
    char pole [100][100];
    int snake_x[100];
    int snake_y[100];

    int snake_x1[100];
    int snake_y1[100];

    int max_length = 5;
    snake_x[0] = 10;
    snake_y[0] = 10;
    std::cout << "Нажмите клавишу (q для выхода):\n";
    setNonBlocking(true);
    bool game = 1;
    char c;
    char napr = 'd';


    setNonBlocking(true);

    while (game) {

        c = getchar();
        if (c != EOF) {   // если что-то нажато
            std::cout << "Нажато: " << c << "\n";
            napr = c;
            if (c == 'q') break;
        }



        for(i=max_length-1; i>0; i--)
        {
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }

        if(napr == 'w') snake_y[0]--;
        if(napr == 'a') snake_x[0]--;
        if(napr == 's') snake_y[0]++;
        if(napr == 'd') snake_x[0]++;

        for(i=1; i<max_length; i++)
        {
            if(snake_x[0]==snake_x[i]&&snake_y[0]==snake_y[i])
            {
                game = 0;
            }
        }

        if(snake_x[0] == 50 || snake_y[0] == 29 || snake_x[0] == 0 || snake_y[0] == 0)
        {
            game = 0;
        }
        
        for (i=0; i<30; i++)
        {
            for(j=0; j<50; j++)
                {
                    if(i==0||j==0 || i==29 ||j==49)
                    {
                        pole[i][j]='*';
                    }
                    else
                    {
                        pole[i][j]=' ';
                    }
                }
        }


        for(i=0;i<max_length;i++)
        {
            pole[snake_y[i]][snake_x[i]] = '@';
        }

        
        for (i=0; i<30; i++)
        {
            for(j=0; j<50; j++)
                {
                    std::cout<<pole[i][j];
                }
            std::cout << "\n";
        }


        std::cout << "Нажато: " << napr << "\n";
        usleep(100000); // 100 мс
        system("clear");
    }




    std::cout << "GAME OVER";
    setNonBlocking(false);
    return 0;
}
