#include <stdio.h>
#include <stdlib.h>
#define Bound(x,y) (x>=0 && x<=7 && y>=0 && y<=7)

//找出可下的位置
int find(int i, int j, int dx, int dy, int chess[8][8], int color, int judge,int next[8][8]){ 
    //以白棋為例
    while(Bound(i,j)){                      
        i += dy;                            //i:控制y軸(直向)   j:控制x軸(橫向)
        j += dx;                            //先走出一步

        if(chess[i][j] != judge){           //下一步是白棋or空白，這個方向直接跳過
            return 0;
        }
        else {                              //下一步是黑棋
            while(Bound(i,j)){                  
                if(chess[i][j] == judge){       //測下下一步是不是黑棋
                    i += dy;                    //(如果是黑棋再往下找有沒有空白處，找不到最後會跳出while迴圈，then break)
                    j += dx;                
                    continue;
                }
                else{                           //下下一步是空白，可以放(不可能跳一格還會是白棋，這樣上一局就應該翻棋子了，so可以只寫else)
                    next[i][j] = color;         //紀錄這個位置可以放白棋
                    return 0;
                }
            }
        }
    }
}



int main(){
    int i,j,dx,dy,color,judge;
    int next[8][8] = {};
    int chess[8][8]={{0,0,0,0,0,0,0,0},         //棋盤
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,1,2,0,0,0},
                     {0,0,0,2,1,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0}
                    };

    for( i=0; i<8; i++){                //一個一個檢查白子、黑子  a:y軸 b:x軸
        for(j=0; j<8; j++){
            switch(chess[i][j]){
                //空白
                case 0:
                    break;

                //如果是黑子
                case 1:                     
                    color = 1;
                    judge = 2;
                    
                    find(i,j,dx=1,dy=0,chess,color,judge,next);   //右 
                    find(i,j,dx=-1,dy=0,chess,color,judge,next);   //左
                    find(i,j,dx=0,dy=-1,chess,color,judge,next);   //上
                    find(i,j,dx=0,dy=1,chess,color,judge,next);   //下
                    find(i,j,dx=1,dy=1,chess,color,judge,next);   //右下
                    find(i,j,dx=-1,dy=1,chess,color,judge,next);   //左下
                    find(i,j,dx=1,dy=-1,chess,color,judge,next);   //右上
                    find(i,j,dx=-1,dy=-1,chess,color,judge,next);   //左上

                    break;
                
                //如果是白子
                case 2:
                    color = 2;                
                    judge = 1;
                    
                    find(i,j,dx=1,dy=0,chess,color,judge,next);   //右 
                    find(i,j,dx=-1,dy=0,chess,color,judge,next);   //左 
                    find(i,j,dx=0,dy=-1,chess,color,judge,next);   //上 
                    find(i,j,dx=0,dy=1,chess,color,judge,next);   //下
                    find(i,j,dx=1,dy=1,chess,color,judge,next);   //右下
                    find(i,j,dx=-1,dy=1,chess,color,judge,next);   //左下
                    find(i,j,dx=1,dy=-1,chess,color,judge,next);   //右上
                    find(i,j,dx=-1,dy=-1,chess,color,judge,next);   //左上

                    break;
            }
        } 
    }
    
    int black=0, white=0;                       //控制逗號個數
    
    printf("白子可下位置:\n");
    for(int a=0; a<8; a++){                     //輸出白子可放的位置
        for(int b=0; b<8; b++){
            if(next[a][b] == 2){
                if(white>0)
                    printf(",");
                    
                printf("(%d, %d)",a,b);
                white++;
            }
        }
    }
    
    printf("\n");
    printf("黑子可下位置:\n");
    for(int a=0; a<8; a++){                     //輸出黑子可放的位置
        for(int b=0; b<8; b++){
            if(next[a][b] == 1){
                if(black>0)
                    printf(",");
                    
                printf("(%d, %d)",a,b);
                black++;
            }
        }
    }
    printf("\n");
    return 0;
}
    
    
    