#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct
{
	int row, col;
}win_size_t;

void drawTable(win_size_t winsize, int nums[][4]);
void getBornField(int *y, int *x);
void writeNums(win_size_t winsize, int y, int x);
void printArray(int nums[][4]);
int upMoveMaker(int nums[][4]);
int leftMoveMaker(int nums[][4]);
int overControl(int nums[][4]);
int downMoveMaker(int nums[][4]);
int rightMoveMaker(int nums[][4]);
void newBorn(int nums[][4]);


int main()
{
	int row, col;
	int flag=1, flagLeft=1;
	int y, x;
	int i, j;
	int nums[4][4]={0};
	int command;
	win_size_t winsize;
	
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);
	noecho();
	timeout(TRUE);
	
	getmaxyx(stdscr, winsize.row, winsize.col);
		
	getBornField(&y, &x);
	nums[y][x] = 2;
	getBornField(&y, &x);
	nums[y][x] = 2;

	while(1)
	{	
		drawTable(winsize, nums);
		refresh();
		command = getch();
		
		if(command == KEY_UP)
		{
			while(flag)
				flag = upMoveMaker(nums);			
		
			newBorn(nums);
			flag=1;
		}
		
		else if(command == KEY_LEFT)
		{
			while(flag)
				flag = leftMoveMaker(nums);
			
			newBorn(nums);			
			flag=1;
			
		}
		else if(command == KEY_RIGHT)
		{
			while(flag)
				flag = rightMoveMaker(nums);
			
			newBorn(nums);
			flag=1;
		}
		else if(command == KEY_DOWN)
		{
			while(flag)
				flag = downMoveMaker(nums);
			
			newBorn(nums);
			flag=1;
		}
			
		if(!overControl(nums))
			break;
		
		clear();
		usleep(100000);
	}
	
	getchar();
	endwin();
	return 0;
}


void drawTable(win_size_t winsize, int nums[][4])
{
	int i, j, a, b;
	
	mvprintw(winsize.row/2-2, winsize.col/2-2, "---------------------");
	for(i=-1; i < 3; i++)
	{
		for(j=-2; j < 19; j+=5)
			mvprintw(winsize.row/2+i, winsize.col/2+j, "|");
	}
	
	for(a=0, i=-1; a < 4; i++, a++)
	{
		for(b=0,j=-2; b < 4; j+=5, b++)
			mvprintw(winsize.row/2+i, winsize.col/2+j+1, "%d", nums[a][b]);	
	}
	mvprintw(winsize.row/2+3, winsize.col/2-2, "---------------------");
}

void getBornField(int *y, int *x)
{
	*y = rand() % 4;
	*x = rand() % 4;
}


void printArray(int nums[][4])
{
	int i,j;
	
	printf("\n");
	for(i=0; i < 4; i++)
	{
		for(j=0; j<4; j++)
			printf("%d  ", nums[i][j]);
		printf("\n");
	}
}


int upMoveMaker(int nums[][4])
{
	int flag=0;
	static int flag_2=0;
	int i, j;
	
	for(i=0; i < 4; i++)
		{
			for(j=0; j<4; j++)
			{
				if(nums[i][j] != 0 && i != 0)
				{
					flag++;
					if(nums[i-1][j] == 0)
					{
						nums[i-1][j] = nums[i][j];
						nums[i][j] = 0;
					}
					else if(nums[i-1][j] == nums[i][j])
					{
						nums[i-1][j] += nums[i][j];
						nums[i][j] = 0;
					}
					else
						flag=0;
				}
			}		
		}
	return flag;
}


int leftMoveMaker(int nums[][4])
{
	int flag=0;
	static int flag_2=0;
	int i, j;
	
	for(i=0; i < 4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(nums[i][j] != 0 && j != 0)
			{
				flag++;
				if(nums[i][j-1] == 0)
				{
					nums[i][j-1] = nums[i][j];
					nums[i][j] = 0;
				}
				else if(nums[i][j-1] == nums[i][j])
				{
					nums[i][j-1] += nums[i][j];
					nums[i][j] = 0;
				}
				else
					flag=0;
			}
		}		
	}
	return flag;
}



int downMoveMaker(int nums[][4])
{
	int flag=0;
	static int flag_2=0;
	int i, j;
	
	for(i=0; i < 4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(nums[i][j] != 0 && i != 3)
			{
				flag++;
				if(nums[i+1][j] == 0)
				{
					nums[i+1][j] = nums[i][j];
					nums[i][j] = 0;
				}
				else if(nums[i+1][j] == nums[i][j])
				{
					nums[i+1][j] += nums[i][j];
					nums[i][j] = 0;
				}
				else
					flag=0;
			}
		}		
	}
	return flag;
}



int rightMoveMaker(int nums[][4])
{
	int flag=0;
	int flag_2=0;
	int i, j;
	
	mvprintw(1,1,"%d", flag_2);
	
	for(i=0; i < 4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(nums[i][j] != 0 && j != 3)
			{
				flag++;
				if(nums[i][j+1] == 0)
				{
					nums[i][j+1] = nums[i][j];
					nums[i][j] = 0;
				}
				else if(nums[i][j+1] == nums[i][j])
				{
					nums[i][j+1] += nums[i][j];
					nums[i][j] = 0;
				}
				else
					flag=0;
			}
		}		
	}
	mvprintw(2,1,"%d", flag_2);
	return flag;
}


int overControl(int nums[][4])
{
	int flag=0;
	int i, j;
	
	for(i=0; i < 4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(nums[i][j] == 0)
				flag++;
			else if(j != 0 && nums[i][j] == nums[i][j-1])
				flag++;
			else if(i != 0 && nums[i][j] == nums[i-1][j])
				flag++;
		}
	}
	return flag;
}


void newBorn(int nums[][4])
{
	int y, x;
	getBornField(&y, &x);
	if(nums[y][x] == 0)
		nums[y][x] = 2;
	
}
