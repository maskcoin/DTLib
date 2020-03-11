#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "array.h"
#include "exception.h"

namespace DTLib
{

template < typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    T* copy(T* array, int len, int newLen);
    void update(T* array, int length);
    void init(T* array, int length);
public:
    DynamicArray(int length = 0);

    DynamicArray(const DynamicArray<T>& obj);
    DynamicArray<T>& operator = (const DynamicArray<T>& obj);
    void resize(int length);

    int length() const;

    ~DynamicArray();
};

template < typename T >
DynamicArray<T>::DynamicArray(int length)
{
    init(new T[length], length);
}

template < typename T >
DynamicArray<T>::DynamicArray(const DynamicArray<T>& obj)
{

    init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);

}

template < typename T>
DynamicArray<T>& DynamicArray<T>::operator = (const DynamicArray<T>& obj)
{
    if( this != &obj )
    {
        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    return *this;
}

template < typename T >
void DynamicArray<T>::resize(int length)
{
    if( m_length != length )
    {
        update(copy(this->m_array, m_length, length), length);
    }
}

template < typename T >
int DynamicArray<T>::length() const
{
    return m_length;
}

template < typename T >
DynamicArray<T>::~DynamicArray()
{
    delete [] this->m_array;
}

template < typename T >
T* DynamicArray<T>::copy(T* array, int len, int newLen)
{
    T* ret = new T[newLen];

    if( ret )
    {
        int size = (len <= newLen) ? len : newLen;
        for(int i=0; i<size; i++)
        {
            ret[i] = array[i];
        }
    }

    return ret;
}

template < typename T >
void DynamicArray<T>::update(T* array, int length)
{
    if( array != nullptr )
    {
        T* temp = this->m_array;

        this->m_array = array;
        m_length = length;

        delete [] temp;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamiArray object...");
    }
}

template < typename T >
void DynamicArray<T>::init(T* array, int length)
{
    if( array )
    {
        this->m_array = array;
        m_length = length;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to init DynamiArray object...");
    }
}

}



#endif // DYNAMICARRAY_H
