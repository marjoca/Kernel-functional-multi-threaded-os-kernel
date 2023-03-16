.global __thread_create
.type __thread_create,@function
__thread_create:
mv a4,a3
mv a3,a2
mv a2,a1
mv a1,a0
addi a0,x0,0x11
ecall
ret