/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <cmath>
#include "avltree.h"

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;

    t->height = max(h(t->left), h(t->right))+1;
    temp->height = max(h(temp->left), h(temp->right))+1; 
    t = temp;
 
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;

    t->height = max(h(t->left), h(t->right))+1;
    temp->height = max(h(temp->left),h(temp->right))+1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::updateHeights(Node*& t){
    t->height = max(h(t->left), h(t->right))+1;
    if (t->left)
    t->left->height = max(h(t->left->left),h(t->left->right))+1;
    if (t->right)
    t->right->height = max(h(t->right->left),h( t->right->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    updateHeights(subtree);

int balance = b(subtree);
int leftBalance = b(subtree->left);
int rightBalance=b(subtree->right);
		
if (balance <-1)
{ 
   if(leftBalance <0)
	rotateRight(subtree);
   else
	rotateLeftRight(subtree);
}
if (balance >1)
{
   if(rightBalance >0)
	rotateLeft(subtree);
   else
	rotateRightLeft(subtree);
}
 
    updateHeights(subtree);

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree==NULL)
  	subtree = new Node(key, value);
    else if (key < subtree->key)
	{
		insert(subtree->left, key, value);
		rebalance(subtree);
	}
	else if (key > subtree->key)
	{
		insert(subtree->right, key, value);
                 rebalance(subtree);
		
	}
				
	updateHeights(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
 
    if (key < subtree->key) {
        // your code here
	remove(subtree->left, key);
	rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
	remove(subtree->right, key);
	rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree=NULL;
	   
	   
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
	 Node* &temp = findiop(subtree->left) ;  
     
       swap(subtree,temp);
	remove (subtree->left,key);
		
        } else {
            /* one-child remove */
            // your code here   
          Node *&temp = subtree->left ? subtree->left : subtree->right;
           swap(subtree,temp);
	   temp=NULL;
        }
        // your code here
	
    }
}

template <class K, class V>
int AVLTree<K, V>::h(Node*& node){

    if (node == NULL)
        return -1;
    return node->height;
}
template <class K, class V>
int AVLTree<K, V>::b(Node* t)
{
    if (t == NULL)
        return 0;
    return h(t->right)-h(t->left);
}


template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::findiop(Node*& root)
{

    if( root==NULL || root->right==NULL) return root;
    
    return findiop(root->right);
   
}
