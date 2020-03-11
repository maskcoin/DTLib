#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "seqlist.h"
#include "exception.h"

namespace DTLib
{

template < typename T >
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity; // 顺序存储空间的大小
public:
    DynamicList(int capacity);  // 申请堆空间
    int capacity() const;
    /* 重新设置顺序存储空间的大小 */
    void resize(int capacity);
    ~DynamicList(); // 归还空间
};

template < typename T >
DynamicList<T>::DynamicList(int capacity)
{
    this->m_array = new T[capacity];

    if( this->m_array != nullptr )
    {
        m_capacity = capacity;
        this->m_length = 0;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object...");
    }
}

template < typename T >
int DynamicList<T>::capacity() const
{
    return m_capacity;
}

template < typename T >
void DynamicList<T>::resize(int capacity)
{
    if( capacity != m_capacity)
    {

        T* new_array = new T[capacity];

        if( new_array != nullptr )
        {
            int length = (this->m_length < capacity ? this->m_length : capacity);

            for(int i=0; i<length; i++)
            {
                new_array[i] = this->m_array[i];
            }

            T* temp = this->m_array;

            this->m_array = new_array;
            this->m_length = length;
            this->m_capacity = capacity;

            delete [] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList object...");
        }
    }

}

template < typename T >
DynamicList<T>::~DynamicList()
{
    delete [] this->m_array;
}

}

#endif // DYNAMICLIST_H
