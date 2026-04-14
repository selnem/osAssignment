#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    while(1){
        void *p = malloc(1024 * 1024);
        if(p==NULL) break;
        sleep(1);
    }
    return 0;
}