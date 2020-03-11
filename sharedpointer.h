#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "pointer.h"
#include "exception.h"


namespace DTLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        m_ref = obj.m_ref;
        if( this->m_ref )
        {
            (*m_ref)++;
        }
    }
public:
    SharedPointer(T* p = nullptr) : m_ref(nullptr)
    {
        if( p )
        {
            this->m_ref = reinterpret_cast<int*>(std::malloc(sizeof(int)));

            if( this->m_ref )
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj)
    {
        assign(obj);
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if( this != &obj )
        {
            clear();
            assign(obj);
        }

        return *this;
    }

    void clear()  // 将当前指针置为空
    {
        T* toDel = this->m_pointer;
        int* ref = m_ref;

        this->m_pointer = nullptr;
        m_ref = nullptr;

        if( ref )
        {
            (*ref)--;

            if( *ref == 0 )
            {
                free(ref);

                delete toDel;
            }
        }
    }

    bool operator == (const SharedPointer<T>& obj)
    {
        return (this->m_pointer == obj.m_pointer);
    }

    bool operator != (const SharedPointer<T>& obj)
    {
        return (this->m_pointer != obj.m_pointer);
    }

    ~SharedPointer()
    {
        clear();
    }

};

}


#endif // SHAREDPOINTER_H
