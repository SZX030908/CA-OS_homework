#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <syscall.h>
#include <stdbool.h>
#include <sys/time.h>
#include "monitor.h"
#define BUFFER_NUM 64

double buffer_array[BUFFER_NUM];

void Monitor_getTask(server_result * result);
void Monitor_putResult(double res);
void Monitor_getResult(client_result * result);
// void array_print();
void Monitor_init();

void * func_thread_calc(void * arg) {
    server_result task;
    unsigned server_count = 0;//记录自己调用方法monitor方法的次数
    while (1) {
        Monitor_getTask(&task);
        if (!task.status) {
            printf("A server %u thread finished! monitor count :%u\n",*(unsigned *)arg,server_count);
            return NULL;
        }
        server_count++;
        double x = (task.a + 0.5) / (double)NSTEPS;
        double y = 4.0 / (1.0 + x * x);
        Monitor_putResult(y);
    }
    return NULL;
}

void * func_thread_reduce(void * arg) {
    client_result task;
    while (1) {
        Monitor_getResult(&task);
        if (!task.status) {
            printf("A client %u thread finished!\n",*(unsigned *)arg);
            return NULL;
        }
    }
    return NULL;
}

void Monitor_getTask(server_result * result) {
    pthread_mutex_lock(&task_monitor.server_lock);

    if (task_monitor.remind_server_task <= 0)
        result->status = false;
    else
    {
        result->status = true;

        result->a = NSTEPS - task_monitor.remind_server_task;
        task_monitor.remind_server_task--;
    }

    pthread_mutex_unlock(&task_monitor.server_lock);
    return ;
}

void Monitor_putResult(double res) {
    pthread_mutex_lock(&task_monitor.client_lock);

    while ((task_monitor.current_num >= 64)) {
        pthread_cond_wait(&task_monitor.can_reduce, &task_monitor.client_lock);
    }//如果当前数组中的元素个数大于64个，则等待

    buffer_array[task_monitor.array_point_last] = res;
    task_monitor.array_point_last = (task_monitor.array_point_last+1) % BUFFER_NUM;
    task_monitor.current_num++;

    pthread_cond_broadcast(&task_monitor.can_get);//tell other threads

    pthread_mutex_unlock(&task_monitor.client_lock);
}

void Monitor_getResult(client_result * result) {
    pthread_mutex_lock(&task_monitor.client_lock);

    while ((task_monitor.current_num <= 0)) {
        pthread_cond_wait(&task_monitor.can_get, &task_monitor.client_lock);
    }//如果当前数组中的元素个数没有了，则等待

    if (task_monitor.remind_client_task <= 0)
        result->status = false;
    else
    {
        result->status = true;

        task_monitor.pi += buffer_array[task_monitor.array_point_front];
        task_monitor.array_point_front = (task_monitor.array_point_front+1) % BUFFER_NUM;
        task_monitor.remind_client_task--;
        task_monitor.current_num--;
    }

    pthread_cond_broadcast(&task_monitor.can_reduce);//tell other threads

    pthread_mutex_unlock(&task_monitor.client_lock);

    return;
}

void Monitor_init() {
    unsigned i = 0;
    while(i < BUFFER_NUM)
        buffer_array[i++] = 0;

    task_monitor.remind_server_task = NSTEPS;
    task_monitor.remind_client_task = NSTEPS - 1;
    task_monitor.array_point_front = 0;
    task_monitor.array_point_last = 0;
    task_monitor.current_num = 0;

    // task_monitor.getTask = Monitor_getTask;
    // task_monitor.putResult = Monitor_putResult;
    // task_monitor.getResult = Monitor_getResult;

    task_monitor.monitor_calc = func_thread_calc;
    task_monitor.monitor_reduce = func_thread_reduce;

    task_monitor.pi = 0.0;
    //task_monitor.array_print = array_print;
    pthread_mutex_init(&task_monitor.server_lock, NULL);
    pthread_mutex_init(&task_monitor.client_lock, NULL);
}