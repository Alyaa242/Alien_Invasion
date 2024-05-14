#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "Node.h"

using namespace std;
template <typename T>
class Deque : public LinkedQueue <T>

{
    bool last;

public:
    Deque();
    bool isEmpty() const;
    bool addLast(const T& item);
    bool insert(const T& entry);    //Function that insert and handle whether to enqueue or addLast
    bool removeLast(T& oldValue);
    bool enqueue(const T& newEntry);
    bool dequeue(T& frntEntry);
    bool peek(T& frntEntry)  const;
    bool peekBack(T& backEntry) const;
};


template<typename T>
inline Deque<T>::Deque()
{
    last = false;
}

template <typename T>
bool Deque<T>::isEmpty() const
{

    return !LinkedQueue<T>::frontPtr;

}

template<typename T>
inline bool Deque<T>::addLast(const T& item)
{
    Node <T>* newNode = new Node <T>(item);
    if (isEmpty())
    {
        LinkedQueue<T>::frontPtr = newNode;
        LinkedQueue<T>::backPtr = LinkedQueue<T>::frontPtr;
    }

    else
    {
        (newNode)->setNext(LinkedQueue<T>::frontPtr);
        (LinkedQueue<T>::frontPtr)->setPrev(newNode);
        (LinkedQueue<T>::frontPtr) = newNode;

    }

    LinkedQueue<T>::counter++;
    LinkedQueue<T>::backPtr->setNext(nullptr);

    return true;
}

template<typename T>
inline bool Deque<T>::insert(const T& entry)
{
    //Check whether the last element was inserted from front or back
    if (!last) {
        enqueue(entry);
        last = true;
    }
    else {
        addLast(entry);
        last = false;
    }
    return true;
}

template <typename T>
bool Deque<T>::removeLast(T& oldValue)
{
    if (isEmpty())
    {
        return false;
    }

    Node <T>* ptr = LinkedQueue<T>::backPtr;
    if (!ptr)
        return false;

    oldValue = ptr->getItem();
    LinkedQueue<T>::backPtr = LinkedQueue<T>::backPtr->getPrev();
    Node <T>* prev = ptr->getPrev();
    LinkedQueue<T>::backPtr->setNext(nullptr);

    if (ptr == LinkedQueue<T>::frontPtr)
    {
        delete  LinkedQueue<T>::frontPtr;
        LinkedQueue<T>::frontPtr = nullptr;

    }
    else
    {
        delete ptr;
        ptr = nullptr;

    }

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
    if (LinkedQueue <T>::dequeue(frntEntry))
        return true;
    return false;
}

template<typename T>
inline bool Deque<T>::peek(T& frntEntry) const
{

    if (LinkedQueue <T>::peek(frntEntry))
        return true;
    return false;
}

template<typename T>
inline bool Deque<T>::peekBack(T& backEntry) const
{
    if (isEmpty())
        return false;

    backEntry = LinkedQueue <T>::backPtr->getItem();
    return true;
}
