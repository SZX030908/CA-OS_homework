#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <syscall.h>
#include <stdbool.h>
#include <sys/time.h>
#define NSTEPS 100000000


typedef struct {
    int a;
    bool status;
} server_result;

typedef struct {
    bool status;
} client_result;

typedef struct {
    pthread_mutex_t server_lock;

    pthread_mutex_t client_lock;
    pthread_cond_t can_reduce;
    pthread_cond_t can_get;

    int remind_server_task;//记录生产者还有多少个任务
    int remind_client_task;//记录消费者还有多少个任务

    int array_point_front;
    int array_point_last;
    int current_num;//记录当前队列中还有多少个数，是否够相加

    void * (*monitor_calc)(void * arg);
    void * (*monitor_reduce)(void * arg);
    double pi;
} Monitor;

Monitor task_monitor;
void Monitor_init();