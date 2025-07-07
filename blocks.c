#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#define cap 6
#define max1 25
#define max2 15
#define setn(a, b, arr) (arr[a][b] = '#')

int temp[4];
int s=0;
typedef struct{
    int a;
    int b;
}tempblock;
tempblock ar[cap];
int size=0;
char arr[max1][max2];
char array[4][4];
int max_occupy=0;
int hello=0;
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
void initalize(int m,int n,int flag){
    if(flag==0)
    {
        for(int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                arr[i][j]=32;
            }
        }
    }
    else
    {
        for(int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                array[i][j]=32;
            }
        }   
    }
}
void generate_block(int num){
    if(num==0)
    {
        num++;
    }
    switch(num){
        case 1:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=1;
               ar[2].b=3;
               ar[3].a=2;
               ar[3].b=2;
               size=4;
               break;
        case 2:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=1;
               ar[2].b=3;
               ar[3].a=2;
               ar[3].b=1;
               size=4;
               break;
        case 3:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=2;
               ar[2].b=2;
               ar[3].a=2;
               ar[3].b=3;
               size=4;
               break;
        case 4:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=1;
               ar[2].b=3;
               ar[3].a=1;
               ar[3].b=4;
               size=4;
               break;
        case 5:
               ar[0].a=1;
               ar[0].b=1;
               size=1;
               break; 
        case 6:
               ar[0].a=1;
               ar[0].b=2;
               ar[1].a=2;
               ar[1].b=1;
               ar[2].a=2;
               ar[2].b=2;
               ar[3].a=2;
               ar[3].b=3;
               ar[4].a=3;
               ar[4].b=2;
               size=5;
               break;
        case 7:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=2;
               ar[1].b=1;
               ar[2].a=3;
               ar[2].b=1;
               ar[3].a=4;
               ar[3].b=1;
               size=4;
               break;
        case 8:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=1;
               ar[2].b=3;
               size=3;
               break;
        case 9:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=2;
               ar[1].b=1;
               ar[2].a=2;
               ar[2].b=2;
               size=3;
               break;
        case 10:
               ar[0].a=1;
               ar[0].b=3;
               ar[1].a=2;
               ar[1].b=1;
               ar[2].a=2;
               ar[2].b=2;
               ar[3].a=2;
               ar[3].b=3;
               size=4;
               break;
        case 11:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=1;
               ar[2].b=3;
               size=3;
               break;
        case 12:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=2;
               ar[1].b=1;
               ar[2].a=2;
               ar[2].b=2;
               ar[3].a=3;
               ar[3].b=1;
               ar[4].a=3;
               ar[4].b=2;
               size=5;
               break;                
        case 13:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=2;
               ar[2].b=1;
               ar[3].a=2;
               ar[3].b=2;
               size=4;
               break;
        case 14:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=2;
               ar[2].a=2;
               ar[2].b=2;
               size=3;
               break;
        case 15:
               ar[0].a=1;
               ar[0].b=1;
               ar[1].a=1;
               ar[1].b=3;
               ar[2].a=2;
               ar[2].b=1;
               ar[3].a=2;
               ar[3].b=2;
               ar[4].a=2;
               ar[4].b=3;
               size=5;
               break;
        case 16:
               ar[0].a=1;
               ar[0].b=2;
               ar[1].a=2;
               ar[1].b=1;
               ar[2].a=2;
               ar[2].b=2;
               ar[3].a=2;
               ar[3].b=3;
               size=4;
               break;                
    }
}
/*void setn(int a,int b,char arr[][max2]){
    arr[a][b]='#';
}*/
void removen(int a,int b)
{
    arr[a][b]=' ';
}
void set_box()
{
    for(int i=0;i<size;i++)
    {
        setn(ar[i].a,ar[i].b,arr);
    }
}
void remove_box()
{
    for(int i=0;i<size;i++)
    {
        removen(ar[i].a,ar[i].b);
    }
}
void print(){
    clear_screen();
    printf("\t*****Block game*****\n");
    printf("         \t* * * * * * *\n");
    printf("Score : %d\t* %c %c %c %c   *\n",hello,array[0][0],array[0][1],array[0][2],array[0][3]);
    printf("         \t* %c %c %c %c   *\n",array[1][0],array[1][1],array[1][2],array[1][3]);
    printf("         \t* %c %c %c %c   *\n",array[2][0],array[2][1],array[2][2],array[2][3]);
    printf("         \t* %c %c %c %c   *\n",array[3][0],array[3][1],array[3][2],array[3][3]);
    printf("         \t* * * * * * *\n");
    for(int i=0;i<max1;i++){
        for(int j=0;j<max2;j++){
            if(((j==0 || j==max2-1) && i>5 ) || i==max1-1){
                printf("* ");
            }
            else{
                printf("%c ",arr[i][j]);
            }
        }
        printf("\n");
    }
    usleep(120000);
    hello++;
}
void left()
{
    int i=0;
    int output=1;
    while(i<size)
    {
        if(ar[i].b-1==0)
        {
            output=0;
            break;
        }
        i++;
    }
    if(output)
    {
        remove_box();
        for(int i=0;i<size;i++)
        {
            int temp=ar[i].b;
            ar[i].b=temp-1;
        }
        set_box();
    }
}
int right()
{
    int output=1;
    int i=0;
    while(i<size)
    {
        if(ar[i].b+1==max2-1)
        {
            output=0;
            break;
        }
        i++;
    }
    if(output)
    {
        remove_box();
        for(int i=0;i<size;i++)
        {
            int temp=ar[i].b;
            ar[i].b=temp+1;
        }
        set_box();
    }
}
int set_temp()
{
    int output=1;
    s=0;
    for(int i=0;i<size;i++)
    {
        for(int j=i;j<size;j++)
        {
            if(ar[i].b==ar[j].b && i!=j)
            {
                output=0;
                break;
            }
        }
        if(output==1){
            temp[s]=i;
            s++;            
        }
        else{
            output=1;
        }
    }
}
int check()
{
    int output1=1;
    for(int i=0;i<s;i++)
    {
        if(arr[ar[temp[i]].a+1][ar[temp[i]].b]=='#')
        {
            output1=0;
            break;
        }
    }
    return output1;
}
void continuous()
{
    remove_box();
    for(int i=0;i<size;i++)
    {
        int temp=ar[i].a;
        ar[i].a=temp+1;
    }
    set_box();
}
int block_len()
{
    int count=0;
    for(int i=1;i<size;i++)
    {
        if(ar[i].a>ar[i-1].a)
        {
            count++;
        }
    }
    return count;
}
void smashall_block(int n)
{
    for(int i=0;i<max_occupy;i++)
    {
        for(int j=0;j<max2-2;j++)
        {
            arr[n][j]=arr[n-1][j];
        }
        n=n-1;
    }
    max_occupy--;
}
void smash(int len)
{
    int output=1;
    int j=ar[size-1].a;
    while(len>=0){
        for(int i=1;i<max2-1;i++)
        {
            if(arr[j][i]!='#')
            {
                output=0;
                break;
            }         
        }
        if(output==1)
        {
            smashall_block(j);
            hello+=2;
            print();
        }
        output=1;
        len--;
    }
}
void setnext(int num)
{
    initalize(4,4,1);
    if(num==0)
    {
        num++;
    }
    switch(num){
        case 1:
               setn(1,1,array);
               setn(1,2,array);
               setn(1,3,array);
               setn(2,2,array);
               break;
        case 2:
               setn(1,1,array);
               setn(1,2,array);
               setn(1,3,array);
               setn(2,1,array);
               break;
        case 3:
               setn(1,1,array);
               setn(1,2,array);
               setn(2,2,array);
               setn(2,3,array);
               break;
        case 4:
               setn(1,1,array);
               setn(1,2,array);
               setn(1,3,array);
               setn(1,4,array);
               break;
        case 5:
               setn(1,1,array);
               break; 
        case 6:
               setn(1,2,array);
               setn(2,1,array);
               setn(2,2,array);
               setn(2,3,array);
               setn(3,2,array);
               break;
        case 7:
               setn(1,1,array);
               setn(2,1,array);
               setn(3,1,array);
               setn(4,1,array);
               break;
        case 8:
               setn(1,1,array);
               setn(1,2,array);
               setn(1,3,array);
               break;
        case 9:
               setn(1,1,array);
               setn(2,1,array);
               setn(2,2,array);
               break;
        case 10:
               setn(1,3,array);
               setn(2,1,array);
               setn(2,2,array);
               setn(2,3,array);
               break;
        case 11:
               setn(1,1,array);
               setn(1,2,array);
               setn(1,3,array);
               break;
        case 12:
               setn(1,1,array);
               setn(2,1,array);
               setn(2,2,array);
               setn(3,1,array);
               setn(3,2,array);
               break;                
        case 13:
               setn(1,1,array);
               setn(1,2,array);
               setn(2,1,array);
               setn(2,2,array);
               break;
        case 14:
               setn(1,1,array);
               setn(1,2,array);
               setn(2,2,array);
               break;
        case 15:
               setn(1,1,array);
               setn(1,3,array);
               setn(2,1,array);
               setn(2,2,array);
               setn(2,3,array);
               break;
        case 16:
               setn(1,2,array);
               setn(2,1,array);
               setn(2,2,array);
               setn(2,3,array);
               break;                
    }
}
int main(){
    int current_occupy;
    int so=1;
    initalize(max1,max2,0);
    generate_block(rand()%17);
    set_box();
    set_temp();
    int rand1=rand()%17;
    int len=block_len();
    setnext(rand1);
    print();
    while(1)
    {
        int ch=kbhit(100);
        if(ch)
        {
            if(ch=='a')
            {
                left();
            }
            else if(ch=='d')
            {
                right();
            }
            else if(ch=='q')
            {
                break;
            }
        }
        int chk=check();
        if(ar[size-1].a<max1-2 && chk==1){
            continuous();
        }
        else{
            for(int j=1;j<max2-1;j++)
            {
                if(arr[4][j]=='#')
                {
                    so=0;
                    break;
                }
            }
            if(so==0)
            {
                break;
            }
            current_occupy=max1-ar[0].a;
            if(current_occupy>max_occupy)
            {
                max_occupy=current_occupy;
            }
            smash(len);
            generate_block(rand1);
            set_box();
            set_temp();
            rand1=rand()%17;
            setnext(rand1);
            len=block_len();
        }
        print();
    }
    printf("Game Over\nYour score is %d\n",hello);
}