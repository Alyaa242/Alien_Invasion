#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "Node.h"

using namespace std;
template <typename T>
class Deque : public LinkedQueue <T> 

{
public: 
    Deque() = default;
    bool isEmpty();
    void addLast(T item);
    bool removeLast(T& item);
    bool enqueue(const T& newEntry);
    bool dequeue(T& frntEntry);
 
};


template <typename T>
bool Deque<T>::isEmpty()
{
    
    return !LinkedQueue<T>::frontPtr ;
    
}

template<typename T>
inline void Deque<T>::addLast(T item)
{
    Node <T>* newNode = new Node <T>(item);
    if (isEmpty())
    {
        LinkedQueue<T>::frontPtr = newNode;
        LinkedQueue<T>::backPtr = LinkedQueue<T>::frontPtr;
    } 
      
    else
    {
        (newNode)-> setNext(LinkedQueue<T>::frontPtr);
        (LinkedQueue<T>::frontPtr)= newNode ;

    }

    LinkedQueue<T>::counter++;
    LinkedQueue<T>::backPtr->setNext(nullptr);
}

template <typename T>
bool Deque<T>::removeLast(T& oldValue)
{
    if (isEmpty())
    {
        return false;
    }

    Node<T>* ptr = LinkedQueue<T>::backPtr;
    oldValue = ptr->getItem();
    Node<T>* prevPtr = ptr->getPrev();
    delete ptr;
    prevPtr->setNext(nullptr);
    LinkedQueue<T>::backPtr = prevPtr;

    /*Node <T>* ptr = LinkedQueue<T>::frontPtr;
    while (ptr->getNext()->getNext())
        ptr = ptr->getNext();

    oldValue = ptr->getNext()->getItem();

    Node <T>* oneBefore = ptr;

    oneBefore->setNext(nullptr);

    delete  LinkedQueue<T>::backPtr;
    LinkedQueue<T>::backPtr = oneBefore;*/

    LinkedQueue<T>::counter--;

    return true;
}

template<typename T>
inline bool Deque<T>::enqueue(const T& newEntry)
{
    LinkedQueue <T>::enqueue(newEntry);
    return true;
}

template<typename T>
inline bool Deque<T>::dequeue(T& frntEntry)
{
    if(LinkedQueue <T>::dequeue(frntEntry))
        return true;
    return false;
}

