#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10
#define Bound(x,y) (x>=0 && x<=9 && y>=0 && y<=9)

typedef struct Position{
    int i;   //(i,j)  i:控制y軸(直向)   j:控制x軸(橫向)
    int j;
}position;

position stack[MAX_N*MAX_N];         //宣告stack
int top = 0;                         //stack初始位置
position end = {6,9};
int maze[MAX_N][MAX_N] ={               //1:牆壁 0:可走的路 2:走過的路
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
    { 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
    { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
    { 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
    { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


void push(position i_j){
    if(top >= MAX_N*MAX_N)
        return;

    stack[top] = i_j;
    top++;
}

position pop(){
    position fail = {-1,-1};
    if(top == 0)
        return fail;

    top--;
    position result = stack[top];
    return result;
}

void print_maze(){
    for(int i=0; i<=9; i++){
        for(int j=0; j<=9; j++){
            int judge = 0;
            for(int m=0; m<top; m++){
                if(i==stack[m].i && j==stack[m].j){
                    printf("@ ");
                    judge = 1;
                    break;
                }
            }
            if(judge == 0)
                printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
}




int main(){
    position start = {1,0};
    position now = {start.i, start.j};
    int success = 0;

    while(Bound(now.i,now.j)){
        if(now.i == end.i && now.j == end.j)  //成功break
        {
            success = 1;
            break;
        }

        else if(success != 1 && maze[now.i][now.j-1] == 0)   //往左
        {
            maze[now.i][now.j] = 2;
            push(now);
            now.j--;
        }
        else if(success != 1 && maze[now.i][now.j+1] == 0)   //往右
        {
            maze[now.i][now.j] = 2;
            push(now);
            now.j++;
        }
        else if(success != 1 && maze[now.i-1][now.j] == 0)   //往上
        {
            maze[now.i][now.j] = 2;
            push(now);
            now.i--;
        }
        else if(success != 1 && maze[now.i+1][now.j] == 0)   //往下
        {
            maze[now.i][now.j] = 2;
            push(now);
            now.i++;
        }

        else            //退 回 去
        {
            maze[now.i][now.j] = 2;
            now = pop();
        }
        // print_maze();
        // printf("\n--------------------\n");


    }

    if(now.i == -1 && now.j == -1){
        printf("fail\n");
        printf("----------------------\n");
        print_maze();
    }
    else{
        printf("success\n");
        printf("----------------------\n");
        push(end); 
        print_maze();
    }

    return 0;
}

