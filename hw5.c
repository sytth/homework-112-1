#include <stdio.h>
#include <stdlib.h>
#define Bound(x,y) (x>=0 && x<=7 && y>=0 && y<=7)

//找出可下的位置(以白棋為例)
int find(int i, int j, int dx, int dy, int chess[8][8], int color, int judge,int next[8][8]){ 
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

//輸出目前棋盤
int NowChess(int chess[8][8]){
    for(int a=0; a<8; a++){                   
        for(int b=0; b<8; b++){
            printf("%d ",chess[a][b]);
        }
        printf("\n");
    }
    return 0;
}

//輸出可放的位置
int You_can_set(int color, int next[8][8]){
    int count = 0;                  //控制逗號個數
    for(int a=0; a<8; a++){                     
        for(int b=0; b<8; b++){
            if(next[a][b] == color){
                if(count>0)
                    printf(",");
                    
                printf("(%d, %d)",a,b);
                count++;
            }
        }
    }
    return 0;
}


//翻轉成正確棋盤(以白棋為例)
int turn(int m, int n, int dx, int dy, int chess[8][8], int judge,int count){     //judge：白要翻成黑
    for(int a =1; a<=count; a++){
        m += dy;
        n += dx;
        chess[m][n] = judge;
    }
}


//計算可翻多少棋子(以白棋為例)
int sum(int i, int j, int dx, int dy, int chess[8][8],int color, int judge){     //color：要下哪個顏色的棋子 judge：判斷的棋子顏色
    int count = 0;                          //這個方向可以翻的棋子數量

    while(Bound(i,j)){               
        int m = i,n = j;                    //原始(i,j)座標  
        i += dy;                            //i:控制y軸(直向)   j:控制x軸(橫向)
        j += dx;                            //先走出一步

        if(chess[i][j] != judge){           //下一步是白棋or空白，這個方向直接跳過
            return 0;
        }
        else {                              //下一步是黑棋
            while(Bound(i,j)){                  
                if(chess[i][j] == judge){       //測下下一步是不是黑棋
                    count++;                    //(如果是黑棋再往下找有沒有白棋，找不到最後會跳出while迴圈，then break)
                    i += dy;                    
                    j += dx;                
                    continue;
                }
                else if(chess[i][j] == color){      //下下一步是白棋，可以翻
                    turn(m,n,dx,dy,chess,judge,count);      //呼叫翻棋子函式
                    return count;
                }
            }
        }
    }
}



int main(){
    int i,j,dx,dy,color,judge;
    int next[8][8] = {};
    int chess[8][8]={{0,0,0,0,0,0,0,0},         //初始棋盤
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

    int turn_sum = 0;
    color = 1;
    judge = 2;
    printf("1 黑棋你下\n");
    NowChess(chess);                            //輸出棋盤
    You_can_set(color = 1,next);                //輸出可放的位置
    printf("\n請下合法的位子 x y\n");
    scanf("%d%d",&i,&j);                        //輸入黑棋要下的位置

    turn_sum += sum(i,j,dx=1,dy=0,chess,color,judge);   //右 
    turn_sum += sum(i,j,dx=-1,dy=0,chess,color,judge);   //左
    turn_sum += sum(i,j,dx=0,dy=-1,chess,color,judge);   //上
    turn_sum += sum(i,j,dx=0,dy=1,chess,color,judge);   //下
    turn_sum += sum(i,j,dx=1,dy=1,chess,color,judge);   //右下
    turn_sum += sum(i,j,dx=-1,dy=1,chess,color,judge);   //左下
    turn_sum += sum(i,j,dx=1,dy=-1,chess,color,judge);   //右上
    turn_sum += sum(i,j,dx=-1,dy=-1,chess,color,judge);   //左上

    printf("可翻轉 %d 子\n",turn_sum);



   return 0;
}
