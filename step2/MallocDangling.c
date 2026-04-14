#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(){
    while(1){
        void *p = malloc(1024 * 1024);
        if(p==NULL) break;
        memset(p,0,1024*1024);
        sleep(1);
    }
    return 0;
}
