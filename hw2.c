#include <stdio.h>
#include <stdlib.h>
#define Bound(x,y) (x>=0 && x<=7 && y>=0 && y<=7)


int find(int colorFind , int i, int j, int dx, int dy, int chess[8][8], int test){
    

    while(Bound(i,j)){                          //i:控制y軸(直向)   j:控制x軸(橫向)
        switch(colorFind){

            case 1:                             //判斷能不能下黑棋
                i += dy;
                j += dx;

                if(chess[i][j] != 2){
                    return 0;
                }
                else {
                    while(Bound(i,j)){
                        if(chess[i][j]==2){
                            i += dy;
                            j += dx;
                            continue;
                        }
                        else{                   //找到空白處(可以下的地方)
                            test = 1;
                            return test;
                        }
                    }
                }
                break;

            case 2:                                     //判斷能不能下白棋
                i += dy;
                j += dx;

                if(chess[i][j] != 1){
                    return 0;
                }
                else {                                  //下一步是黑棋
                    while(Bound(i,j)){                  
                        if(chess[i][j]==1){             //測下下一步是不是黑棋
                            i += dy;                    //(如果是再往下找有沒有白棋，找不到最後會跳出while迴圈，then break)
                            j += dx;
                            continue;
                        }
                        else{                           //下下一步是白棋，可以放
                            test = 1;
                            return test;
                        }
                    }
                }
                break;
        }
    }
}


int main(){
    int chess[8][8],color,colorFind,i,j,dx,dy,test=0;
    char other;

    for(int a=0; a<8; a++){                     //輸入棋盤
        for(int b=0; b<8; b++){
            scanf("%d",&chess[a][b]);
        } 
    }

    scanf("%d %d %c %d",&colorFind,&i,&other,&j);  //colorFind : 是否可以下這個顏色的棋子
    color = chess[i][j];                          //color : 輸入的座標上棋子的顏色

    switch (color){
        case 1: 
            printf("black,no");
            break;
        
        case 2:
            printf("white,no");
            break;

        case 0:
            test = find(colorFind,i,j,dx=1,dy=0,chess,test);   //右  ok
            test = find(colorFind,i,j,dx=-1,dy=0,chess,test);   //左 ok
            test = find(colorFind,i,j,dx=0,dy=-1,chess,test);   //上  ok
            test = find(colorFind,i,j,dx=0,dy=1,chess,test);   //下 ok
            test = find(colorFind,i,j,dx=1,dy=1,chess,test);   //右下 ok
            test = find(colorFind,i,j,dx=-1,dy=1,chess,test);   //左下  ok
            test = find(colorFind,i,j,dx=1,dy=-1,chess,test);   //右上 ok
            test = find(colorFind,i,j,dx=-1,dy=-1,chess,test);   //左上 ok

            if(test > 0)
                printf("Yes");
            
            else if(test == 0)
                printf("No");
    }
   return 0;
}
    
    
    