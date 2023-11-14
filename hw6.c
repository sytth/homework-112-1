#include <stdio.h>
#include <stdlib.h>
#define Bound(x,y) (x>=0 && x<=7 && y>=0 && y<=7)

int find(int i, int j, int dx, int dy, int chess[8][8], int color, int judge,int next[8][8]);
int NowChess(int chess[8][8]);
int You_can_set(int color, int next[8][8]);
int turn(int m, int n, int dx, int dy, int chess[8][8], int judge,int count);
int sum(int i, int j, int dx, int dy, int chess[8][8],int color, int judge,int can_turn);
int turn_count(int i,int j,int chess[8][8],int color,int judge,int can_turn);

//一個一個檢查棋盤上的白子or黑子  i:y軸 j:x軸
int check(int chess[8][8],int next[8][8],int color,int judge){
    int dx,dy,can_set=0;
    for(int i=0; i<8; i++){                
        for(int j=0; j<8; j++){
            if(chess[i][j] == color){               //現在輪到白棋下，判斷白棋的位置就好
                can_set += find(i,j,dx=1,dy=0,chess,color,judge,next);   //右 
                can_set += find(i,j,dx=-1,dy=0,chess,color,judge,next);   //左
                can_set += find(i,j,dx=0,dy=-1,chess,color,judge,next);   //上
                can_set += find(i,j,dx=0,dy=1,chess,color,judge,next);   //下
                can_set += find(i,j,dx=1,dy=1,chess,color,judge,next);   //右下
                can_set += find(i,j,dx=-1,dy=1,chess,color,judge,next);   //左下
                can_set += find(i,j,dx=1,dy=-1,chess,color,judge,next);   //右上
                can_set += find(i,j,dx=-1,dy=-1,chess,color,judge,next);   //左上
            }
        } 
    }
    return can_set;
}

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
                    return 1;
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

//翻轉成正確棋盤(以白棋為例，)
int turn(int m, int n, int dx, int dy, int chess[8][8], int color,int count){     //judge：白要翻成黑
    for(int a =1; a<=count+1; a++){
        chess[m][n] = color;
        m += dy;
        n += dx;
    }
}

//計算這步可翻多少棋子  2.翻轉棋子
int turn_count(int i,int j,int chess[8][8],int color,int judge,int can_turn){
    int turn_sum = 0,dx,dy;
    turn_sum += sum(i,j,dx=1,dy=0,chess,color,judge,can_turn);   //右 
    turn_sum += sum(i,j,dx=-1,dy=0,chess,color,judge,can_turn);   //左
    turn_sum += sum(i,j,dx=0,dy=-1,chess,color,judge,can_turn);   //上
    turn_sum += sum(i,j,dx=0,dy=1,chess,color,judge,can_turn);   //下
    turn_sum += sum(i,j,dx=1,dy=1,chess,color,judge,can_turn);   //右下
    turn_sum += sum(i,j,dx=-1,dy=1,chess,color,judge,can_turn);   //左下
    turn_sum += sum(i,j,dx=1,dy=-1,chess,color,judge,can_turn);   //右上
    turn_sum += sum(i,j,dx=-1,dy=-1,chess,color,judge,can_turn);   //左上

    return turn_sum;
}



//計算可翻多少棋子-各方向計算(以白棋為例)
int sum(int i, int j, int dx, int dy, int chess[8][8],int color, int judge,int can_turn){     //color：要下哪個顏色的棋子 judge：判斷的棋子顏色
    int count = 0;                          //這個方向可以翻的棋子數量

    while(Bound(i,j)){               
        int m = i,n = j;                    //(m,n) = 原始(i,j)座標  
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
                    if(color == 2 && can_turn == 0){                             //統計白棋放各位置可翻的數量(先不翻)
                        return count;
                    }
                    
                    else{
                        turn(m,n,dx,dy,chess,color,count);      //呼叫翻棋子函式(只有黑棋可以同時翻)
                        return count;
                    }
                }
                else if(chess[i][j] == 0)
                    return 0;
            }
        }
    }
}


int main(){
    int i,j,dx,dy,color,judge,control=0;
    int chess[8][8]={{0,0,0,0,0,0,0,0},         //初始棋盤
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,1,2,0,0,0},
                     {0,0,0,2,1,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0}
                    };
    while (control == 0){
        //******下黑棋******
        int turn_sum = 0,black=0,next[8][8] = {},can_turn=1;   //清空可下的位置棋盤陣列next
        color = 1;
        judge = 2;
        printf("1 黑棋你下\n");
        NowChess(chess);                            //輸出目前棋盤
        black = check(chess,next,color,judge);      //尋找能放的位置
        if(black == 0){                             //***沒有可放的位置，結束遊戲
            break;
        }        
        You_can_set(color = 1,next);                //輸出可放的位置
        printf("\n請下合法的位子 x y\n");
        scanf("%d%d",&i,&j);                        //輸入黑棋要下的位置
        turn_sum = turn_count(i,j,chess,color,judge,can_turn);         //1.計算這步可翻多少棋子  2.翻轉棋子
        printf("可翻轉 %d 子\n",turn_sum);

        for(int a=0; a<=7; a++){                        //清空可下的位置棋盤陣列next
            for(int b=0; b<=7; b++){
               next[a][b] = 0;
            }
        }

    
        //******下白棋******
        int white=0,compare[8][8]={};       
        turn_sum = 0,can_turn=0;
        color = 2;
        judge = 1;
        printf("2 白棋電腦下\n");
        white = check(chess,next,color,judge);      //尋找能放的位置
        if(white == 0){                             //***沒有可放的位置，結束遊戲
            break;
        }
        for(int i=0; i<=7; i++){                //判斷白棋下的最佳位置 1.計算每個位置可翻的棋子個數 2.比較
            for(int j=0; j<=7; j++){
                if(next[i][j] == 2){
                    compare[i][j] += sum(i,j,dx=1,dy=0,chess,color,judge,can_turn);   //右 
                    compare[i][j] += sum(i,j,dx=-1,dy=0,chess,color,judge,can_turn);   //左
                    compare[i][j] += sum(i,j,dx=0,dy=-1,chess,color,judge,can_turn);   //上
                    compare[i][j] += sum(i,j,dx=0,dy=1,chess,color,judge,can_turn);   //下
                    compare[i][j] += sum(i,j,dx=1,dy=1,chess,color,judge,can_turn);   //右下
                    compare[i][j] += sum(i,j,dx=-1,dy=1,chess,color,judge,can_turn);   //左下
                    compare[i][j] += sum(i,j,dx=1,dy=-1,chess,color,judge,can_turn);   //右上
                    compare[i][j] += sum(i,j,dx=-1,dy=-1,chess,color,judge,can_turn);   //左上
                }
            }
        }
        int max=0,i=0,j=0;              //(m,n)紀錄最大值的座標
        for(int a=0; a<=7; a++){
            for(int b=0; b<=7; b++){
                if(compare[a][b] != 0){
                    if(compare[a][b] > max){
                        max = compare[a][b];
                        i = a;
                        j = b;
                    }

                }
            }
        }
        can_turn=1;
        turn_sum = turn_count(i,j,chess,color,judge,can_turn);         //1.計算這步可翻多少棋子  2.翻轉棋子
        printf("電腦下 %d,%d ,可翻轉 %d 子\n",i,j,turn_sum);
    }

    //結束遊戲，判斷輸贏
    int black=0, white=0;
    for(int i=0; i<=7; i++){
        for(int j=0; j<=7; j++){
            if(chess[i][j] == 1)
                black++;
            
            else if(chess[i][j] == 2)
                white++;
        }
    }
    printf("棋局結束");
    if(black > white)
        printf("黑方勝 %d:%d",black,white);
    
    else if(black < white)
        printf("白方勝 %d:%d",black,white);

    else if(black == white)
        printf("平手 %d:%d",black,white);

   return 0;
}
