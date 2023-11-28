/*
 * heap.h
 *
 *  Created on: 19/10/2023
 *      Author: Sebas Colín
 *
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <sstream>
#include <string> 

using namespace std;

template <class T> 
class Heap {

    private:

        T *data;
        unsigned int sizeVar;
        unsigned int count;
        unsigned int parent(unsigned int) const;
        unsigned int left(unsigned int) const;
        unsigned int right(unsigned int) const;
        void heapify(unsigned int);
        void swap(unsigned int, unsigned int);

    public: 

        // Constructor & Destructor     
        Heap(unsigned int);
	    ~Heap();

        // Other functions 
        std::string toString() const;
        bool full() const;
        void clear();

        // HW Member functions
        void push(unsigned int);
        void pop();
        T top();
        bool empty() const;
        unsigned int size() const;

};

template <class T>
Heap<T>::Heap(unsigned int sz) { 
    sizeVar = sz;
	data = new T[sizeVar];
	if (data == 0) {
		cout << "Out of memory";
	}
	count = 0;
}

template <class T> 
Heap<T>::~Heap() {
    clear();
}

template <class T> 
void Heap<T>::clear() {
    delete [] data;
    data = 0;
    sizeVar = 0;
    count = 0;
}

template <class T>
bool Heap<T>::full() const {
	return (count == sizeVar);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}


/*============== HOMEWORK FUNCTIONS ===================*/

template <class T>
void Heap<T>::push(unsigned int val)  {
	unsigned int pos;
	if (full()) {
		cout << "Overflowed heap";
	}

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T> 
void Heap<T>::pop() {
	if (empty()) {
		cout << "No such element";
	}
	T aux = data[0];

	data[0] = data[--count];
	heapify(0);
}

template <class T> 
T Heap<T>::top() {
    return data[0];
}

template <class T> 
bool Heap<T>::empty() const {
    return (count == 0);
}

template <class T> 
unsigned int Heap<T>::size() const {
    return count;
}

/*================= OTHER FUNCTIONS ==================*/

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif