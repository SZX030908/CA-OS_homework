#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define LEN 5
#define OPTIMES 5
int array[5];
int flag = 0;
pthread_mutex_t mutex;
//thread1 

void* thread_fun_1(){
    int i;
    int write_num = 0;
    int count = 0;
    while(count < OPTIMES) {
        if(!flag){
             pthread_mutex_lock(&mutex);
        
            //critical section
            for(i=0;i<LEN;i++){
                write_num = rand()%20 + 1;
                array[i] = write_num; 
            }
            count++;
            flag = 1;
            //critical section

            pthread_mutex_unlock(&mutex);
        }
    }
}
//thread2 
void* thread_fun_2(){
    int i;
    int sum = 0;
    int count = 0;
    while(count < OPTIMES) {
        if(flag){
             pthread_mutex_lock(&mutex);
        
            //critical section
            printf("[");
            for(i=0;i<LEN;i++){
                sum += array[i];
                if(i == 0)
                    printf("%d",array[i]);
                else 
                    printf(",%d",array[i]);
            }
            printf("]\n");
            printf("sum[%d]:%d\n",count,sum);
            count++;
            sum = 0;
            flag = 0;
            //critical section

            pthread_mutex_unlock(&mutex);
        }
    }
}
int main()
{
    int result;
    int max = 0;
    int i;
    pthread_t pthread_1;
    pthread_t pthread_2;
    struct timespec time1;
    struct timespec time2;

    clock_gettime(CLOCK_REALTIME, &time1);
    pthread_create(&pthread_1,NULL,thread_fun_1,NULL);
    pthread_create(&pthread_2,NULL,thread_fun_2,NULL);

    pthread_join(pthread_1,NULL);
    pthread_join(pthread_2,NULL);
    clock_gettime(CLOCK_REALTIME, &time2);

    printf("time = %ld ns\n", time2.tv_nsec - time1.tv_nsec);
}
