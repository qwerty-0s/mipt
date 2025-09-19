#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
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


int main(){
	
	char		x[10];
	char           napr = 'w';
	unsigned	i,j,g;
	char pole[100][100];
	int snakex[100];
	int snakey[100];
        int snakex1[1000000];
        int snakey1[1000000];
        int kill;	
        int xeda=5;
        int yeda=5;
        unsigned k=5;


	snakex[0]=10;
	snakey[0]=10;
	
    setNonBlocking(true);
	
	           for(i=0;i<100;i++)
			{
			  for(j=0;j<100;j++)
			   {
			    if(i==50||j==50||i==0||j==0)
			    {
			     pole[i][j]='*';
		            }
		            else 
		            {
		             pole[i][j]=' ';
		            }
			  }
			}
                   
    
	while(1){
		usleep(1000000);

        napr = getchar();
        if (napr != EOF) {   // если что-то нажато
            std::cout << "Нажато: " << napr << "\n";
            if (napr == 'q') break;
            if (napr == 'w') std::cout << "вверх";
        }
        
			
                                   
			
			if(napr == 'w')
			{ 
			snakex[0]--;
			} 
			
		     	if(napr == 's') {
		     	snakex[0]++ ;
		     	}
		     	
			if(napr == 'd') {
			snakey[0]++ ;
			}
			
			if(napr == 'a') {
			snakey[0]-- ;
			}
			
			snakex1[g]=snakex[0];
			snakey1[g]=snakey[0];
					
			pole[snakex[0]][snakey[0]]= '\"';
			
			if(g>k)
			{
			pole[snakex1[g-k]][snakey1[g-k]]=' ';
                       }
                       
			for(i=0;i<51;i++)
			{
			 for(j=0;j<51;j++)
			 {
			   printf("%c ",pole[i][j]);
		         }
		         printf("\n");
			}
			
			
			
			
			
			if(snakex[0]>49||snakex[0]<1||snakey[0]>49||snakey[0]<1)
			{
			  system("clear");
			  printf("\n");
			  printf("\n");
			  printf("\n");
			  printf("                SNAKE IS DEAD                ");
			  printf("\n");
			  printf("                NOOOOOOOOOOOO                ");
			  printf("\n");
			  printf("                    !!!                      ");
			  break;
			}
			
		        if(g>10)
		        {
		         for(i=1;i<10;i++)
		          {
		            if(snakex[0]==snakex1[g-i]&&snakey[0]==snakey1[g-i])
		            {
		                system("clear");
		       	  printf("\n");
			          printf("\n");
			          printf("\n");
			          printf("                SNAKE IS DEAD                ");
		                  printf("\n");
			          printf("                NOOOOOOOOOOOO                ");
			          printf("\n");
			          printf("                    !!!                      ");
			          kill=1;
			          break;
		            }
		          
		          }
		          if(kill==1)
		          {
		            break;
		          }
		        }
		        if(snakex[0]==xeda&&snakey[0]==yeda)
		        {
		          k++;
		          xeda=rand()%50;
                   	   yeda=rand()%50;
		          pole[xeda][yeda]='+';
		         
		        }
		          if(k==5)
                       {
                        pole[xeda][yeda]='+';
                       }       
		
			
			usleep(100000);
			system("clear");
			
			g++;
			
			if (strcmp(x, "q") == 0) break;
		
	}

	                                                                                                 
                           	
                 
	setNonBlocking(false);
	return 0;
}

