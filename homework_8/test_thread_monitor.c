#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <syscall.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include "monitor.h"

#define SERVER_NUM 4
#define CLIENT_NUM 1

int main() {
    Monitor_init();
    printf("Processing...\n");

    struct timespec time_1;
    struct timespec time_2;

    pthread_t server_thread[SERVER_NUM];
    unsigned server_id[SERVER_NUM];
    pthread_t client_thread[CLIENT_NUM];
    unsigned client_id[CLIENT_NUM];

    clock_gettime(CLOCK_REALTIME, &time_1);
    for (unsigned i = 0; i < SERVER_NUM; i++) {
        server_id[i] = i;
        pthread_create(server_thread + i, NULL, task_monitor.monitor_calc, server_id + i);
    }
    for(unsigned j = 0; j < CLIENT_NUM; j++) {
        client_id[j] = j;
        pthread_create(client_thread + j, NULL, task_monitor.monitor_reduce, client_id + j);
    }

    for (unsigned i = 0; i < SERVER_NUM; i++) {
        pthread_join(server_thread[i], NULL);
    }
    for(unsigned j = 0; j < CLIENT_NUM; j++) {
        pthread_join(client_thread[j], NULL);
    }
    clock_gettime(CLOCK_REALTIME, &time_2);

    printf("Seconds: %ld\n", time_2.tv_sec-time_1.tv_sec);

    double result_pi = task_monitor.pi/NSTEPS;
    printf("\nPass\nThe final pi result is: %.25f\n",result_pi);

    return 0;
}