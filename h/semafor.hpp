#ifndef OS_PROJEKAT_SEMAFOR_HPP
#define OS_PROJEKAT_SEMAFOR_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"
#include "MemoryAllocator.hpp"


// Thread Control Block
class Semafor
{
public:
    ~Semafor() {  }

        static Semafor *createSemafor(unsigned init);
      int wait();
      int signal();
      int close();


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

private:
    Semafor(unsigned init) :
            val(init),zatvoren(false)
            {}

    int val;
   bool zatvoren;
   List<TCB> blocked;








};

#endif //OS_PROJEKAT_SEMAFOR_HPP
