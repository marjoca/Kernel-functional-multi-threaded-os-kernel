.global mem_alloc_kernel
.type mem_alloc_kernel,@function
mem_alloc_kernel:
mv a1,a0
addi a0,x0,0x01
ecall
ret