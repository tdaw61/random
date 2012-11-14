.globl Main
Main:
pushl %ebp
movl %esp, %ebp
subl $0, %esp
pushl $5
popl %eax
neg %eax
pushl %eax
popl %eax
movl %eax, -8(%ebp)
pushl $3
popl %eax
movl %eax, -4(%ebp)
pushl $2
popl %eax
movl %eax, -12(%ebp)
pushl -4(%ebp)
pushl $5
popl %eax
popl %ebx
cmp %eax, %ebx
jl L1
pushl $0
jmp L2
L1:
pushl $1
L2:
popl %eax
movl $0, %ebx
cmp %eax, %ebx
je skip_if_0
pushl $7
popl %eax
movl %eax, -4(%ebp)
skip_if_0:
pushl $1
pushl $5
popl %eax
movl %eax, 	-20(%ebp)
pushl $1
popl %eax
imul $4, %eax
movl %ebp, %ebx
subl $0, %ebp
addl %eax, %ebp
pushl 0(%ebp)
movl %ebx, %ebp
popl %eax
movl %eax, -12(%ebp)
pushl -12(%ebp)
popl %eax
movl %ebp, %esp
popl %ebp
ret

