#ifndef OS_PROJEKAT_SYSCALL_C_HPP
#define OS_PROJEKAT_SYSCALL_C_HPP
#include "tcb.hpp"

extern "C" void thread_dispatch();
class TCB;
void putc(char c);
char getc();
int thread_create(TCB** handle, void(*start_routine)(void*), void* arg);
int thread_create_cpp_api(TCB **handle, void (*start_routine)(void *), void *arg);
int thread_start_cpp_api(TCB **handle);
void thread_dispatch();
void* mem_alloc(size_t size);
int mem_free(void*);
class Semafor;
typedef Semafor* sem_t;
typedef TCB* thread_t;//ili da menjam u testu TCB*
int sem_open (sem_t* handle,unsigned init);
int sem_close (sem_t handle);
int sem_wait (sem_t id);
int sem_signal (sem_t id);

#endif //OS_PROJEKAT_SYSCALL_C_HPP