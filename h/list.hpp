

#ifndef OS_PROJEKAT_LIST_HPP
#define OS_PROJEKAT_LIST_HPP


#include "../lib/mem.h"
#include "MemoryAllocator.hpp"

template<typename T>
class List
{
private:

    struct Elem
    {

        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next) {}
        void *operator new(size_t n)
        {
            return memory_alloc(n);
           // return __mem_alloc(n);
        }

        void *operator new[](size_t n)
        {
            return memory_alloc(n);
           // return __mem_alloc(n);
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
    };

    Elem *head, *tail;
    uint64 br;
public:
    List() : head(0), tail(0),br(0) {}

    List(const List<T> &) = delete;

    List<T> &operator=(const List<T> &) = delete;

    uint64 length(){
        return br;
    }

    void addFirst(T *data)
    {
        Elem *elem = new Elem(data, head);
        head = elem;
        br++;
        if (!tail) { tail = head; }
    }

    void addLast(T *data)
    {
        Elem *elem = new Elem(data, 0);
        br++;
        if (tail)
        {
            tail->next = elem;
            tail = elem;
        } else
        {
            head = tail = elem;
        }
    }

    T *removeFirst()
    {
        if (!head) { return 0; }
br--;
        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T *peekFirst()
    {
        if (!head) { return 0; }
        return head->data;
    }

    T *removeLast()
    {
        if (!head) { return 0; }
br--;
        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T *peekLast()
    {
        if (!tail) { return 0; }
        return tail->data;
    }

};

#endif //OS_PROJEKAT_LIST_HPP


