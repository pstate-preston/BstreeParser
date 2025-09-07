/**
 * Implementation file for function of the Bstree<T> class
 * @author Duncan, Preston Gautreaux
 * @see Bstree.h
 * <pre>
 * File: Bstree.cpp
 * Date: 11-27-2024
 * Course: csc 1254 Section 1
 * Instructor: Dr. Duncan
 * </pre>
 */

using namespace std;

#include "Bstree.h"
#include <algorithm>
#include <vector>

/* Nested Node class definitions */
template <typename T>
Bstree<T>::Node::Node(T item)
{
    data = item;
    left = nullptr;
    right = nullptr;
}

/* Outer Bstree class definitions */
template <typename T>
Bstree<T>::Bstree()
{
    root = nullptr;
    order = 0;
}

template <typename T>
Bstree<T>::Bstree(const Bstree<T>& other)
{
    root = nullptr;
    order = other.order;
    recCopy(root, other.root);
}

template <typename T>
Bstree<T>::Bstree(Bstree<T>&& other)
{
    root = other.root;
    other.root = nullptr;
    order = other.order;
    other.order = 0;
}

template <typename T>
Bstree<T>::~Bstree()
{
    recDestroy(root);
}

template <typename T>
Bstree<T>& Bstree<T>::operator=(const Bstree<T>& other)
{
    if (this != &other)
    {
        (*this).~Bstree();
        Bstree<T> clone(other);
        root = clone.root;
        order = clone.order;
        clone.order = 0;
        clone.root = nullptr;
    }
    return *this;
}

template <typename T>
bool Bstree<T>::empty() const
{
    return root == nullptr;
}

template<typename T>
void Bstree<T>::insert(T item)
{
    Node* tmp;
    Node* newnode = new Node(item);

    /* If it is the first node in the tree */
    if (!root)
    {
        root = newnode;
        order++;
        return;
    }
    /*find where it should go */
    tmp = root;
    while (true)
    {
        if (tmp->data == item)
        { /* Key already exists. */
            tmp->data = item;
            delete newnode; /* dont need it */
            return;
        }
        else if (tmp->data > item)
        {
            if (!(tmp->left))
            {/* If the key is less than tmp */
                tmp->left = newnode;
                order++;
                return;
            }
            else
            {/* continue searching for insertion pt. */
                tmp = tmp->left;
            }
        }
        else
        {
            if (!(tmp->right))
            {/* If the key is greater than tmp */
                tmp->right = newnode;
                order++;
                return;
            }
            else
            {/* continue searching for insertion point*/
                tmp = tmp->right;
            }
        }
    }
}

template<typename T>
bool Bstree<T>::inTree(T item) const
{
    Node* tmp;
    if (!root)
        return false;
    /*find where it is */
    tmp = root;
    while (true)
    {
        if (tmp->data == item)
            return true;
        else if (tmp->data > item)
        {
            if (!(tmp->left))
                return false;
            else
            {/* continue searching */
                tmp = tmp->left;
            }
        }
        else
        {
            if (!(tmp->right))
                return false;
            else
                /* continue searching for insertion pt. */
                tmp = tmp->right;
        }
    }
}

template<typename T>
bool Bstree<T>::remove(const T& item)
{
    /* find item in tree */
    Node* nodeptr = search(item);
    /* if it exists in tree remove, update order, return true. otherwise return false */
    if (nodeptr)
    {
        remove(nodeptr);
        order--;
        return true;
    }
    return false;
}

template<typename T>
const T& Bstree<T>::retrieve(const T& key) const
{
    Node* nodeptr;
    if (!root)
        throw BstreeException("Exception:tree empty on retrieve().");
    nodeptr = search(key);
    if (!nodeptr)
        throw BstreeException("Exception: non-existent key on retrieve().");
    return nodeptr->data;
}

template<typename T>
void Bstree<T>::inorderTraverse(FuncType apply) const
{
    inorderTraverse(root, apply);
}

template<typename T>
long Bstree<T>::size() const
{
    return order;
}


template <typename T>
void Bstree<T>::recCopy(Node*& dest, Node* src)
{
    if (src)
    {
        dest = new Node(src->data);
        recCopy(dest->left, src->left);
        recCopy(dest->right, src->right);
    }
}

template<typename T>
void Bstree<T>::recDestroy(Node* root)
{
    if (root)
    {
        if (root->left) recDestroy(root->left);
        if (root->right) recDestroy(root->right);
        delete root;
    }
}

template<typename T>
typename Bstree<T>::Node* Bstree<T>::findParent(Node* node) const          
{
    Node* tmp = root;
    if (tmp == node)
        return nullptr;
    while (true)                                 
    {
        //assert(tmp->data != node->data);
        if (!tmp)
            return nullptr;
        if (tmp->data > node->data)
        {
            //assert(tmp->left);
            if (tmp->left == node)
                return tmp;
            else
                tmp = tmp->left;
        }
        else
        {
            //assert(tmp->right);
            if (tmp->right == node)
                return tmp;
            else
                tmp = tmp->right;
        }
    }
}

template<typename T>
void Bstree<T>::inorderTraverse(Node* node, FuncType apply) const
{
    if (node)
    {
        inorderTraverse(node->left, apply);
        apply(node->data);
        inorderTraverse(node->right, apply);
    }
}

template<typename T>
typename Bstree<T>::Node* Bstree<T>::search(const T& item) const    
{
    Node* tmp = root;
    while (tmp)
    {
        if (tmp->data == item)
            return tmp;
        else if (tmp->data > item)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return tmp;
}


template<typename T>
bool Bstree<T>::remove(Node* node)
{
    T data;
    Node* replacement;
    Node* parent = findParent(node);
    if (!parent)
        return false;
    if (node->left && node->right)
    {
        replacement = node->right;
        while (replacement->left)
            replacement = replacement->left;
        data = replacement->data;
        remove(replacement);
        node->data = data;
    }
    else
    {
        if (!(node->left) && !(node->right))
            replacement = nullptr;
        else if (node->left == nullptr)
            replacement = node->right;
        else
            replacement = node->left;
        if (!parent)
            root = replacement;
        else if (parent->left == node)
            parent->left = replacement;
        else
            parent->right = replacement;
        delete node;
    }
    return true;
}

/****** IMPLEMENT AUGMENTED PRIVATE Bstree FUNCTIONS BELOW ******/

    /*** BEGIN: AUGMENTED PRIVATE FUNCTIONS ***/

template<typename T>                                                                                
void Bstree<T>::preorderTraverse(Node* node, FuncType apply) const
{
    if (node)
    {
        apply(node->data);
        preorderTraverse(node->left, apply);
        preorderTraverse(node->right, apply);
    }
    else
    {
        return;
    }
}

template<typename T>                                                                                
void Bstree<T>::postorderTraverse(Node* node, FuncType apply) const
{
    if (node)
    {
        postorderTraverse(node->left, apply);
        postorderTraverse(node->right, apply);
        apply(node->data);
    }
    else
    {
        return;
    }
}

template<typename T>                                                                                
long Bstree<T>::height(const Node* node) const
{
    if (!node)
    {
        return -1;
    }
    else
    {
        return (1 + max(height(node->left), height(node->right)));
    }
}

/*  ---- OLD AND INCORRECT. ----
*  The bug: for the else statement, the case would be if (!lft && rgt), which is silly because 
*  the function will only be called in this case, but it should be called if both left and right
*  are not nullptr. Implementation is corrected below, left this for reference.
* 
template<typename T>                                                                                
bool Bstree<T>::isomorphic(const Node* lft, const Node* rgt) const
{
    if (lft && rgt)
    {
        return true;
    }
    else if (!lft && !rgt)
    {
        return false;
    }
    else if (lft && !rgt)
    {
        return false;
    }
    else
    {
        return (isomorphic((lft->left), (rgt->left)) && isomorphic((lft->right), (rgt->right)));
    }
}
*/

template<typename T>
bool Bstree<T>::isomorphic(const Node* lft, const Node* rgt) const
{
    if (!lft && !rgt) 
    {
        return true;
    }
    else if (!lft || !rgt) 
    {
        return false;
    }
    else 
    {
        return isomorphic(lft->left, rgt->left) &&
            isomorphic(lft->right, rgt->right);
    }
}

template<typename T>                                                                                
void Bstree<T>::descendants(vector<T>& desc, const Node* node) const
{
    Node* cur = search(node->data);

    if (!node)
    {
        return;
    }
    
    if (!cur->left)
    {
        if (cur->right)
        {
            desc.push_back(cur->data);
            cur = cur->right;
        }
        else
        {
            return;
        }
    }

    if (!cur->right)
    {
        if (cur->left)
        {
            desc.push_back(cur->data);
            cur = cur->left;
        }
        else
        {
            return;
        }
    }

    if (cur->right && cur->left)
    {
        descendants(desc, cur->left);
        descendants(desc, cur->right);
    }
}

template<typename T>                                                                                
void Bstree<T>::bias(bool& hlb, bool& hrb, Node* cur) const
{
    if (!cur)
    {
        return;
    }
    
    int leftH = height(cur->left);
    int rightH = height(cur->right);

    if (leftH < rightH)
    {
        hrb = true;
    }

    if (leftH > rightH)
    {
        hlb = true;
    }

    if (cur->left)
    {
        if (cur->right)
        {
            bias(hlb, hrb, cur->left);
            bias(hlb, hrb, cur->right);
        }
        else
        {
            bias(hlb, hrb, cur->left);
        }
    }
    else if (cur->right)
    {
        bias(hlb, hrb, cur->right);
    }
    else
    {
        return;
    }
}

/*** END: AUGMENTED PRIVATE FUNCTIONS ***/





/****** IMPLEMENT AUGMENTED PUBLIC Bstree FUNCTIONS BELOW ******/
  /**** BEGIN: AUGMENTED PUBLIC FUNCTIONS ***/

template<typename T>                                                                                
void Bstree<T>::preorderTraverse(FuncType apply) const
{
    preorderTraverse(root, apply);
}

template<typename T>                                                                                
void Bstree<T>::postorderTraverse(FuncType apply) const
{
    postorderTraverse(root, apply);
}

template<typename T>                                                                                
long Bstree<T>::height() const
{
    return height(root);
}

template<typename T>                                                                                
vector<T> Bstree<T>::ancestors(T entry) const
{
    
    Node* cur = search(entry);
    Node* parent = findParent(cur);
    vector<T> anc;

    if (!cur)
    {
        throw BstreeException("Ancestors could not be found, element does not exist in tree");
    }

    while (parent)
    {
        anc.push_back(parent->data);
        cur = parent;
        parent = findParent(cur);
    }
    return anc;
}

template<typename T>                                                                                
vector<T> Bstree<T>::descendants(T entry) const
{
    vector<T> desc;
    descendants(desc, search(entry));
    return desc;
}

template<typename T>
bool Bstree<T>::isomorphic() const
{
    if (!root)
    {
        return true;
    }
    return isomorphic(root->left, root->right);
}

template<typename T>                                                                                
const T* Bstree<T>::getParent(T entry) const
{
    if (!search(entry))
    {
        throw BstreeException("Entry does not exist in tree, cannot use getParent");
    }

    else if (!findParent(search(entry)))
    {
        return nullptr;
    }

    else
    {
        Node* parent = findParent(search(entry));
        return &(parent->data);
    }
}


template<typename T>
const T* Bstree<T>::getSibling(T entry) const
{
    Node* cur = search(entry);
    Node* parent = findParent(cur);
    T* result = nullptr;

    if (!cur)
    {
        throw BstreeException("Cannot find sibling: element does not exist in this tree");
    }
    
    if (!parent)
    {
        result = nullptr;  //entry is root
    }
    
    else if (parent->left == cur)
    {
        if (parent->right)
        {
            result = &(parent->right->data);
        }
        else
        {
            result = nullptr;
        }
    }
    
    else if (parent->right == cur)
    {
        if (parent->left)
        {
            result = &(parent->left->data);
        }
        else
        {
            result = nullptr;
        }
    }
    return result;
}


template<typename T>
const T* Bstree<T>::leftChild(T entry) const
{
    Node* node = search(entry);
    if (!search(entry))
    {
        throw BstreeException("Entry does not exist in tree");
    }
    else if (!node->left)
    {
        return nullptr;
    }
    else
    {
        return &(node->left->data);
    }
}


template<typename T>
const T* Bstree<T>::rightChild(T entry) const
{
    Node* node = search(entry);
    if (!search(entry))
    {
        throw BstreeException("Entry does not exist in tree");
    }
    else if (!node->right)
    {
        return nullptr;
    }
    else
    {
        return &(node->right->data);
    }
}



template<typename T>                                 
bool Bstree<T>::isFibonacci() const
{
    bool leftcheck = false;
    bool rightcheck = false;
    bias(leftcheck, rightcheck, root);

    

    if (size() <= 1)
    {
        return true;
    }

    if (leftcheck && rightcheck)
    {
        return false;
    }

    int prev = 0;
    int fib = 1;
    int next = 1;
    int final = size() + 1;
    int h = height(root);
    int i = 3;

    for (i ; fib < final; i++)
    {
        next = prev + fib;
        prev = fib;
        fib = next;
    }

    if ((fib == final) && (h == (i - 2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**** END: AUGMENTED PUBLIC FUNCTIONS ***/



