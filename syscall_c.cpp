
#include "../h/tcb.hpp"
#include "../h/syscall_c.hpp"
#include "../lib/console.h"

extern "C" int __thread_create(TCB**  handle,void (*start_routine)(void*),void *arg,void* stack_space);
extern "C" int __thread_create_cpp_api(TCB**  handle,void (*start_routine)(void*),void *arg,void* stack_space);
extern "C" int __thread_start_cpp_api(TCB**  handle);
extern "C" void* mem_alloc_kernel(size_t size);
extern "C" int mem_free_kernel(void* ptr);
extern "C" int __sem_open(sem_t* handle,unsigned init);
extern "C" int __sem_close(sem_t handle);
extern "C" int __sem_wait(sem_t id);
extern "C" int __sem_signal(sem_t id);
extern "C" void __putc_kernel(char c);
extern "C" char __getc_kernel();
extern "C" int __thread_exit();
int thread_create(TCB **handle, void (*start_routine)(void *), void *arg) {
    void *stack_space=mem_alloc(1024*sizeof (uint64));
    __thread_create(handle,start_routine,arg,stack_space);
    uint64 ret;
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}
int thread_create_cpp_api(TCB **handle, void (*start_routine)(void *), void *arg){
    void *stack_space=mem_alloc(1024*sizeof (uint64));
    __thread_create_cpp_api(handle,start_routine,arg,stack_space);
    uint64 ret;
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}
int thread_start_cpp_api(TCB **handle){
    __thread_start_cpp_api(handle);
    uint64 ret;
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;

}
int thread_exit(){
    __thread_exit();
    uint64 ret;
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}
void* mem_alloc(size_t size){

    void* ret;
    mem_alloc_kernel(size);
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}

int mem_free(void* ptr){
    mem_free_kernel(ptr); //ili uint64 ret= to
    uint64 ret;
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}
void putc(char c){
   __putc_kernel(c);
}
char getc(){
    return __getc_kernel();
}
int sem_open(sem_t* handle,unsigned init){
    uint64 ret;
    __sem_open(handle,init);
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}
int sem_close (sem_t handle){
    /*Oslobađa semafor sa datom ručkom. Sve niti koje su se
    zatekle da čekaju na semaforu se deblokiraju, pri čemu njihov
    wait vraća grešku. U slučaju uspeha vraća 0, a u slučaju
    neuspeha vraća negativnu vrednost (kôd greške).*/
    uint64 ret;
    __sem_close(handle);
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;

}
int sem_wait (sem_t id){
    uint64 ret;
    __sem_wait(id);
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}
int sem_signal (sem_t id){
    uint64 ret;
    __sem_signal(id);
    __asm__ volatile("mv %0,a0":"=r"(ret));
    return ret;
}

