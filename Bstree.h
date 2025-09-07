/**
 * The specification for an extensible parametric binary search tree.
 * @author Duncan, Preston Gautreaux
 * <pre>
 * File: Bstree.h
 * Date: 9999-99-99
 * Course: csc 1254 Section 1
 * Instructor: Dr. Duncan
 * </pre>
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

#include "BstreeException.h"

#ifndef BSTREE_H
#define BSTREE_H

using namespace std;

/**
 * A parametric extensible binary search tree class
 * @param <T> the binary search tree data type
 */
template <typename T> class Bstree
{
private:
    /**
     * forward declaration of a function pointer of type (const T&) -> void
     */
    typedef void (*FuncType)(const T& item);
    /**
     * Constructs an empty binary search tree;
     */
     /**
      * forward declaration of the Node class
      */
    class Node;
    /**
     * the number of nodes in this tree
     */
    long order;
    /**
     * A pointer to the root node of this tree
     */
    Node* root;

    /**
     * An auxiliary recursive function for the copy constructor
     * @param dest the root of a corresponding subtree of the destination tree
     * @param src the root of a corresponding subtree of the source tree
     */
    void recCopy(Node*& dest, Node* src);

    /**
     * An auxiliary recursive function for the destructor.
     * @param subtreRoot a pointer to the root of a subtree of this tree
     */
    void recDestroy(Node* subtreeRoot);
    /**
     * Give a pointer to the parent node of the specified Node
     * @param node the node whose parent node is to be found
     * @return the pointer to the parent node of the specified Node
     */
    Node* findParent(Node* node) const;
    /**
     * Traverses this tree in inorder
     * @param node a node of this tree
     * @param apply a pointer to a function of type (const T&) -> void
     * that is applied to the data field in the specified node
     */
    void inorderTraverse(Node* node, FuncType apply) const;
    /**
     * Removes the specified node from the tree
     * @param node a pointer to the node to be removed
     * @return true if the node is removed; otherwise false
     */
    bool remove(Node* node);
    /**
     * searches for the specified item in this tree
     * @param item the search key
     * @return a pointer to the node containing the item if it is found;
     * otherwise, nullptr
     */
    Node* search(const T& item) const;

    /*** BEGIN: AUGMENTED PRIVATE FUNCTIONS ***/

    /**
     * Traverses this tree in preorder
     * @param node a node of this tree
     * @param apply a pointer to a function of type (const T&) -> void
     * that is applied to the data field in the specified node
     */
    void preorderTraverse(Node* node, FuncType apply) const;

    /**
     * Traverses this tree in postorder
     * @param node a node of this tree
     * @param apply a pointer to a function of type (const T&) -> void
     * that is applied to the data field in the specified node
     */
    void postorderTraverse(Node* node, FuncType apply) const;

    /**
     * Recursively computes the height of the subtree rooted at the specified Node
     * @param node the root of a subtree
     * @return the height of the subtree rooted at the specified Node
     */
    long height(const Node* node) const;

    /**
     * Recursively determines whether the subtrees rooted at the specified nodes
     * are isomorphic; that is, the subtrees have the same shape
     * @param lft the root of the left subtree
     * @param rgt the root of the right subtree
     * @return true if the subtrees are isomorphic; otherwise, false
     */
    bool isomorphic(const Node* lft, const Node* rgt) const;

    /**
     * Recursively generates a vector of entries of descendant nodes of
     * the specied  node
     * @param desc a vector of entries in the subtree rooted at the
     * specified node, in pre-order.
     * @param node the root of a subtree
     */
    void descendants(vector<T>& desc, const Node* node) const;

    /**
     * Recursively determines whether the subtree rooted at the specified
     * node is left-bias/right-bias or has an ancestor that is
     * left-bias/right-bias
     * @param hlb true when the tree contains a left-half node or has an
     * ancestor that is a left-half node.
     * @param hrb true when the tree contains a right-half node or has an
     * ancestor that is a right-half node.
     * @param node the root of a subtree
     */
    void bias(bool& hlb, bool& hrb, Node* cur) const;

    /*** END: AUGMENTED PRIVATE FUNCTIONS ***/

public:
    /**
     * Constructs an empty binary search tree;
     */
    Bstree();

    /**
     * Copy constructor
     * @param other the tree to copy
     */
    Bstree(const Bstree<T>& other);

    /**
     * Move constructor
     * @param other the tree to move
     */
    Bstree(Bstree<T>&& other);

    /**
     * Returns the binary search tree memory to the system
     */
    virtual ~Bstree();

    /**
     * copy assignment operator
     * @param other the src tree
     */
    Bstree<T>& operator=(const Bstree<T>& other);

    /**
     * Determines whether the binary search tree is empty.
     * @return true if the tree is empty; otherwise, false
     */
    bool empty() const;

    /**
     * Inserts an item into the tree.
     * @param item the value to be inserted.
     */
    void insert(T item);

    /**
     * Determines whether an item is in the tree.
     * @param item item with a specified search key.
     * @return true on success; false on failure.
     */
    bool inTree(T item) const;

    /**
     * Deletes an item from the tree.
     * @param item item with a specified search key.
     * @return true on success; false on failure.
     */
    bool remove(const T& item);

    /**
     * Returns the item in the tree with the specified
     * key. If the item does not exists, an exception occurs.
     * @param key the key to the item to be retrieved.
     * @return it with the specified key.
     * @throws BstreeException if the item with the specified key is not
     * in the tree
     */
    const T& retrieve(const T& key) const;

    /**
     * Traverses a binary tree in inorder and applies the function visit
     * once for each node.
     * @param apply a pointer to a function of type (const T&) -> void
     */
    void inorderTraverse(FuncType apply) const;

    /**
     * Gives the number of node in this tree
     * @return the size of the tree; the number of nodes in this tree.
     */
    long size() const;

    /**** BEGIN: AUGMENTED PUBLIC FUNCTIONS ***/

   /**
    * Traverses a binary tree in preorder and applies the function visit
    * once for each node.
    * @param apply a pointer to a function of type (const T&) -> void
    */
    void preorderTraverse(FuncType apply) const;

    /**
     * Traverses a binary tree in postorder and applies the function visit
     * once for each node.
     * @param apply a pointer to a function of type (const T&) -> void
     */
    void postorderTraverse(FuncType apply) const;

    /**
     * Gives the height of this tree
     * @return the height of this tree
     */
    long height() const;

    /**
     * Generates a vector of ancestors of the specified entry
     * @param entry an entry in this tree
     * @return a vector of ancestors of the specified entry
     * @throw BstreeException when the specified entry is not in this tree
     */
    vector<T> ancestors(T entry) const;

    /**
     * A wrapper function for a function that generates a vector of
     * entries of nodes that are descendants of the node containing
     * the specified entry; this function obtains a pointer to the
     * node containing the entry and calls its corresponding auxiliary
     * function to generate a vector of entries that are descendants
     * of the subtree rooted at that node by traversing the subtree
     * rooted at the node in pre-order.
     * @param entry an entry in this tree
     * @return a vector of entries that are  descendants of the node
     * containing the specified entry
     * @throw BstreeException when the specified entry is not in this tree
     */
    vector<T> descendants(T entry) const;

    /**
     * Determines whether the left and right subtrees of the root
     * of this tree are isomorphic
     * @return true if the right and left subtrees of the root of
     * this tree are isomorphic; otherwise, false. The empty tree
     * and a tree of size 1 are vacously isomorphic
     */
    bool isomorphic() const;

    /**
     * Gives a pointer to the parent of the specified entry
     * @param entry an entry of this tree
     * @return a pointer to the parent data of the specified entry or
     * null if the specified entry is the root.
     * @throw BstreeException when this entry is not in this tree
     */
    const T* getParent(T entry) const;

    /**
     * Gives a pointer to the sibling of the specified entry
     * @param entry an entry of this tree
     * @return a pointer to the sibling's data of the specified entry or
     * null if the specified entry is the root or has no sibling
     * @throw BstreeException when this entry is not in this tree
     */
    const T* getSibling(T entry) const;

    /**
     * Gives a pointer to the left child of the specified entry
     * @param entry an entry in this tree
     * @return a pointer to the left child data of the specified entry
     * or null if the specified entry does not have a left child
     * @throw BstreeException when this entry is not in this tree
     */
    const T* leftChild(T entry) const;

    /**
     * Gives a pointer to the right child of the specified entry
     * @param entry an entry in this tree
     * @return a pointer to the right child data of the specified entry
     * or null if the specified entry does not have a right child
     * @throw BstreeException when this entry is not in this tree
     */
    const T* rightChild(T entry) const;

    /**
     * Determines whether this tree is a Fibonacci tree
     * @return true if this tree is a Fibonacci tree; otherwise, false
     */
    bool isFibonacci() const;

    /**** END: AUGMENTED PUBLIC FUNCTIONS ***/

};

/**
 * nested Node class definition
 * @param <T> the data type of the binary search tree
 * @param <U> the data type of the item in this node
 */
template <typename T>
class Bstree<T>::Node
{
private:
    /**
     * the data item in this Node
     */
    T data;
    /**
     * a pointer to the left child of this Node
     */
    Node* left;
    /**
     * a pointer to the right child of this Node
     */
    Node* right;
    /**
     * Granting friendship - access to private members of this class to the
     * Bstee<U> class
     */
    friend class Bstree<T>;
public:
    /**
     * Constructs a node with a given data value.
     * @param item the data to store in this node
     */
    Node(T item);

};
#endif //BSTREE_H
