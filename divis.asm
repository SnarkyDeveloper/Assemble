; Checks if var is divisible by x in loop of 20

section .data
    msg db "Not divisible by 3", 10
    msg.len equ $ - msg
section .text
    global _start

_start:
    mov ecx, 20
    loop_start:
        pusha
        mov eax, ecx
        mov edx, 0
        mov ebx, 3
        mov eax, ecx
        mov edx, 0
        mov ebx, 3
        div ebx                ; eax = ecx / 3, edx = ecx % 3
        cmp edx, 0
        je skip_print
        mov eax, 4
        mov ebx, 1
        mov ecx, msg
        mov edx, msg.len
        int 80h
    skip_print:
        popa
        dec ecx
        jnz loop_start

    mov eax, 1          ; sys_exit system call number
    xor ebx, ebx        ; exit code 0
    int 0x80