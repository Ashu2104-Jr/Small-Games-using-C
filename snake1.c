#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef struct{
    int pos;
    int p;
    int next;
}print;
print arr1[max];
void move(int i,int arr[],int p[],int pno)
{
    int val=p[pno]+i;
    if(val<=99)
    {
        if(arr[val]!=0)
        {
            p[pno]=arr[val];
        }
        else
        {
            p[pno]=val;
        }
    }
}
void setvalues(int arr[]) {
    int a[20], b[20];
    
    for(int i = 0; i < 20; i++) {
        a[i] = rand() % max;
        b[i] = rand() % max;
    }
    
    for(int j = 0; j < 20; j++) {
        arr[a[j]] = b[j];
    }
}
int roll()
{
      return rand()%6;
}
void printn(int arr[], int p[], int pno, int get) {
    printf("\e[1;1H\e[2J"); // clear screen
    printf("Chance of Player %d\n", pno + 1);
    printf("Rolled value: %d\n\n", get);

    for (int i = 0; i < max; i++) {
        arr1[i].pos = i;
        arr1[i].next = arr[i];
	arr1[i].p=0;
    }

    // Mark player positions
    for (int i = 0; i < 4; i++) {
        if (p[i] >= 0 && p[i] < max) {
            arr1[p[i]].p= i + 1;
        }
    }

    int n = max;
    int f = max-10;

    while (f >=0) {
        for (int i = n; i > f; i--) {
            printf("\t[%02d]", i);
        }
        printf("\n");

        // Print snakes or ladders
        for (int i = n; i > f; i--) {
            if (arr1[i].next < i && arr1[i].next != 0) {
                printf("\t S%02d", arr1[i].next);  // Snake
            } else if (arr1[i].next > i && arr1[i].next != 0) {
                printf("\t L%02d", arr1[i].next);  // Ladder
            } else {
                printf("\t     ");
            }
        }
        printf("\n");

        // Print players
        for (int i = n; i > f; i--) {
            if (arr1[i].p != 0) {
                printf("\t P%d ", arr1[i].p);
            } else {
                printf("\t     ");
            }
        }
        printf("\n\n");

        n = f;
        f -= 10;
    }
}

int main() {
    int arr[max];
    int p[4];
    int pno=0;
    int rolly=1;
    for(int i=0;i<4;i++)
    {
        p[i]=-1;
    }
    for(int i=0;i<=max;i++)
    {
        arr[i]=0;
    }
    setvalues(arr);
    int ob=1;
    while(ob)
    {
        printf("roll : ");
        scanf("%d",&rolly);
        if(p[pno]==99)
        {
            break;
        }
        if(rolly==1)
        {
            int dice=roll();
            move(dice,arr,p,pno);
            printn(arr,p,pno,dice);
            if(pno==3)
            {
                pno=0;
            }
            else
            {
                pno++;
            }
        }
        else
        {
            if(pno==3)
            {
                pno=0;
            }
            else
            {
                pno++;
            }
        }
    }
    
    printf("no %d is winner",pno+1);
    return 0;
}

