#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Array {

private:

	T arr[100];
	int count;
	
public:

	Array();
	void insert(T item);
	bool remove(int i, T& item);
	void print() const;
	int getCount() const;

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
		arr[i] = arr[count - 1];
		count--;
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
		cout << *arr[i] << ", ";
	}
	cout << *arr[count - 1];
	cout << ']';
}

template<typename T>
inline int Array<T>::getCount() const
{
	return count;
}