#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "linklist.h"

namespace DTLib
{

template < typename T >
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node* last() const
    {
        return  this->position(this->m_length - 1)->m_next;

    }

    void last_to_first() const
    {
        last()->m_next = this->m_header.m_next;
    }

public:
    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;

        i = i % (this->m_length + 1);

        ret = LinkList<T>::insert(i, e);

        if( ret && (i == 0) )
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        if( i == 0 )
        {
            Node* toDel = this->m_header.m_next;

            if( toDel != nullptr )
            {
                this->m_header.m_next = toDel->m_next;
                this->m_length--;

                if( this->m_length > 0 )
                {
                    last_to_first();

                    if( this->m_current == toDel )
                    {
                        this->m_current = toDel->m_next;
                    }
                }
                else
                {
                    this->m_header.m_next = nullptr;
                    this->m_current = nullptr;
                }

                this->destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        return LinkList<T>::set(mod(i), e);
    }

    bool get(int i, T& e) const
    {
        return LinkList<T>::get(mod(i), e);
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }

    int find(const T& e) const
    {
        int ret = -1;
        Node* slider = this->m_header.m_next;

        for(int i=0; i<this->m_length; i++)
        {
            if ( slider->m_value == e )
            {
                ret = i;
                break;
            }

            slider = slider->m_next;
        }

        return ret;
    }

    void clear()
    {
        while ( this->m_length > 1 )
        {
            remove(1);
        }

        if ( this->m_length == 1 )
        {
            remove(0);
        }
    }

    bool move(int i, int step = 1)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == nullptr);
    }

    ~CircleList()
    {
        clear();
    }
};
}



#endif // CIRCLELIST_H
