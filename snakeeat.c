#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
typedef struct{
    int x;
    int y;
}cor; 
typedef struct{
    cor data;
}snake;
typedef struct{
    snake ar[100];
    int head;
    int cur;
}s;
#define n 20
int a=5;
int b=2;
int flag=1;
char set;
char arr[20][20];
int count=0;
s s1;

void create()
{
    s1.ar[s1.cur].data.x=a;
    s1.ar[s1.cur].data.y=b;
    s1.cur++;
}
void clear_screen() {
    printf("\033[H\033[J");
}
char getch() {
    struct termios oldt, newt;
    char ch;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // Set new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read a single character
    read(STDIN_FILENO, &ch, 1);

    // Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
int kbhit(int timeout_ms) {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO); // raw mode
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    struct timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    if (ret > 0) {
        int ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore mode
        return ch;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore mode
    return 0; // timeout: no key
}
void print()
{
    clear_screen();
    sleep(0.6);
    int k=1;
    printf("\nscore is %d\n",count);
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(k==1 || k==20)
            {
                printf("* ");
            }
            else
            {
                if(j==0 || j==19)
                {
                    printf("*");
                }
                else
                {
                    printf("%c ",arr[i][j]);
                }
            }
        }
        k++;
        printf("\n");
    }
    printf("\n");
}
void setn(int a,int b)
{
    arr[a][b]='9';	
}
void reset(int a,int b)
{
    arr[a][b]=' ';
}
void snakeset()
{
        cor temp; 
    	if(set=='w')
        {	
            a=a-1;
        }
        else if(set=='a')
        {		
            b=b-1;
        }
        else if(set=='s')
        {	
            a=a+1;
        }
        else if(set=='d')
        {	
            b=b+1;
        }
        int f=a;
        int k=b;
        int i=0;
        while(i<s1.cur)
        {
            temp.x=s1.ar[i].data.x;
            temp.y=s1.ar[i].data.y;
            s1.ar[i].data.x=f;
            s1.ar[i].data.y=k;
            setn(s1.ar[i].data.x,s1.ar[i].data.y);
            f=temp.x;
            k=temp.y;
	        i++;
        }
        reset(temp.x,temp.y);
        print();
}
void increase()
{
        create();
    	if(set=='w')
        {	
            s1.ar[s1.cur-1].data.x=(s1.ar[s1.cur-2].data.x+1);
            s1.ar[s1.cur-1].data.y=b;
        }
        else if(set=='a')
        {		
            s1.ar[s1.cur-1].data.x=a;
            s1.ar[s1.cur-1].data.y=(s1.ar[s1.cur-2].data.y+1);
        }
        else if(set=='s')
        {	
            s1.ar[s1.cur-1].data.x=(s1.ar[s1.cur-2].data.x-1);
            s1.ar[s1.cur-1].data.y=b;
        }
        else if(set=='d')
        {	
            s1.ar[s1.cur-1].data.x=a;
            s1.ar[s1.cur-1].data.y=(s1.ar[s1.cur-2].data.y-1);
        }
        
}
int main() {
    int i,j;
    int ch;
    s1.cur=0;
    create();
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            arr[i][j]=' ';
        }
    }
    snakeset();
    while(a!=0 && b!=19 && b!=0 && a!=19)
    {
        ch=kbhit(100);
        if(ch!=113)
        {
            set=ch;
        }
        else
        {
            break;
        }
        if(flag==1)
        {		
            i=rand()%19;
            j=rand()%19;
	    if(i!=a && j!=b && i!=0 && j!=0)
	    {		
            	setn(i,j);
            	flag=0;
	    }	
        }
	if(i==a && j==b)
	{
		flag=1;
        increase();
		count=count+10;
    	}
    	snakeset();
    }
    clear_screen();
    printf("\nGame over\nyour score is %d\n",count);
}
