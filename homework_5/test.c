#define _GNU_SOURCE
#define __USE_GNU 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

/*#define SIZE 1000000
#define NUM 10
typedef struct test_struct{
    int* test_array;
    int num;
}test_struct;

long result = 0;
pthread_mutex_t mutex;*/

// 回调函数
int main()
{
    int pid;
    /*int i;
    int count = SIZE/NUM;
    long temp_result = 0;

    struct test_struct* temp = (test_struct*)arg;
    int temp_num = temp->num;
    int start = count * temp_num;
    int* p_array = temp->test_array;*/

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(1,&cpuset);
    sched_setaffinity(0, sizeof(cpuset), &cpuset);
    //sleep(1);

    pid = getpid();
    printf("%d\n",pid);

    while(1)
        ;

    /*for(i = 0;i < count ;i++)
        temp_result += *(p_array + start + i);

    pthread_mutex_lock(&mutex);

    result += temp_result;
    //printf("current result = %ld\n", result);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
    return NULL;*/
}