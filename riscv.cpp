#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../lib/console.h"
#include "../h/semafor.hpp"
#include "../lib/mem.h"
#include "../h/MemoryAllocator.hpp"

void Riscv::popSppSpie()
{
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(1 << 8));
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile("sret");
}


void Riscv::obradiPrekid() {
    uint64 scause;
    scause=r_scause();

    if(scause==0x0000000000000008UL || scause==0x0000000000000009UL){//ecall
        uint64 a0;
        void* a1;
        void* a2;
        void* a3;
        void* a4;
        __asm__ volatile("ld %0,80(s0)":"=r"(a0));
        __asm__ volatile("ld %0,88(s0)":"=r"(a1));
        __asm__ volatile("ld %0,96(s0)":"=r"(a2));
        __asm__ volatile("ld %0,104(s0)":"=r"(a3));
        __asm__ volatile("ld %0,112(s0)":"=r"(a4));
        uint64 sepc=r_sepc();//ovde mora sepc da se sacuva
        obrada_sistemskihpoziva(a0,a1,a2,a3,a4);
        __asm__ volatile("sd a0,80(fp)");
        TCB::dispatch();
        sepc+=4;
        w_sepc(sepc);
    }
    else if (scause == 0x8000000000000001UL) {
        Riscv::mc_sip(Riscv::SIP_SSIP);
    }
    else if (scause == 0x8000000000000009UL) {
        console_handler();
    }

}
void Riscv::obrada_sistemskihpoziva(uint64 a0,void* a1, void* a2, void* a3,void* a4) {

    if(a0==0x11){
        TCB** handle= (TCB**)a1;
        TCB::Body body=(TCB::Body)a2;

        void* arg=a3;
        void* stack_space=a4;
        uint64 ret = 1;


        if(handle!= nullptr){
            *handle=TCB::createThread(body,arg,stack_space);
            ret=0;
            Scheduler::put(*handle);
        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x03){
        TCB** handle= (TCB**)a1;
        TCB::Body body=(TCB::Body)a2;

        void* arg=a3;
        void* stack_space=a4;
        uint64 ret = 1;


        if(handle!= nullptr){
            *handle=TCB::createThread(body,arg,stack_space);
            ret=0;

        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x04){
        TCB** handle= (TCB**)a1;
        uint64 ret;
        if(handle!=nullptr){
            Scheduler::put(*handle);
            ret=1;
        }
        else{
            ret=-1;
        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x13){
        return;
    }
    if(a0==0x12){
        uint64 ret=TCB::exit();
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x01){
        size_t size=(size_t)a1;
       void* ret=memory_alloc(size);
      // void* ret= __mem_alloc(size);
        __asm__ volatile("mv a0,%0"::"r"(ret));

        return;
    }
    if(a0==0x02){
        void* parametar=a1;
        uint64 ret=memory_free(parametar);
     //  uint64 ret= __mem_free(parametar);
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x21){
        Semafor** handle= (Semafor**)a1;
       uint64 init=(uint64)a2;
        uint64 ret=-1;
        if(handle!= nullptr){
            *handle=Semafor::createSemafor(init);
            ret=0;
        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x22){
        Semafor* handle= (Semafor*)a1;
        uint64 ret=-1;

        if(handle!= nullptr){
           ret=handle->close();
        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x23){
        Semafor* handle= (Semafor*)a1;
        uint64 ret=-1;
        if(handle!= nullptr){
            ret=handle->wait();
        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x24){
        Semafor* handle= (Semafor*)a1;
        uint64 ret=-1;

        if(handle!= nullptr){
            ret=handle->signal();

        }
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
    if(a0==0x42){
        char c=*((char*)&a1);//ovaj kast je upitan
        __putc(c);
        return;
    }
    if(a0==0x41){
        char ret=__getc();
        __asm__ volatile("mv a0,%0"::"r"(ret));
        return;
    }
}

