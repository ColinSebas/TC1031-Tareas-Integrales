/*
 * hash.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 * 		Modified: Sebastián Colín
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~Quadratic();
	bool full() const;
	void put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	size = sze;

	keys = new Key[size];
	if (keys == 0) {
		cout << "Out of memory";
	}
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];
	if (values == 0) {
		cout << "Out of memory";
	}
	for (int i = 0; i < size; i++) {
		values[i] = 0;
	}
	func = f;
	count = 0;
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;

}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	i = start = func(k) % size;
	unsigned int j = 1;

	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + (j * j)) % size;
		j++;
	} while (start != i);
	return -1;
}

template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start;
	i = start = func(k) % size;
	unsigned int j = 1;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return;
	}

	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return;
		}
		i = (i + (j * j)) % size;
		j++;
	} while (start != i);
	return;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	long pos;

	pos = indexOf(k);
	return (pos != -1);
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	long pos; 

	pos = indexOf(k); 
	if (pos == -1) 
		cout << "No such element";
	
	return values[pos];
	
	
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
	count = 0;
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}
#endif /* QUADRATIC_H */
