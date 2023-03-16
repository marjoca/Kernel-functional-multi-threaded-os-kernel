.global __thread_exit
.type __thread_exit,@function
__thread_exit:
addi a0,x0,0x12
ecall
ret