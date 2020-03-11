#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "exception.h"

namespace DTLib
{

template < typename T >
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, const T& e);


    virtual bool get(int i, T& e) const;


    T& operator [] (int i);


    T operator [] (int i) const;

    T* array() const
    {
        return m_array;
    }

    virtual int length() const = 0;
};


template < typename T >
bool Array<T>::set(int i, const T& e)
{
    bool ret = ((0 <= i) &&  (i < this->length()));

    if( ret )
    {
        m_array[i] = e;
    }

    return ret;
}

template < typename T >
bool Array<T>::get(int i, T& e) const
{
    bool ret = ((0 <= i) &&  (i < this->length()));

    if ( ret )
    {
        e = m_array[i];
    }

    return ret;
}

template < typename T >
T& Array<T>::operator [] (int i)
{
    if( (0 <= i) && (i < this->length()) )
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
}

template < typename T >
T Array<T>::operator [] (int i) const
{
    return (const_cast<Array<T>&>(*this))[i];
}


}

#endif // ARRAY_H
