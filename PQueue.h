//===========================================================
// Arjun Malhotra
// PQueue.h	
// This program implements a priority queue via the BST class.
//===========================================================

#include "BST.h"
using namespace std;

//===========================================================
#ifndef PQUEUE_H
#define PQUEUE_H

template <class T>
class PQueue
{
private:
    BST<T>      bst;
public:
                PQueue      ( void );
                PQueue      ( const PQueue<T> & );
               ~PQueue      ( void );
    PQueue<T>   operator=   ( const PQueue<T> & );
    void        enqueue     ( T item );
    T           dequeue     ( void );
    T           peek        ( void );
    int         length      ( void ) const;
    bool        isEmpty     ( void ) const;
    void        clear       ( void );
    string      to_string   ( void ) const;
    friend ostream & operator<< ( ostream &os, const PQueue<T> &pq )
    {
        os << pq.bst;
        return os;
    }
};

//-----------------------------------------------------------
// class methods below here
//-----------------------------------------------------------

//===========================================================
// Default Constructor
//===========================================================
template <class T> 
		PQueue<T>::PQueue      ( void )
{
}
//===========================================================
// Copy Constructor 
//===========================================================
template <class T> 
 		PQueue<T>::PQueue      ( const PQueue<T> &pq )
{
	bst = pq.bst;
}
//===========================================================
// Destructor 
//===========================================================
template <class T> 
 		PQueue<T>::~PQueue      ( void )
{
}
//===========================================================
// Assignment operator =  
//===========================================================
template <class T> 
PQueue<T> 	PQueue<T>::operator=   ( const PQueue<T> &pq )
{
	bst = pq.bst; 
	return *this; 
}
//===========================================================
// enqueue
//===========================================================
template <class T> 
void 	PQueue<T>::enqueue     ( T item )
{
	return bst.insert(bst.root, item); 
}
//===========================================================
// dequeue 
//===========================================================
template <class T> 
T			PQueue<T>::dequeue     ( void )
{
	if ( bst.isEmpty() )
	{
		cout << "Error: cannot dequeue from empty queue\n"; 
		exit(1); 
	}
	

	T ret = (bst.findBiggest(bst.root))->data;  // use find biggest and remove bst functions

	bst.remove(ret); 							// remove the biggest value out of the tree

	return ret;

	


}
//===========================================================
// peek
//===========================================================
template <class T> 
T				PQueue<T>::peek        ( void )
{
	if ( bst.isEmpty() )
	{
		cout << "Error: cannot peek from empty pqueue \n"; 
		exit(1); 
	}
	
	return (bst.findBiggest(bst.root)) -> data;
}
//===========================================================
// length
//===========================================================
template <class T> 
int         PQueue<T>::length      ( void ) const
{
	return bst.length( bst.root ); 
}
//===========================================================
// isEmpty
//===========================================================
template <class T> 
bool        PQueue<T>::isEmpty     ( void ) const
{
	return bst.isEmpty(); 
}
//===========================================================
// clear
//===========================================================
template <class T> 
void        PQueue<T>::clear       ( void )
{
	bst.clear(bst.root); 
}
//===========================================================
// to_string
//===========================================================
template <class T> 
string      PQueue<T>::to_string   ( void ) const
{
	return bst.to_string( bst.root );
}
//===========================================================
#endif
