#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Array {

	T arr[1000];
	int count;		//Counter of elements
	
public:

	Array();
	void insert(T item);
	bool remove(int i, T& item);		//A function to get an element and remove it	
	bool atIndx(int i, T& item) const;	//A function to get an element without removing it
	void print() const;
	int getCount() const;
	bool isEmpty() const;

};

template<typename T>
inline Array<T>::Array()
{
	count = 0;
}

template<typename T>
inline void Array<T>::insert(T item)
{
	arr[count] = item;
	count++;
}

template<typename T>
inline bool Array<T>::remove(int i, T& item)
{
	if (i < count) {
		item = arr[i];
		arr[i] = arr[count - 1];	//Swap last element with the elemt we are removing
		count--;
		return true;
	}
	return false;
}

template<typename T>
inline bool Array<T>::atIndx(int i, T& item) const
{
	if (i < count) {
		item = arr[i];
		return true;
	}
	return false;
}

template<typename T>
inline void Array<T>::print() const
{
	if (count == 0)
		return;
	cout << '[';
	for (int i = 0; i < count - 1; i++) {
		cout << arr[i] << ", ";
	}
	cout << arr[count - 1];
	cout << ']';
}

template<typename T>
inline int Array<T>::getCount() const
{
	return count;
}

template<typename T>
inline bool Array<T>::isEmpty() const
{
	return !count;
}
