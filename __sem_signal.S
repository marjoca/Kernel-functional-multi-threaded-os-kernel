.global __sem_signal
.type __sem_signal,@function
__sem_signal:
mv a1,a0
addi a0,x0,0x24
ecall
ret