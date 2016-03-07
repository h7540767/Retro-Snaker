#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <curses.h>
#include <fcntl.h>
#include <list>
#include <stdlib.h>

using namespace std;

struct node
{
	int x;
	int y;
	int temp[2];
};

int main()
{

	WINDOW * win = initscr();
	
	clear();
	
	
	char buff=0;
	char directionkey=0;
	char speedkey=0;
	
	int ymax = COLS;
	int xmax = LINES;
	int numofsnake = 5;
	int delayms = 100;
	
	list<int> xlist;
	list<int> ylist;
	list<int>::iterator it;
	
	
	struct node snake[(xmax-2)*(ymax-2)];
	struct node apple;
	
	apple.x = xmax-2;
	apple.y = ymax-2;
	
	for(int i = 0;i<5;i++)
	{
		snake[i].x = 1;
		snake[i].y = i+1;
		snake[i].temp[0] = snake[i].x;
		snake[i].temp[1] = snake[i].y;
	}

	box(stdscr, ACS_VLINE, ACS_HLINE);

	refresh();

	noecho();

    curs_set(0);

	fcntl(0,F_SETFL, O_NONBLOCK);
	
	mvaddch(snake[0].x,snake[0].y,'@');
	mvaddch(snake[1].x,snake[1].y,'*');
	mvaddch(snake[2].x,snake[2].y,'*');
	mvaddch(snake[3].x,snake[3].y,'*');
	mvaddch(snake[4].x,snake[4].y,'*');
	
	mvaddch(apple.x,apple.y,'^');
	
	while(true)
	{
		
		srand(time(0));

		xlist.clear();
		for(int i = 1;i<xmax-1;i++)
			xlist.push_back(i);

		ylist.clear();
		for(int i = 1;i<ymax-1;i++)
			ylist.push_back(i);
		
		buff = getch();

		if(buff != -1&&buff !='k'&&buff !='l')
		directionkey = buff;
        
		switch(directionkey)
		{
			case 'w':
			mvaddch(snake[0].x,snake[0].y,' ');
			snake[0].x--;
			
			if(snake[0].x<1)
			    snake[0].x = xmax-2;
			
			for(int i = 1;i<numofsnake;i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			{
				clear();
				mvaddstr(xmax/2,ymax/2,"Game Over!");
				mvaddstr(xmax/2+1,ymax/2,"Press T To Exit.");
				refresh();
				while(1)
				{
					buff = getch();
					if(buff == 't')
					{
						clear();
						refresh();
						endwin();
						return 0;
					}
				}
				
			}
			
			mvaddch(snake[0].x,snake[0].y,'@');
			
			if(snake[0].x == apple.x && snake[0].y == apple.y)
			{
				for(int i = 0;i<numofsnake;i++)
				{
					xlist.remove(snake[i].x);
					ylist.remove(snake[i].y);
				}
				
				it = xlist.begin();
				for(int i =0;i<rand()%xlist.size();i++)
					it++;
				apple.x = *it;
				
				it = ylist.begin();
				for(int i =0;i<rand()%ylist.size();i++)
					it++;
				apple.y = *it;

				mvaddch(apple.x,apple.y,'^');
				
				//吃完苹果后对新增节点做初始化
				numofsnake++;
				snake[numofsnake-1].x = snake[numofsnake-2].x;
				snake[numofsnake-1].y = snake[numofsnake-2].y;
				snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
				snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			}
			//蛇开始移动
			for(int i = 1;i<numofsnake;i++)
			{
				mvaddch(snake[i].x,snake[i].y,' ');
				snake[i].x = snake[i-1].temp[0];
				snake[i].y = snake[i-1].temp[1];
				mvaddch(snake[i].x,snake[i].y,'*');
				snake[i-1].temp[0] = snake[i-1].x;
				snake[i-1].temp[1] = snake[i-1].y;
			}
			snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
			snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			
			break;
			
			case 's':
			mvaddch(snake[0].x,snake[0].y,' ');
			
			snake[0].x++;
			if(snake[0].x>xmax-2)
			    snake[0].x = 1;
			
			for(int i = 1;i<numofsnake;i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			{
				clear();
				mvaddstr(xmax/2,ymax/2,"Game Over!");
				mvaddstr(xmax/2+1,ymax/2,"Press Any T To Exit.");
				refresh();
				while(1)
				{
					buff = getch();
					if(buff == 't')
					{
						clear();
						refresh();
						endwin();
						return 0;
					}
				}
				
			}
			
			mvaddch(snake[0].x,snake[0].y,'@');
			
			if(snake[0].x == apple.x && snake[0].y == apple.y)
			{
				for(int i = 0;i<numofsnake;i++)
				{
					xlist.remove(snake[i].x);
					ylist.remove(snake[i].y);
				}
				
				it = xlist.begin();
				for(int i =0;i<rand()%xlist.size();i++)
					it++;
				apple.x = *it;
				
				it = ylist.begin();
				for(int i =0;i<rand()%ylist.size();i++)
					it++;
				apple.y = *it;

				mvaddch(apple.x,apple.y,'^');
				
				//吃完苹果后对新增节点做初始化
				numofsnake++;
				snake[numofsnake-1].x = snake[numofsnake-2].x;
				snake[numofsnake-1].y = snake[numofsnake-2].y;
				snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
				snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			}
			
			for(int i = 1;i<numofsnake;i++)
			{
				mvaddch(snake[i].x,snake[i].y,' ');
				snake[i].x = snake[i-1].temp[0];
				snake[i].y = snake[i-1].temp[1];
				mvaddch(snake[i].x,snake[i].y,'*');
				snake[i-1].temp[0] = snake[i-1].x;
				snake[i-1].temp[1] = snake[i-1].y;
			}
			snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
			snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			
			break;
			
			case 'a':
			mvaddch(snake[0].x,snake[0].y,' ');
			
			snake[0].y--;
			if(snake[0].y<1)
			    snake[0].y = ymax-2;
			
			for(int i = 1;i<numofsnake;i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			{
				clear();
				mvaddstr(xmax/2,ymax/2,"Game Over!");
				mvaddstr(xmax/2+1,ymax/2,"Press Any T To Exit.");
				refresh();
				while(1)
				{
					buff = getch();
					if(buff == 't')
					{
						clear();
						refresh();
						endwin();
						return 0;
					}
				}
				
			}
			
			mvaddch(snake[0].x,snake[0].y,'@');
			
			if(snake[0].x == apple.x && snake[0].y == apple.y)
			{
				for(int i = 0;i<numofsnake;i++)
				{
					xlist.remove(snake[i].x);
					ylist.remove(snake[i].y);
				}
				
				it = xlist.begin();
				for(int i =0;i<rand()%xlist.size();i++)
					it++;
				apple.x = *it;
				
				it = ylist.begin();
				for(int i =0;i<rand()%ylist.size();i++)
					it++;
				apple.y = *it;

				mvaddch(apple.x,apple.y,'^');
				
				//吃完苹果后对新增节点做初始化
				numofsnake++;
				snake[numofsnake-1].x = snake[numofsnake-2].x;
				snake[numofsnake-1].y = snake[numofsnake-2].y;
				snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
				snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			}
			
			for(int i = 1;i<numofsnake;i++)
			{
				mvaddch(snake[i].x,snake[i].y,' ');
				snake[i].x = snake[i-1].temp[0];
				snake[i].y = snake[i-1].temp[1];
				mvaddch(snake[i].x,snake[i].y,'*');
				snake[i-1].temp[0] = snake[i-1].x;
				snake[i-1].temp[1] = snake[i-1].y;
			}
			snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
			snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			
			break;
			
			case 'd':
			mvaddch(snake[0].x,snake[0].y,' ');
			
			snake[0].y++;
			if(snake[0].y>ymax-2)
			    snake[0].y = 1;
			
			for(int i = 1;i<numofsnake;i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			{
				clear();
				mvaddstr(xmax/2,ymax/2,"Game Over!");
				mvaddstr(xmax/2+1,ymax/2,"Press Any T To Exit.");
				refresh();
				while(1)
				{
					buff = getch();
					if(buff == 't')
					{
						clear();
						refresh();
						endwin();
				        return 0;
					}
				}
				
			}
			
			mvaddch(snake[0].x,snake[0].y,'@');
			
			if(snake[0].x == apple.x && snake[0].y == apple.y)
			{
				for(int i = 0;i<numofsnake;i++)
				{
					xlist.remove(snake[i].x);
					ylist.remove(snake[i].y);
				}
				
				it = xlist.begin();
				for(int i =0;i<rand()%xlist.size();i++)
					it++;
				apple.x = *it;
				
				it = ylist.begin();
				for(int i =0;i<rand()%ylist.size();i++)
					it++;
				apple.y = *it;

				mvaddch(apple.x,apple.y,'^');
				
				//吃完苹果后对新增节点做初始化
				numofsnake++;
				snake[numofsnake-1].x = snake[numofsnake-2].x;
				snake[numofsnake-1].y = snake[numofsnake-2].y;
				snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
				snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			}
			
			for(int i = 1;i<numofsnake;i++)
			{
				mvaddch(snake[i].x,snake[i].y,' ');
				snake[i].x = snake[i-1].temp[0];
				snake[i].y = snake[i-1].temp[1];
				mvaddch(snake[i].x,snake[i].y,'*');
				snake[i-1].temp[0] = snake[i-1].x;
				snake[i-1].temp[1] = snake[i-1].y;
			}
			snake[numofsnake-1].temp[0] = snake[numofsnake-1].x;
			snake[numofsnake-1].temp[1] = snake[numofsnake-1].y;
			break;

			case 'c':
			clear();
			refresh();
			endwin();
			return 0;

			
			default:
			break;
		}
		
		if(buff == 'k')
			delayms += 10;
		if(delayms >500)
			delayms = 50;
		if(buff == 'l')
			delayms -=10;
		if(delayms <= 50)
			delayms = 500;
		
		napms(delayms);
		refresh();
		
	}



}
