
#include "../h/tcb.hpp"


#include "../h/riscv.hpp"
#include "../h/userMain.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_cpp.hpp"

sem_t semWaitForUserMainToFinish;

void userMainWrapper(void *) {
    userMain();
    sem_signal(semWaitForUserMainToFinish);
}

extern "C" void prekidnaRutina();

int main() {
    memory_initialization();
    TCB::running = TCB::createThread(nullptr, nullptr, nullptr);
    Riscv::w_stvec((uint64) &(Riscv::prekidnaRutina));
//    thread_create(&userMainThread,userMainWrapper, nullptr);
    sem_open(&semWaitForUserMainToFinish, 0);
    Thread *userMainThread = new Thread(userMainWrapper, nullptr);
    userMainThread->start();
    sem_wait(semWaitForUserMainToFinish);
    delete userMainThread;
//        __asm__ volatile("csrs sstatus, 0x02");

    return 0;
}

