//
// Created by os on 9/10/22.
//
#include "../h/syscall_cpp.hpp"

void* operator new (size_t size){
    return mem_alloc(size);
}
void operator delete(void *ptr){
    mem_free(ptr);
}
void Thread::threadWrapper(void* thr){
    Thread* thread=(Thread*)thr;
    thread->run();

}
Thread::Thread(void (*body)(void *), void *arg){

    thread_create_cpp_api(&myHandle,body,arg);//proveriti negde da li su argumenti razliciti od nullptr

}
Thread::Thread()
{
    thread_create_cpp_api(&myHandle,threadWrapper, (void*)this);//za arrg this???

}

int Thread::start() {
    return thread_start_cpp_api(&myHandle);
}
Thread::~Thread (){

}
void Thread::dispatch() {
    thread_dispatch();
}
Semaphore::Semaphore(unsigned init)
{
    sem_open(&myHandle,init);
}
Semaphore::~Semaphore (){
    sem_close(myHandle);
}
int Semaphore::wait()
{
    return sem_wait(myHandle);
}
int Semaphore::signal() {
    return sem_signal(myHandle);
}
void Console::putc(char c){
    ::putc(c);
}
char Console::getc(){
    return ::getc();
}



