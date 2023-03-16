
#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/syscall_c.hpp"

TCB *TCB::running = nullptr;

TCB *TCB::createThread(Body body,void* arg,void* stack_space)
{
    return new TCB(body,arg,stack_space);
}

void TCB::yield()
{

}
int TCB::exit() {//ovo je upitno
    if(running!= nullptr){

        return 0;
    }
    else{
        return -1;
    }

}
void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished() && !old->isBlocked()) { Scheduler::put(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}


void TCB::threadWrapper() {
    Riscv::popSppSpie();
    running->body(running->arg);//running->arg
    running->setFinished(true);
    thread_dispatch();
}

void *TCB::getArg() const {
    return arg;
}

void TCB::setArg(void *arg) {
    TCB::arg = arg;
}

bool TCB::isBlocked() {
    return blocked;
}

void TCB::setIsBlocked(bool b) {
    blocked = b;
}

void TCB::setWoken(int i) {
    wokenRetVal = i;
}

int TCB::getWoken() {
    return wokenRetVal;
}
