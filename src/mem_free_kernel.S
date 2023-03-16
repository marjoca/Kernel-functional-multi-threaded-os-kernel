.global mem_free_kernel
.type mem_free_kernel,@function
mem_free_kernel:
mv a1,a0
addi a0,x0,0x02
ecall
ret