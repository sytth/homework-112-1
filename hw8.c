#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10
#define Bound(x,y) (x>=0 && x<=9 && y>=0 && y<=9)

typedef struct Position{
    int i;   //(i,j)  i:控制y軸(直向)   j:控制x軸(橫向)
    int j;
}position;

position stack[MAX_N*MAX_N];         //宣告stack
int top = -1;                   //stack初始位置在-1

int walk_the_maze(int maze[MAX_N][MAX_N],position start, position end){


}






int main(){
    int maze[MAX_N][MAX_N] ={               //1:牆壁 0:可走的路
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1 },
        { 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
        { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    position start,end;
    start.i = 1;
    start.j = 0;
    end.i = 6;
    end.j = 9;
    walk_the_maze(maze,start,end);
    

    return 0;
}

