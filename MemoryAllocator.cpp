#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"


const void* FREE_MEM_HEAD;

struct FreeMem{
    size_t size;
    FreeMem* next;
    FreeMem* prev;
};


void memory_initialization(){//da li treba potpis f-je u hpp
    FREE_MEM_HEAD=HEAP_START_ADDR;
    FreeMem* prviSlobodniBlok=(FreeMem*)FREE_MEM_HEAD;
    prviSlobodniBlok->size=(size_t)HEAP_END_ADDR-(size_t)HEAP_START_ADDR;
    prviSlobodniBlok->next= nullptr;
    prviSlobodniBlok->prev=nullptr;

}
void* memory_alloc(size_t size){
    size = size + sizeof(FreeMem);
    //size se pretvori u broj blokova
    for(FreeMem* cur=(FreeMem*)FREE_MEM_HEAD;cur!= nullptr;cur=cur->next){
        if(cur->size>=size){
            size_t sizeLeft=cur->size-size;
            if(sizeLeft>=sizeof(FreeMem)){
                FreeMem* newSegment=(FreeMem*)(((char*)cur)+size);
                newSegment->size=sizeLeft;
                if(cur->prev){
                    cur->prev->next=newSegment;
                }
                else{//nema prethodnog
                    FREE_MEM_HEAD=newSegment;
                }
                if(cur->next){
                    cur->next->prev=newSegment;
                }
                newSegment->prev=cur->prev;
                newSegment->next=cur->next;
                cur->size = size;
                return (char*) cur + sizeof(FreeMem);
            }
            else{
                if(cur->prev)cur->prev->next=cur->next;
                else FREE_MEM_HEAD=cur->next;
                if(cur->next) cur->next->prev=cur->prev;
                cur->size = size + sizeLeft;
                return (char*) cur + sizeof(FreeMem);
            }
        }
    }
    return nullptr;//u slucaju neuspeha
}
int tryToJoin(FreeMem* cur){
    if(!cur)return 0;
    if(cur->next && (char*)cur+cur->size==(char*)(cur->next)){
        cur->size+=cur->next->size;
        cur->next=cur->next->next;
        if(cur->next)cur->next->prev=cur;
        return 1;
    }
    else{
        return 0;
    }
}
int memory_free(void* ptr) {
    ptr = (char*) ptr - sizeof(FreeMem);
    FreeMem *cur = 0;
    if (!FREE_MEM_HEAD || ((FreeMem *) ptr) < FREE_MEM_HEAD)
        cur = 0;
    else{
        for (cur = (FreeMem *) FREE_MEM_HEAD; cur->next != 0 && ((FreeMem *) ptr) > (cur->next); cur = cur->next);
    }
    FreeMem* newSeg=((FreeMem*)ptr);
    newSeg->size=((FreeMem*)ptr)->size;
    newSeg->prev=cur;
    if(cur) newSeg->next=cur->next;
    else newSeg->next=(FreeMem*)FREE_MEM_HEAD;
    if(newSeg->next) newSeg->next->prev=newSeg;
    if(cur) cur->next=newSeg;
    else FREE_MEM_HEAD=newSeg;
    tryToJoin(newSeg);
    tryToJoin(cur);
return 0;
}
