.global __getc_kernel
.type __getc_kernel,@function
__getc_kernel:
addi a0,x0,0x41
ecall
ret