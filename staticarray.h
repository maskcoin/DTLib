#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "array.h"

namespace DTLib
{

template < typename T, int N >
class StaticArray : public Array< T >
{
protected:
    T m_space[N];
public:
    StaticArray();

    // 拷贝构造和赋值操作
    StaticArray(const StaticArray<T, N>& obj);
    StaticArray<T, N>& operator = (const StaticArray<T, N>& obj);

    int length() const;
};

template < typename T, int N>
StaticArray<T, N>::StaticArray()
{
    this->m_array = m_space;
}

template < typename T, int N>
StaticArray<T, N>::StaticArray(const StaticArray<T, N>& obj)
{
    this->m_array = m_space;

    for(int i=0; i<N; i++)
    {
        this->m_array[i] = obj.m_array[i];
    }
}

template < typename T, int N >
StaticArray<T, N>& StaticArray<T, N>::operator =(const StaticArray<T, N>& obj)
{
    if( this != &obj)
    {
        for(int i=0; i<N; i++)
        {
            this->m_array[i] = obj.m_array[i];
        }
    }

    return *this;
}

template < typename T, int N >
int StaticArray<T, N>::length() const
{
    return N;
}

}



#endif // STATICARRAY_H
