.global __thread_start_cpp_api
.type __thread_start_cpp_api,@function
__thread_start_cpp_api:
mv a1,a0
addi a0,x0,0x04
ecall
ret