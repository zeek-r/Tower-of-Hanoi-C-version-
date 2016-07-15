#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#define MAX 10

int array[MAX][MAX], size, ch[2], counter = 0;

void clear(void);
void init(void);
void greet(void);
bool won(void);
void draw(void);
void move(void);



int main(void)
{	
	do
	{
		printf("Please enter the length of the tower(0-10): ");
		scanf("%d", &size);
	}while(size > 10 || size < 0);
	clear();
	greet();
	init();
	while(true)
	{
		if(counter > 0)
		{
			clear();
			greet();
		}
			
		draw();
		printf("\nChoice: ");
		
		if(counter == 0)
		printf("**Please select the block number and shaft(for  block 1 to shaft 2 enter: 1, 2): ");
		scanf("%d %d", &ch[0], &ch[1]);
		move();
		if(won())
		{
			clear();
			printf("Game Won!!\nOptimal Solution: %.1f\n", pow(2,size)-1);
			draw();
			break;
		}
	}
	return 0;
}

void init(void)
{
	FILE *fp;
	fp = fopen("game_log.txt", "a");
	if(counter == 0)
	{
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(j == 0)
				{
					array[i][j] = i+1;
					fprintf(fp,"%d ", array[i][j]);
				}
	
				else
				{
					array[i][j] = 0;
					fprintf(fp, "%d ", array[i][j]);
				}
				fprintf(fp, "|");
			}
		fprintf(fp, "\n");
		}
	}
	else
	{
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				fprintf(fp, "%d ", array[i][j]);
			}
			fprintf(fp, "|");
		}
	fprintf(fp, "\n");
	}
	fclose(fp);
}

void greet(void)
{
	char c[30];
	strcpy(c, "TOWER OF HANOI");
	printf("\t\t\t\tTOWER OF HANOI\n\t\t\t\t");
	for(int i = 0; i < strlen(c); i++)
	{
		printf("_");
		
	}
	printf("\n\n");
	usleep(500000);
}

void clear(void)
{
	printf("\e[1;1H\e[2J");
}

void draw(void)
{
	printf("\t\tShaft %d\t\t\tShaft %d\t\t\tShaft %d\n\n", 1, 2, 3);
	for(int i = 0; i < size; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(array[i][j] == 0)
			{
				printf("\t\t-\t");
			}
			else
			printf("\t\t%d\t", array[i][j]);
		}
		printf("\n");
	}
	if(counter > 0)
	{
		printf("Steps used:%d\t\t\n", counter);
	}
}

void move(void)
{
	int illegal = 0;
	int k = ch[0], l = ch[1];
	int c = 0, d = 0, e = 0, f = 0;
	if((k  > size  || k < 1) || (l > 3 || l < 1))
	{
		illegal = 1;
	}
		for(int i = 0; i <= size - 1; i++)
		{
			for(int j = 0; j <= l - 1; j++)
			{
				if(array[i][j] == 0 && j == l - 1)
				{
					c = i;
					d = j;
				}
			}
		}
		
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(k  == array[i][j])
				{
					e = i; 
					f = j;
					for(int a = i; a >= 0; a--)
					{
						if(k > array[i-1][j] && i != 0 && array[i-1][j] != 0 )
						illegal = 1;
					}
					
					if((array[c+1][d] != 0) && k > array[c+1][d])
					{
							illegal = 1;
					}
					
					if(array[e][f] == array[c][d] || array[e][f] == array[c+1][d])
					{
						illegal = 2;
					}
				}
			}
			
		}
		if(illegal == 1)
		{
			printf("Illegal Move!!, Select another block\n");
			usleep(1500000);
		}
		
		else if(illegal == 2)
		{
			counter++;
		}
		else
		{
			array[c][d] = k;
			array[e][f] = 0;		
			counter++;
		}
	
}

bool won(void)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 2; j < 3; j++)
		{
			if( j == 2 && array[i][j] != i+1)
			{
				return false;
			}
		}
	}
return true;
}

