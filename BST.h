//===================================================================
// Arjun Malhotra
// BST.h
// Definition and implementation a Binary Search Tree (bst) class.
//===================================================================

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
using namespace std;

//===================================================================
#ifndef BST_H
#define BST_H

template <class T>
struct Node
{
    T       data;
    Node *  left;
    Node *  right;
};

template <class T>
class BST
{
public:
    Node<T> * root;        // root pointer for binary search tree
                BST         ( void );
               ~BST         ( void );
                BST         ( const BST<T> & );
    BST<T>      operator=   ( const BST<T> & );
    Node<T>*    copy        ( Node<T> * );
    void        insert      ( Node<T> *&ptr, T item );
    void        remove      ( T item );
    Node<T> *   find        ( Node<T> *, T item ) const;
    Node<T> *   findParent  ( Node<T> *, T item ) const;
    Node<T> *   findBiggest ( Node<T> * ) const;
	Node<T> *   findSmallest( Node<T> * ) const;
    void        clear       ( Node<T> *& );
    int         length      ( Node<T> * ) const;
    bool        isEmpty     ( void ) const;
    string      to_string   ( Node<T> * ) const;
    friend ostream & operator<< ( ostream &os, const BST<T> &bst )
    {
        os << bst.to_string(bst.root);
        return os;
    }
    
};


//=============================================================================
// CONSTRUCTORS & DESTRUCTOR
//=============================================================================

//-----------------------------------------------------------------------------
// Default Constructor
// Creates a new empty binary search tree
//-----------------------------------------------------------------------------
template <class T>
					BST<T>::BST ( void )
{
			root = NULL;
}
//-----------------------------------------------------------------------------
// Copy Constructor
// Parameters: 
// 		Binary search tree bst: a bst to copy passed by reference
// Return values: 
//		Returns the new bst, which contains the content of bst
// Creates a new bst by copying the contents of another bst
//-----------------------------------------------------------------------------
template <class T>
					BST<T>::BST ( const BST<T> & bst)
{
		root = NULL;
		root = copy(bst.root);	
}
//-----------------------------------------------------------------------------
// Destructor 
// Free up memory. 
//-----------------------------------------------------------------------------
template <class T>
					BST<T>::~BST ( void )
{
			clear(root);
}
//-----------------------------------------------------------------------------

//=============================================================================
// OPERATORS & ACCESSORS/MODIFIERS
//=============================================================================

//-----------------------------------------------------------------------------
// operator=
//-----------------------------------------------------------------------------
template <class T>
BST<T>      		BST<T>::operator= ( const BST<T> &bst )
{
	clear(root);
	root = NULL;
	root = copy(bst.root);
	return *this;
}
//-----------------------------------------------------------------------------
// copy
// Parameters: 
// 		Binary search tree bst: a bst to copy passed by reference
// Return values: 
//		Returns the new bst, which contains the content of bst
// Copy a bst by copying the contents of another bst
//-----------------------------------------------------------------------------
template <class T>
Node<T>*        		BST<T>::copy ( Node<T> *ptr )
{
	if ( ptr == NULL )
		return NULL;
	else
	{
		Node<T> *t = new Node<T>;
		t->data = ptr->data;
		t->left = copy(ptr->left);
		t->right = copy(ptr->right);
		return t;
	}
}
//-----------------------------------------------------------------------------
// insert
// Inserting an item into a bst. 
// Parameters: 
// 		BST: a bst to insert item into
//			 an item to insert 
// Return values: 
//		bst with the new inserted item
//-----------------------------------------------------------------------------
template <class T>
void        		BST<T>::insert  ( Node<T> *&ptr, T item )
{
	if ( ptr == NULL )
	{
		ptr = new Node<T>;
		ptr->left = ptr->right = NULL;
		ptr->data = item;
	}
	else if ( ptr->data > item )
		insert ( ptr->left, item );
	else
		insert ( ptr->right, item );
}
//-----------------------------------------------------------------------------
// remove 
// Remove an item from the bst 
// Parameters: 
// 	 	BST: a bst to remove items from
//			 item given to find and take out of the bst
// Return values: 
//		bst with the item removed
//		if the item is not in bst, returns original bst and errors sign
//-----------------------------------------------------------------------------
template <class T>
void        		BST<T>::remove ( T item )
{
	Node<T>* qtr = find( root, item);
	if ( qtr == NULL )
	{
		cout << "Error: can't find the item." << endl;
		exit(1);
	}
	Node<T>* ptr = findParent( root, item);

	if ( ptr == NULL )
	{
		if ( qtr->left == NULL and qtr->right == NULL )
		{
			delete qtr;
			root = NULL;
		}
		else if ((qtr->left == NULL and qtr->right != NULL) or (qtr->left != NULL and qtr->right != NULL))
		{
			Node<T>* smallest = findSmallest (qtr->right);
			Node<T>* temp = new Node<T>;
			temp->data = smallest->data;
			remove(smallest->data);
			root->data = temp->data;
			delete temp;		
		
		}	
		else if (qtr->left != NULL and qtr->right == NULL )
		{
			Node<T>* biggest = findBiggest (qtr->left);
			Node<T>* temp = new Node<T>;
			temp->data = biggest->data;
			remove(biggest->data);
			root->data = temp->data;
			delete temp;	
		} 		
	}
	else
	{
		if ( qtr->left == NULL and qtr->right == NULL )
		{
			if (ptr->data > item)
				ptr->left = NULL;
			else
				ptr->right = NULL;
			delete qtr;
		}
		else if ((qtr->left == NULL and qtr->right != NULL) or (qtr->left != NULL and qtr->right != NULL))
		{
			Node<T>* smallest = findSmallest (qtr->right);
			Node<T>* temp = new Node<T>;
			temp->data = smallest->data;
			remove(smallest->data);
			if (ptr->data > item)
				ptr->left = temp;
			else
				ptr->right = temp;
			temp->left = qtr->left;
			temp->right = qtr->right;
			delete qtr;
		
		
		}	
		else if (qtr->left != NULL and qtr->right == NULL )
		{
			Node<T>* biggest = findBiggest (qtr->left);
			Node<T>* temp = new Node<T>;
			temp->data = biggest->data;
			remove(biggest->data);
			if (ptr->data > item)
				ptr->left = temp;
			else
				ptr->right = temp;
			temp->left = qtr->left;
			temp->right = qtr->right;
			delete qtr;
		
		
		} 
	}
		
}
//-----------------------------------------------------------------------------
// find 
// Find the location of an item inside a bst 
// Paramters:
//		BST in which we are searching for the item
//		item given to be found within the bst
// Return values:
//      The location of the item inside the bst
//-----------------------------------------------------------------------------
template <class T>
Node<T>*   		BST<T>::find ( Node<T> *ptr, T item ) const
{

	if ( ptr == NULL )
		return NULL;

	else 
	{
		if ( item == ptr->data )
			return ptr;
		else if ( item > ptr->data )
			return find(ptr->right, item);
		else 
			return find(ptr->left, item);
	}			
}
//-----------------------------------------------------------------------------
// findParent 
// Find the location of the parent of an item inside a bst 
// Paramters:
//		BST in which we are searching for the parent of an item
//		item given to be found within the bst
// Return values:
//      The location of the parent of an item inside the bst
//-----------------------------------------------------------------------------
template <class T>
Node<T> *   		BST<T>::findParent ( Node<T> *ptr, T item ) const
{
	if (ptr->data == item)
		return NULL; 
	else
	{	
		if ( item > ptr->data ) 
		{
			if ( ptr->right->data == item )
				return ptr; 
			else 
				return findParent(ptr->right,item);
		}
		else  
		{
			if ( ptr-> left->data == item) 
				return ptr; 
			else
				return findParent(ptr->left, item);
		}	
	}
}
//-----------------------------------------------------------------------------
// findBiggest 
// Find the location of the biggest item inside a bst 
// Paramters:
//		BST in which we are searching for the biggest item
//		item given to be found within the bst
// Return values:
//      The location of the biggest item inside the bst
//-----------------------------------------------------------------------------
template <class T>
Node<T> *    		BST<T>::findBiggest ( Node<T> *bst ) const
{	
	if ( root == NULL )
		return NULL;
	else if ( bst->right == NULL )
		return bst;
	else 
		return findBiggest(bst->right);
}

//-----------------------------------------------------------------------------
// findSmallest
// Find the location of the smallest item inside a bst 
// Paramters:
//		BST in which we are searching for the smallest item
//		item given to be found within the bst
// Return values:
//      The location of the smallest item inside the bst
//-------------------------------- ---------------------------------------------
template <class T>
Node<T> *   		BST<T>::findSmallest ( Node<T> *bst ) const
{	
	if ( root == NULL )
		return NULL;	
	else if ( bst->left == NULL )
		return bst;
	else
		return findSmallest(bst->left);
}

//-----------------------------------------------------------
// clear
// Clear the bst.
//-----------------------------------------------------------------------------
template <class T>
void        BST<T>::clear       ( Node<T> *&bst )
{
	if ( bst != NULL )
	{
		clear(bst->left);
		clear(bst->right);
		if (bst == root )
		{
			delete bst;
			root = NULL;
		}
		else
			delete bst;
	}
		
}
//-----------------------------------------------------------------------------
// length
// Returns the length of the bst.
//-----------------------------------------------------------------------------
template <class T>
int         		BST<T>::length  ( Node<T> * ptr ) const
{
	if ( ptr == NULL )
		return 0;
	else
		return 1 + length(ptr->left) + length(ptr->right);
}
//-----------------------------------------------------------------------------
// isEmpty 
// Returns whether or not the bst is empty.
//-----------------------------------------------------------------------------
template<class T>
bool        		BST<T>::isEmpty  ( void ) const
{
		return ( root == NULL );
}
//-----------------------------------------------------------------------------
// to_String 
// Prints out the items inside bst in pre-order style.
//-----------------------------------------------------------------------------
template<class T>
string  	BST<T>::to_string   ( Node<T> * node ) const
{
	stringstream ss;
	
	if ( node == NULL )
		ss << "";
	else
	{
		ss << node->data << " ";
		ss << to_string(node->left);
		ss << to_string(node->right);
	}
		
	string str = ss.str();
	return str;
}    
//-----------------------------------------------------------------------------
//=============================================================================


#endif
