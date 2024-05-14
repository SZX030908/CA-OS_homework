#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>
// #include <uintstd.h>
#define A_line 1000
#define A_B_connect 1000
#define B_comm 1000
int main(int argc, char **argv)
{
    double *A,*B,*C;
    int i,j,k;
    int ID,num_procs,line;
    MPI_Status status;
    struct timeval time_1;
    struct timeval time_2;

    gettimeofday(&time_1,NULL);
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&ID);
    MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
    A = (double *)malloc(sizeof(double)*A_line*A_B_connect);
    B = (double *)malloc(sizeof(double)*A_B_connect*B_comm);
    C = (double *)malloc(sizeof(double)*A_line*B_comm);
    line = A_line/num_procs;
    if(ID==0){
        for( i=0;i<A_line;i++)
            for( j=0;j<A_B_connect;j++)
                A[i*A_B_connect+j] = 1.0;
        for( i=0;i<A_B_connect;i++)
            for( j=0;j<B_comm;j++)
                B[i*B_comm+j] = 1.0;   
        for(i=1;i<num_procs;i++){
            MPI_Send(B,B_comm*A_B_connect,MPI_DOUBLE,i,0,MPI_COMM_WORLD);
            MPI_Send(A+(i-1)*line*A_B_connect,line*A_B_connect,MPI_DOUBLE,i,1,MPI_COMM_WORLD);
        }
        for(i=1;i<num_procs;i++)
            MPI_Recv(C+(i-1)*line*B_comm,line*B_comm,MPI_DOUBLE,i,2,MPI_COMM_WORLD,&status);
        for(i=(num_procs-1)*line;i<A_line;i++)
            for(j=0;j<B_comm;j++){
                C[i*B_comm+j] = 0;
                for(k=0;k<A_B_connect;k++)
                   C[i*B_comm+j]+=A[i*A_B_connect+k]*B[k*B_comm+j];
            }
    }
    else{
        MPI_Recv(B,B_comm*A_B_connect,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);
        MPI_Recv(A+(ID-1)*line*A_B_connect,line*A_B_connect,MPI_DOUBLE,0,1,MPI_COMM_WORLD,&status);
        for(i=(ID-1)*line;i<ID*line;i++)
            for(j=0;j<B_comm;j++){
                C[i*B_comm+j] = 0;
                for(k=0;k<A_B_connect;k++)
                    C[i*B_comm+j] += A[i*A_B_connect+k]*B[k*B_comm+j];
            }
        MPI_Send(C+(ID-1)*line*B_comm,line*B_comm,MPI_DOUBLE,0,2,MPI_COMM_WORLD);
    }
    MPI_Finalize();

    gettimeofday(&time_2,NULL);
    printf("Seconds = %lu \t Uanoseconds = %lu\n", time_2.tv_sec-time_1.tv_sec, time_2.tv_usec-time_1.tv_usec);

    return 0;
}