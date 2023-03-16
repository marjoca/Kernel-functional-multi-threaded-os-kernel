//
// Created by os on 9/10/22.
//

#ifndef PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#define PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#include "syscall_c.hpp"
void* operator new (size_t);
void operator delete(void*);

class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    static int sleep (time_t);
    static void threadWrapper(void*);
protected:
    Thread ();
    virtual void run () {}

private:
    TCB* myHandle;//thread_t je tip handlea

};
class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};
class Console {
public:
    static char getc ();
    static void putc (char);
};
#endif //PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
