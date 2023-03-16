.global __putc_kernel
.type __putc_kernel,@function
__putc_kernel:
mv a1,a0
addi a0,x0,0x42
ecall
ret