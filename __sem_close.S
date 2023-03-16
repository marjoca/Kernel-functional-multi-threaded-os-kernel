.global __sem_close
.type __sem_close,@function
__sem_close:
mv a1,a0
addi a0,x0,0x22
ecall
ret