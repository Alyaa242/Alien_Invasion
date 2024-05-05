//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */
#pragma once
#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"
#include  <iostream>
using namespace std;
//Unless spesificed by the stack user, the default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{

	//count is needed 

	enum { MAX_SIZE = 100 };
private:
	T items[MAX_SIZE];		// Array of stack items
	int top;                   // Index to top of stack
	int count;			// Count of items in the stack

public:

	ArrayStack()
	{
		top = -1;
		count = 0;
	}  // end default constructor

	bool isEmpty() const
	{
		
		
		return top == -1;	
	}  

	bool push(const T& newEntry)
	{
		if( top == MAX_SIZE-1 ) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;   
		count++;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		top--;
		count--;
		return true;
	}  // end pop
	
	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		return true;
	}  // end peek

	bool print() const 
	{
		if (isEmpty()) return false;
		cout << "[";
		for (int i{};i<top;i++)
		{
			cout << items[i] << ", ";
		}
		cout << items[top];
		cout << "]";
		return true;
	}

	int getCount() const {
		return count;
	}
}; // end ArrayStack

#endif
