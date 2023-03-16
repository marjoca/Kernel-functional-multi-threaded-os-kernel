.global __sem_open
.type __sem_open,@function
__sem_open:
mv a2,a1
mv a1,a0
addi a0,x0,0x21
ecall
ret