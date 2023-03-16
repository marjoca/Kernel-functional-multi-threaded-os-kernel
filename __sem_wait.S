.global __sem_wait
.type __sem_wait,@function
__sem_wait:
mv a1,a0
addi a0,x0,0x23
ecall
ret