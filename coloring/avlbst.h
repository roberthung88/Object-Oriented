#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
    int size();
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    int sizehelper(AVLNode<Key, Value>* root);
    void rotateRight(AVLNode<Key,Value>* node);
    void rotateLeft(AVLNode<Key,Value>* node);
    AVLNode<Key, Value>* insertHelper(const std::pair<const Key, Value> &keyValuePair);
    void insertFix(AVLNode<Key,Value>* g, AVLNode<Key,Value>* p);
    void removeFix(AVLNode<Key,Value>* n, char diff);
    AVLNode<Key, Value>* removeHelper(AVLNode<Key, Value>* found, char &diff);
};

template<class Key, class Value>
int AVLTree<Key, Value>::sizehelper(AVLNode<Key, Value>* root)
{
    if(root == NULL){
        return 0;
    }else{
        return(sizehelper(root->getLeft()) + 1 + sizehelper(root->getRight()));
    }
}

template<class Key, class Value>
int AVLTree<Key, Value>::size(){
    return sizehelper(static_cast<AVLNode<Key,Value>*>(this->root_));
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node){
    AVLNode<Key, Value> *top = node->getLeft();
    node->setLeft(top->getRight());
    if(top->getRight() != NULL){
        top->getRight()->setParent(node);
    }
    if(node->getParent() == NULL)
    {
        BinarySearchTree<Key,Value>::root_ = top;
        top->setParent(NULL);
    }else if(node->getParent()->getLeft() == node){
        top->setParent(node->getParent());
        node->getParent()->setLeft(top);
    }else{
        top->setParent(node->getParent());
        node->getParent()->setRight(top);
    }
    top->setRight(node);
    node->setParent(top);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node){
    AVLNode<Key, Value> *top = node->getRight();
    node->setRight(top->getLeft());
    if(top->getLeft() != NULL){
        top->getLeft()->setParent(node);
    }
    if(node->getParent() == NULL)
    {
        BinarySearchTree<Key,Value>::root_ = top;
        top->setParent(NULL);
    }else if(node->getParent()->getLeft() == node){
        top->setParent(node->getParent());
        node->getParent()->setLeft(top);
    }else{
        top->setParent(node->getParent());
        node->getParent()->setRight(top);
    }
    top->setLeft(node);
    node->setParent(top);

}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insertHelper(const std::pair<const Key, Value> &keyValuePair)
{
    AVLNode<Key, Value>* curr_ = static_cast<AVLNode<Key,Value>*>(this->root_);
    
    
    while(curr_ != NULL){
        if(keyValuePair.first > curr_->getKey()){
            if(curr_->getRight() == NULL){
                AVLNode<Key, Value>* toInsert = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, curr_);
                toInsert->setBalance(0);
                curr_->setRight(toInsert);
                return toInsert;
                break;
            }else{
                curr_ = curr_->getRight();
            }
        }else if(keyValuePair.first < curr_->getKey()){
            if(curr_->getLeft() == NULL){
                AVLNode<Key, Value>* toInsert = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, curr_);
                toInsert->setBalance(0);
                curr_->setLeft(toInsert);
                return toInsert;
                break;
            }else{
                curr_ = curr_->getLeft();
            }
        }else{
            // equal
            curr_->setValue(keyValuePair.second);
            return curr_;
            break;
        }
    }
    if(this->root_ == NULL){
        AVLNode<Key, Value>* toInsert = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        this->root_ = toInsert;
        toInsert->setBalance(0);
        return toInsert;
    }
    return NULL;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    if(p == NULL){
        return;
    }
    AVLNode<Key,Value>* g = p->getParent();
    if(g == NULL){
        return;
    }
    //test whether p is left or right child of g
    if(g->getRight() == p){
        //right child
        g->updateBalance(1);
        // case 1
        if(g->getBalance() == 0){
            return;
        }else if(g->getBalance() == 1){
            //case 2
            insertFix(g, p);
        }else if(g->getBalance() == 2){
            //case 3
            if(p->getRight() == n){
                //zig zig
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }else if(p->getLeft() == n){
                //zig zag
                rotateRight(p);
                rotateLeft(g);
                if(n->getBalance() == 1){
                    // case 3a
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }else if(n->getBalance() == 0){
                    // case 3b
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }else if(n->getBalance() == -1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }else if(g->getLeft() == p){
        //left child
        g->updateBalance(-1);
        // case 1
        if(g->getBalance() == 0){
            return;
        }else if(g->getBalance() == -1){
            //case 2
            insertFix(g, p);
        }else if(g->getBalance() == -2){
            //case 3
            if(p->getLeft() == n){
                //zig zig
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }else if(p->getRight() == n){
                //zig zag
                rotateLeft(p);
                rotateRight(g);
                if(n->getBalance() == -1){
                    // case 3a
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }else if(n->getBalance() == 0){
                    // case 3b
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }else if(n->getBalance() == 1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    if(this->root_ == NULL){
        //empty tree
        AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        temp->setBalance(0);
        this->root_ = temp;
    }else{
        //inserts and set balance to 0. This also returns the inserted node
        AVLNode<Key, Value>* n = insertHelper(new_item);
        AVLNode<Key, Value>* parent = n->getParent();
        if(parent != NULL){
            if(parent->getBalance() == -1){
                parent->setBalance(0);
            }else if(parent->getBalance() == 1){
                parent->setBalance(0);
            }else if(parent->getBalance() == 0){
                if(parent->getLeft() == n){
                    parent->updateBalance(-1);
                }else if(parent->getRight() == n){
                    parent->updateBalance(1);
                }
                insertFix(parent, n);
            }
        }
        
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, char diff){
    if(n == NULL){
        return;
    }
    if(diff == 5){
        return;
    }
    AVLNode<Key, Value>* p = n->getParent();
    char ndiff = 0;
    if(p != NULL){
        if(p->getLeft() == n){
            ndiff = 1;
        }else if(p->getRight() == n){
            ndiff = -1;
        }
    }
    
    if(diff == -1){
        //case 1
        if(n->getBalance() + diff == -2){
            AVLNode<Key, Value>* c = n->getLeft();
            //case 1a
            if(c->getBalance() == -1){
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
//                if(ndiff == 0){
//                    p = n->getParent();
//                    if(p != NULL){
//                        if(p->getLeft() == n){
//                            ndiff = 1;
//                        }else if(p->getRight() == n){
//                            ndiff = -1;
//                        }
//                    }
//
//                }
                removeFix(p, ndiff);
            }else if(c->getBalance() == 0){
                //case 1b
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
            }else if(c->getBalance() == 1){
                //case 1c
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if(g->getBalance() == 1){
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }else if(g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }else if(g->getBalance() == -1){
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
//                if(ndiff == 0){
//                    p = n->getParent();
//                    if(p != NULL){
//                        if(p->getLeft() == n){
//                            ndiff = 1;
//                        }else if(p->getRight() == n){
//                            ndiff = -1;
//                        }
//                    }
//
//                }
                removeFix(p, ndiff);
            }
        }else if(n->getBalance() + diff == -1){
            n->setBalance(-1);
        }else if(n->getBalance() + diff == 0){
            n->setBalance(0);
//            if(ndiff == 0){
//                p = n->getParent();
//                if(p != NULL){
//                    if(p->getLeft() == n){
//                        ndiff = 1;
//                    }else if(p->getRight() == n){
//                        ndiff = -1;
//                    }
//                }
//
//            }
            removeFix(p, ndiff);
        }
    }else if(diff == 1){
        //case 1
        if(n->getBalance() + diff == 2){
            AVLNode<Key, Value>* c = n->getRight();
            //case 1a
            if(c->getBalance() == 1){
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
//                if(ndiff == 0){
//                    p = n->getParent();
//                    if(p != NULL){
//                        if(p->getLeft() == n){
//                            ndiff = 1;
//                        }else if(p->getRight() == n){
//                            ndiff = -1;
//                        }
//                    }
//
//                }
                removeFix(p, ndiff);
            }else if(c->getBalance() == 0){
                //case 1b
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
            }else if(c->getBalance()== -1){
                //case 1c
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if(g->getBalance() == -1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }else if(g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }else if(g->getBalance() == 1){
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
//                if(ndiff == 0){
//                    p = n->getParent();
//                    if(p != NULL){
//                        if(p->getLeft() == n){
//                            ndiff = 1;
//                        }else if(p->getRight() == n){
//                            ndiff = -1;
//                        }
//                    }
//
//                }
                removeFix(p, ndiff);
            }
        }else if(n->getBalance() + diff == 1){
            n->setBalance(1);
        }else if(n->getBalance() + diff == 0){
            n->setBalance(0);
            if(ndiff == 0){
                p = n->getParent();
//                if(p != NULL){
//                    if(p->getLeft() == n){
//                        ndiff = 1;
//                    }else if(p->getRight() == n){
//                        ndiff = -1;
//                    }
//                }
                
            }
            removeFix(p, ndiff);
        }
    }
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>:: removeHelper(AVLNode<Key, Value>* found, char &diff){
    if(found != NULL){
        if(found->getLeft() != NULL && found->getRight() != NULL){
            //has both children
            AVLNode<Key, Value> *pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(found));
            nodeSwap(pred, found);
            return removeHelper(found, diff);
        }else if(found->getLeft() != NULL){
            //only has left child
            AVLNode<Key, Value> *left = found->getLeft();
            if(found != this->root_){
                AVLNode<Key, Value> *par = found->getParent();
                if(par->getLeft() == found){
                    diff = 1;
                }else if(par->getRight() == found){
                    diff = -1;
                }

                if(found->getParent()->getLeft() == found){
                    found->getParent()->setLeft(left);
                }else if(found->getParent()->getRight() == found){
                    found->getParent()->setRight(left);
                }
                left->setParent(found->getParent());
                delete found;
                return par;
            }else{
                this->root_ = left;
                this->root_->setParent(NULL);
                delete found;
                diff = 5;
                left->setBalance(0);
                return static_cast<AVLNode<Key, Value>*>(this->root_);
            }
            
        }else if(found->getRight() != NULL){
            //only has right child
            AVLNode<Key, Value> *right = found->getRight();
            if(found != this->root_){
                AVLNode<Key, Value> *par = found->getParent();
                if(par->getLeft() == found){
                    diff = 1;
                }else if(par->getRight() == found){
                    diff = -1;
                }
                if(found->getParent()->getLeft() == found){
                    found->getParent()->setLeft(right);
                }else if(found->getParent()->getRight() == found){
                    found->getParent()->setRight(right);
                }
               
                right->setParent(found->getParent());
                delete found;
                return par;
            }else{
                this->root_ = right;
                this->root_->setParent(NULL);
                delete found;
                diff = 5;
                right->setBalance(0);
                return static_cast<AVLNode<Key, Value>*>(this->root_);;
            }
        }else if(found->getLeft() == NULL && found->getRight() == NULL){
            // no children
            if(found == this->root_){
                delete found;
                this->root_ = NULL;
                diff = 0;
                return NULL;
            }else{
                AVLNode<Key, Value> *par = found->getParent();
                if(par->getLeft() == found){
                    diff = 1;
                }else if(par->getRight() == found){
                    diff = -1;
                }
                if(found->getParent()->getLeft() == found){
                    found->getParent()->setLeft(NULL);
                }else if(found->getParent()->getRight() == found){
                    found->getParent()->setRight(NULL);
                }
                delete found;
                return par;
            }
        }
    }
    return NULL;
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value>* n = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if(this->internalFind(key) == NULL){
        return;
    }

    AVLNode<Key, Value>* p;
    char diff = 0;
   
    AVLNode<Key, Value> *ptemp = removeHelper(n, diff);
    p = ptemp;
    if(p != NULL){
        removeFix(p, diff);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
