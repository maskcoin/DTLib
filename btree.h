#ifndef BTREE_H
#define BTREE_H

#include "tree.h"
#include "btreenode.h"
#include "exception.h"
#include "linkqueue.h"
#include "dynamicarray.h"

namespace DTLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template < typename T >
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = nullptr;

        if( node != nullptr )
        {
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                ret = find(node->left, value);

                if( ret == nullptr )
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = nullptr;

        if( node != nullptr )
        {
            if( node == obj )
            {
                ret = node;
            }
            else
            {
                ret = find(node->left, obj);

                if( ret == nullptr )
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;

        if( pos == ANY )
        {
            if( np->left == nullptr )
            {
                np->left = n;
            }
            else if( np->right == nullptr )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == LEFT )
        {
            if( np->left == nullptr )
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == RIGHT )
        {
            if( np->right == nullptr )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    /* 假设node存在于该树中，从该树中删除node */
    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>;

        if( ret != nullptr )
        {
            if( root() == node )
            {
                this->m_root = nullptr;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( parent->left == node )
                {
                    parent->left = nullptr;
                }
                else if( parent->right == node )
                {
                    parent->right = nullptr;
                }
            }

            node->parent = nullptr;

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new tree ...");
        }
    }

    virtual void clear(BTreeNode<T>* node)
    {
        if( node != nullptr )
        {
            clear(node->left);
            clear(node->right);

            if( node->flag() )
            {
                delete node;
            }
        }
    }

    virtual int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != nullptr )
        {
            BTreeNode<T>* child[] = { node->left, node->right };

            ret = (!!node->left + !!node->right);

            for(int i=0; (i < 2) && (ret < 2); i++)
            {
                ret = (ret < degree(child[i])) ? degree(child[i]) : ret;
            }
        }

        return ret;
    }

    virtual int count(BTreeNode<T>* node) const
    {
        return (node != nullptr) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    virtual int height(BTreeNode<T>* node) const
    {
        return (node != nullptr) ? (((height(node->left) > height(node->right)) ? height(node->left) : height(node->right)) + 1) : 0;
    }

    void clone(const BTreeNode<T>* node, BTreeNode<T>*& ret) const
    {
        if( node != nullptr )
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != nullptr )
            {
                ret->value = node->value;

                clone(node->left, ret->left);
                clone(node->right, ret->right);

                if( ret->left != nullptr )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != nullptr )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new node ...");
            }
        }
    }

    bool equal(BTreeNode<T>* ln, BTreeNode<T>* rn)
    {
        bool ret = (ln == rn);

        if( !ret )
        {
            if( (ln == nullptr) || (rn == nullptr) )
            {
                ret = false;
            }
            else
            {
                ret = (ln->value == rn->value) && equal(ln->left, rn->left) && equal(ln->right, rn->right);
            }
        }

        return ret;
    }

    void add(const BTreeNode<T>* node1, const BTreeNode<T>* node2, BTreeNode<T>*& ret) const
    {
        if( node1 == nullptr )
        {
            clone(node2, ret);
            return;
        }
        else if(node2 == nullptr )
        {
            clone(node1, ret);
            return;
        }
        else
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != nullptr )
            {
                ret->value = node1->value + node2->value;

                add(node1->left, node2->left, ret->left);
                add(node1->right, node2->right, ret->right);

                if( ret->left != nullptr )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != nullptr )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new node ...");
            }
        }
    }

    void traversal(BTreeNode<T>* node, BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
    {
        if( node != nullptr )
        {
            switch( order )
            {
            case PreOrder:
                queue.add(node);
                traversal(node->left, order, queue);
                traversal(node->right, order, queue);
                break;

            case InOrder:
                traversal(node->left, order, queue);
                queue.add(node);
                traversal(node->right, order, queue);
                break;

            case PostOrder:
                traversal(node->left, order, queue);
                traversal(node->right, order, queue);
                queue.add(node);
                break;

            case LevelOrder:
                for(begin(); !end(); next())
                {
                    queue.add(m_queue.front());
                }
                break;

            default:
                THROW_EXCEPTION(InvalidOperationException, "Parameter order is invalid ...");
                break;
            }
        }
    }

    void thread(BTreeNode<T>* node, BTTraversal order, BTreeNode<T>*& ret)
    {
        if( node != nullptr )
        {
            LinkQueue<BTreeNode<T>*> queue;

            traversal(node, order, queue);

            if( queue.length() > 0 )
            {
                ret = queue.front();
                ret->left = nullptr;
                queue.remove();
            }

            BTreeNode<T>* tmp = ret;

            while( queue.length() > 0 )
            {
                tmp->right = queue.front();

                queue.front()->left = tmp;

                tmp = queue.front();

                queue.remove();
            }

            tmp->right = nullptr;
        }
    }

public:
    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    virtual bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if( node != nullptr )
        {
            if( this->m_root == nullptr )
            {
                this->m_root = node;
                node->parent = nullptr;
            }
            else
            {
                BTreeNode<T>* n = dynamic_cast<BTreeNode<T>*>(node);

                BTreeNode<T>* np = find(n->parent);

                if( np != nullptr )
                {
                    ret = insert(n, np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be null ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        int ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if( node != nullptr )
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if ( !ret )
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = nullptr;
        BTreeNode<T>* node = find(value);

        if( node != nullptr )
        {
            remove(node, ret);

            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = nullptr;

        node = find(node);

        if( node != nullptr )
        {
             remove(dynamic_cast<BTreeNode<T>*>(node), ret);

             m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        clear(root());

        m_queue.clear();

        this->m_root = nullptr;
    }

    bool begin()
    {
        bool ret = (root() != nullptr);

        if( ret )
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if( ret )
        {
            BTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            if( node->left != nullptr )
            {
                m_queue.add(node->left);
            }

            if( node->right != nullptr )
            {
                m_queue.add(node->right);
            }
        }

        return ret;
    }

    T current()
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(count());
        LinkQueue<BTreeNode<T>*> queue;

        if( ret != nullptr )
        {
            traversal(root(), order, queue);

            for(int i=0; i< ret->length(); i++)
            {
                ret->set(i, queue.front()->value);

                queue.remove();
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new DynamicArray ...");
        }

        return ret;
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>;

        if( ret != nullptr )
        {
            BTreeNode<T>* node = nullptr;
            clone(root(), node);
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }

        return ret;
    }

    bool operator == (const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator != (const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    SharedPointer < BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T>* ret = nullptr;

        ret = new BTree<T>;

        if( ret != nullptr )
        {
            BTreeNode<T>* node = nullptr;

            add(root(), btree.root(), node);

            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }

        return ret;
    }

    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = nullptr;

        thread(root(), order, ret);

        this->m_root = nullptr;

        m_queue.clear();

        return ret;
    }

    ~BTree()
    {
        clear();
    }

};

}



#endif // BTREE_H
