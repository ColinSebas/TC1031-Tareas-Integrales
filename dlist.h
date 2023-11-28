/*
 * dlist.h
 *
 *  Created on: 25/09/23
 *      Author: Sebas Colin
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;


template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {

    private:

        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);
        DLink(const DLink<T>&);

        T	    value;
        DLink<T> *previous;
        DLink<T> *next;

        friend class DList<T>;
        friend class DListIterator<T>;

};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {

public:

	DList();
	DList(const DList<T>&);
	~DList();

	bool empty () const;
    std::string toString() const;
    void clear();
    void insertFirst(T);
	T removeFirst();

	// String management
	std::string toStringForward() const;
	std::string toStringBackward() const;

    // HW
    void insertion(T); T search(int) const;
    bool update (unsigned int, T); 
    T deleteAt (int);

private:

	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

	friend class DListIterator<T>;
};

template <class T>
DList<T>::DList() : head(NULL), tail(NULL), size(0) {}

template <class T> 
DList<T>::~DList() {
    clear();
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
    tail = 0;
	size = 0;
}

template <class T>
std::string DList<T>::toString() const {

	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();

}

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template <class T>
bool DList<T>::empty() const {
    return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::insertFirst(T val)  {
	DLink<T> *newNode;

	newNode = new DLink<T>(val);
	if (newNode == 0) {
		cout << "Out of memory";
	}
	newNode->next = head;
	head = newNode;
	size++;

}

template <class T>
void DList<T>::insertion(T val)  {
	DLink<T> *newLink;

	newLink = new DLink<T> (val);
	if (newLink == 0) {
		cout << "Out of Memory";
	}

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}

	size++;

}

template <class T>
T DList<T>::search(int val) const {
	DLink<T> *p;
	DLink<T> *q;

	int countFront = 0;
	//int countBack = size;
	p = head;
	q = tail;
	while (p != 0) {
		if (p->value == val) {
			return countFront;
		}
		countFront++;
		//countBack--;
		p = p->next;
		q = q->previous;
	}
	return -1;
}

template <class T>
bool DList<T>::update (unsigned int i, T val) {

    int pos;
    DLink<T> *p;

    if (i > size) {
        return false;
    }

    if (i <= (size / 2)) {
        p = head;
        pos = 0;
        while (pos != i) {
            p = p->next;
            pos++;
        }
        p->value = val;
        
    } else {
        p = tail;
        pos = size - 1;
        while (pos != i) {
            p = p->previous;
            pos--;
        }
        p->value = val;
    }
    return true;


}

template <class T>
T DList<T>::removeFirst()  {
	T val;
	DLink<T> *temp;

	if (empty()) {
		cout << "No such element";
	}

	temp = head;
	val = temp->value;

	if (head == tail) {
		head = NULL;
		tail = NULL;
	} else {
		head = temp->next;
		temp->next->previous = NULL;
	}

	delete temp;
	size --;

	return val;
}

template <class T>
T DList<T>::deleteAt(int i) {
	DLink<T> *temp;

	T val; int pos;
	
	if (i == 0) {
		return removeFirst();
	}

	if (i <= (size / 2)) {
        temp = head;
        pos = 0;
        while (pos != i) {
            temp = temp->next;
            pos++;
        }
    } else {
        temp = tail;
        pos = size - 1;
        while (pos != i) {
            temp = temp->previous;
            pos--;
        }
    }
	temp->next->previous = temp->previous;
	temp->previous->next = temp->next;
	
	delete temp;
	size--;

	return val;

}

#endif