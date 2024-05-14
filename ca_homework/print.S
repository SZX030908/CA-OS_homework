.section .data  
    output: .byte 0
.section .text
.globl _start
_start:
    movl $3, %eax
    movl $2, %ebx
    movl $output, %ecx
    movl $1, %edx
    int $0x80
    movl $4, %eax
    movl $1, %ebx
    movl $output, %ecx
    movl $1, %edx
    int $0x80
    movl $1, %eax
    movl $0, %ebx
    int $0x80