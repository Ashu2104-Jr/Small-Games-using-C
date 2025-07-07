#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#define max1 10
#define max2 30
#define pmax 10
int arr[max1][max2];
typedef struct{   
    int a;
    int b;
    int size;
}poll;
int score=0;
int flag=0;
poll dino;
poll ar[pmax];
int start=0;
int end=0;
int iscorrect()
{
    int i=0;
    int j=ar[start].a;
    while(i<ar[start].size)
    {
        if(j==dino.a && ar[start].b==dino.b)
        {
            exit(0);
        }
        j--;
        i++;
    }
}
void setn(int a,int b)
{
    arr[a][b]='6';
}
void create_poll()
{
    int cnt=end;
    ar[cnt].size=rand()%5;
    ar[cnt].a=max1-1;
    ar[cnt].b=max2-2;
    end=(end+1)%pmax;
}
void remove_poll()
{
    start=(start+1)%pmax;
}
void generate_tile(int s,int d,int cou)
{
    for(int i=0;i<cou;i++)
    {
        s=s-1;
        setn(s,d);
    }
}
void degreate_tile(int s,int d,int cou)
{
    for(int i=0;i<cou;i++){
        s=s-1;
        arr[s][d]=' ';
    }
}
void continuous_tile()
{
    int l=start;
    while(l!=end)  
    {
        if(ar[l].b!=0 )
        {
            degreate_tile(ar[l].a,ar[l].b,ar[l].size);
            ar[l].b=ar[l].b-1;
            generate_tile(ar[l].a,ar[l].b,ar[l].size);
            l=(l+1)%pmax;
        }
        else
        {
            degreate_tile(ar[l].a,ar[l].b,ar[l].size);
            remove_poll();
            l=start;
        }
    }
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
    int k=1;
    iscorrect();
    printf("score : %d\n",score);
    for(int i=0;i<max1;i++)
    {
        for(int j=0;j<max2;j++)
        {
            if(k==1 || k==max1)
            {
                printf("* ");
            }
            else
            {
                if(j==0 || j==max2)
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
    score++;
    usleep(80000);
    iscorrect();
}
int jump()
{
    int i=dino.a;
    int j=dino.b;
    for(int i=0;i<5;i++)
    {
        arr[dino.a][dino.b]=' ';
        dino.a=dino.a-1;
        setn(dino.a,dino.b);
        if(i%2==0)
        {
            continuous_tile();
        }
        print();
    }    
    while(dino.a!=i)
    {
        arr[dino.a][dino.b]=' ';
        dino.a=dino.a+1;
        setn(dino.a,dino.b);
        if(dino.a%2==0)
        {
            continuous_tile();
        }
        print();
    }
}
int main()
{
    int o=0;
    dino.a=8;
    dino.b=2;
    dino.size=1;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            arr[i][j]=' ';
        }
    }
    create_poll();
    setn(dino.a,dino.b);
    print();
    generate_tile(ar[start].a,ar[start].b,ar[start].size);
    while(1)
    {
        int ch=kbhit(100);
        if(ch)
        {
            if(ch==32)
            {
                jump();
            }
            else if(ch=='q')
            {
                return 0;
            }    
        } 
        continuous_tile();  
        if(flag==1)
        {
            break;
        }
        if(o==7)
        {
            create_poll();
            o=0;
        }
        o++;           
        print();   
    }
}