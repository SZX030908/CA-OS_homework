#include <stdio.h>

int main() {

    unsigned eax;
    unsigned ebx;
    unsigned ecx;
    unsigned edx;
    unsigned esi;
    unsigned edi;

    char c; // 要打印的字符
    int syscall = 4;
    int fd = 1; // 文件描述符，1表示标准输出
    int len = 1; // 要写入的字节数
    unsigned u_c = (unsigned)(&c);

    // __asm__ __volatile__(
    //     "movl %0, %%eax\n\t" // 将系统调用号0x04（sys_write）存储到%eax寄存器中
    //     "movl %1, %%ebx\n\t" // 将文件描述符存储到%ebx寄存器中
    //     "movl %2, %%ecx\n\t" // 将缓冲区地址存储到%ecx寄存器中
    //     "movl %3, %%edx\n\t" // 将要写入的字节数存储到%edx寄存器中
    //     "int $0x80\n\t" // 调用系统调用
    //     :
    //     : "i"(0x03), "r"(fd), "r"(u_c), "r"(len)
    //     : "%eax", "%ebx", "%ecx", "%edx"
    // );
    scanf("%c",&c);

    __asm__ __volatile__(
        "movl %0, %%eax\n\t" // 将系统调用号0x04（sys_write）存储到%eax寄存器中
        "movl %1, %%ebx\n\t" // 将文件描述符存储到%ebx寄存器中
        "movl %2, %%ecx\n\t" // 将缓冲区地址存储到%ecx寄存器中
        "movl %3, %%edx\n\t" // 将要写入的字节数存储到%edx寄存器中
        "movl %4, %%edi\n\t" // 将要写入的字节数存储到%edx寄存器中
        "movl %5, %%esi\n\t" // 将要写入的字节数存储到%edx寄存器中
        :
        : "r"(eax), "r"(ebx), "r"(ecx), "r"(edx),"r"(edi),"r"(esi)
    );

    printf("before :\n");
    printf("eax %u  ", eax);
    printf("ebx %u  ", ebx);
    printf("ecx %u  ", ecx);
    printf("edx %u  ", edx);
    printf("edi %u  ", edi);
    printf("esi %u\n", esi);

    edi = 15;
    esi = 14;

    printf("before print :\n");
    printf("eax %d  ", syscall);
    printf("ebx %d  ", fd);
    printf("ecx %u  ", u_c);
    printf("edx %d  ", len);
    printf("edi %u  ", edi);
    printf("esi %u\n", esi);
    __asm__ __volatile__(
        "movl %0, %%eax\n\t" // 将系统调用号0x04（sys_write）存储到%eax寄存器中
        "movl %1, %%ebx\n\t" // 将文件描述符存储到%ebx寄存器中
        "movl %2, %%ecx\n\t" // 将缓冲区地址存储到%ecx寄存器中
        "movl %3, %%edx\n\t" // 将要写入的字节数存储到%edx寄存器中
        "movl %4, %%edi\n\t" // 将缓冲区地址存储到%ecx寄存器中
        "movl %5, %%esi\n\t" // 将要写入的字节数存储到%edx寄存器中
        "int $0x80\n\t" // 调用系统调用

        "movl %%eax,%0\n\t" 
        "movl %%ebx,%1\n\t" 
        "movl %%ecx,%2\n\t" 
        "movl %%edx,%3\n\t" 
        "movl %%edi,%4\n\t" 
        "movl %%esi,%5\n\t"
        :
        : "r"(syscall), "r"(fd), "r"(u_c), "r"(len),"r"(edi),"r"(esi)
        : "%eax", "%ebx", "%ecx", "%edx"
    );

    printf("after print:\n");
    printf("eax %d  ", syscall);
    printf("ebx %d  ", fd);
    printf("ecx %u  ", u_c);
    printf("edx %d  ", len);
    printf("edi %u  ", edi);
    printf("esi %u\n", esi);
    printf("The input character is: %c\n", c);
    return 0;
}