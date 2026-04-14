#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    while(1){
        void *p = malloc(1024*1024);
        if (p==NULL) break;
        sleep(1);
        memset(p,0,1024*1024);
        free(p);    
    }
    return 0;
}
