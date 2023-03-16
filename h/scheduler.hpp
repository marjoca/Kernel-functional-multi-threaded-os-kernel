#ifndef OS_PROJEKAT_SCHEDULER_HPP
#define OS_PROJEKAT_SCHEDULER_HPP

#include "list.hpp"

class TCB;

class Scheduler
{
private:
    static List<TCB> readyCoroutineQueue;

public:
    static TCB *get();

    static void put(TCB *tcb);

};

#endif //OS_PROJEKAT_SCHEDULER_HPP
