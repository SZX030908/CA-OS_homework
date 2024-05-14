#include <stdio.h>
typedef struct test_struct{
    char a;
    short b;
    int c;
    float e;
    double f;
    long d;
    long double g;
}test_struct;

int main(){
    printf("struct size : %lu\n",sizeof(long));
    printf("long long size : %lu\n",sizeof(long long));
    printf("struct size : %lu\n",sizeof(test_struct));
}