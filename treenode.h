#ifndef TREENODE_H
#define TREENODE_H

#include "object.h"

namespace DTLib
{

template < typename T >
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);

    TreeNode<T>& operator = (const TreeNode<T>&);

    void* operator new(unsigned long int size) throw()
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        parent = nullptr;
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode()
{

}

}

#endif // TREENODE_H
