#ifndef OS_PROJEKAT_TCB_HPP
#define OS_PROJEKAT_TCB_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"
#include "MemoryAllocator.hpp"


// Thread Control Block
class TCB
{
public:
    ~TCB() { delete[] stack; }

    static void dispatch();
   static int exit();
    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    void *getArg() const;

    void setArg(void *arg);


    using Body = void (*)(void*);//ovde void * izmedju zagrada

    static TCB *createThread(Body body,void *arg,void *stack_space);

    static void yield();

    static TCB *running;

    void *operator new(size_t n)
    {
       void* ret= memory_alloc(n);

        return ret;
       // return __mem_alloc(n);
    }

    void *operator new[](size_t n)
    {
        return memory_alloc(n);
        //return __mem_alloc(n);
    }

    void operator delete(void *p) noexcept
    {
       memory_free(p);
        //__mem_free(p);
    }

    void operator delete[](void *p) noexcept
    {
        memory_free(p);
        //__mem_free(p);
    }

    void setIsBlocked(bool b);

    void setWoken(int i);

    int getWoken();

private:
    TCB(Body body, void *arg,void* stack_space) :
            body(body),
            stack(body != nullptr ? (uint64*)stack_space : nullptr),
            context({(uint64) &threadWrapper,
                     stack != nullptr ? (uint64) stack_space + DEFAULT_STACK_SIZE : 0
                    }),
            arg(arg),
            finished(false),
            blocked(false),
            exited(false)
    {}

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    uint64 *stack;
    Context context;
    void *arg;
    bool finished;
    bool blocked;
    bool exited;
    int wokenRetVal = 0;

    friend class Riscv;

    static void threadWrapper();

    static void contextSwitch(Context *oldContext, Context *runningContext);




    static uint64 constexpr STACK_SIZE = 1024;

    bool isBlocked();
};

#endif //OS_PROJEKAT_TCB_HPP
