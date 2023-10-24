#include <stdio.h>
#include <stdlib.h>

int main(){
    for(int i=1; i<4; i++){
        for(int j=1; j<10; j++){
            for(int k=i*3-2; k<=i*3; k++){
                printf("%d x %d = %2d\t",k,j,k*j);
            }
            printf("\n");
        }
        printf("\n\n");
    }

   return 0;
}
