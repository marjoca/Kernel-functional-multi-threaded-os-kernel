#include "../h/semafor.hpp"
#include "../h/scheduler.hpp"
#include "../h/tcb.hpp"
Semafor *Semafor::createSemafor(unsigned init)
{
    return new Semafor(init);
}

int Semafor::wait(){
    val--;
    if(val <0){
        TCB::running->setWoken(0);
        blocked.addLast(TCB::running);
        TCB::running->setIsBlocked(true);
       TCB::dispatch();
    }
    return TCB::running->getWoken();
}

int Semafor::signal(){
    val++;
    if(val<=0){
        TCB* thread=blocked.removeFirst();
        thread->setIsBlocked(false);
        Scheduler::put(thread);
    }
    return 0;
}
int Semafor::close(){
    /*Oslobađa semafor sa datom ručkom. Sve niti koje su se
   zatekle da čekaju na semaforu se deblokiraju, pri čemu njihov
   wait vraća grešku. U slučaju uspeha vraća 0, a u slučaju
   neuspeha vraća negativnu vrednost (kôd greške).*/
    val=0;
    zatvoren=true;
    uint64 size = blocked.length();
   for(uint64 i=0;i < size;i++){
       TCB* thread=blocked.removeFirst();
       thread->setIsBlocked(false);
       thread->setWoken(-1);
       Scheduler::put(thread);
   }
   return 0;
}
