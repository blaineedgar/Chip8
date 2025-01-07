#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char ** argv){
    struct timespec begin, end;
    double deltaTime;
    long int x=1;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);

    //beginTime=begin.tv_sec + begin.tv_nsec/1000000000;

    //printf("Counting to 1000...");

    for(long long int i=0;i<20000000000;i++){
        x*=2;
        //printf("\nTakes %ld\n",clock());
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);

    deltaTime= end.tv_sec-begin.tv_sec + (end.tv_nsec-begin.tv_nsec)/1000000000.0;


    printf("\nTakes (CPUTIME) %fs\n",deltaTime);
}