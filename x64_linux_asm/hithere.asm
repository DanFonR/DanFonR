section .data ; variables with assigned values (int eg = 1), .bss for unassigned
hello: db "Hello", 10 ; 10/0xa is newline (\n)
hellolen: equ $ - hello ; $ is current address, equivalent to (hellolen has value of curr address minus address from hello)

global _start ; exposes the _start label to the linker

section .text ; code is here
_start:
    mov rax, 1 ; sys_write
    mov rdi, 1 ; to stdout
    mov rsi, hello ; the message
    mov rdx, hellolen ; of length
    syscall ; command ends here

    mov rax, 60 ; sys_exit
    mov rdi, 0 ; with status code 0
    syscall
