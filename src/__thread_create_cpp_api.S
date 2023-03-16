.global __thread_create_cpp_api
.type __thread_create_cpp_api,@function
__thread_create_cpp_api:
mv a4,a3
mv a3,a2
mv a2,a1
mv a1,a0
addi a0,x0,0x03
ecall
ret