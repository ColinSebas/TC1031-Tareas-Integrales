/*
 * sorts.h
 *
 * 01/09/23
 *      by: Sebastián Colín
*/

#include <vector>

#ifndef SORTS_H_
#define SORTS_H_

template <class T>

class Sorts {

    private: 

        void swap(std::vector<T>&, int, int);
        void copyArray(std::vector<T> &A, std::vector<T> &B, int, int);
        void mergeArray(std::vector<T> &A, std::vector<T> &B, int, int, int);
        void mergeSplit(std::vector<T> &A, std::vector<T> &B,int, int);
    public: 

        void ordenaSeleccion(std::vector<T>&);
        void ordenaBurbuja(std::vector<T>&);
        void ordenaMerge(std::vector<T>&);
        int busqSecuencial(const std::vector<T>&, int val);
        int busqBinaria(const std::vector<T>&, int val);

};

template <class  T>
void Sorts<T>::swap(std::vector<T> &vec, int i, int j) {

    T aux = vec[i];
    vec[i] = vec[j];
    vec[j] = aux;

}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) { 
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {

    int i = low; int j = mid + 1; int k = low;

    while (i <= mid  && j <= high) {
        if (A[i] < A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if (i > mid) {
        for (; j <= high; j++) {
            B[k++] = A[j];
        }
    } else {
        for (; i <= mid; i++) {
            B[k++] = A[i];
        }
    }

}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {

    int mid;

    if ((high - low) < 1) {
        return;
    }
    
    mid = (low + high) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);

}


template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &prueba) {
    
    //std::vector<T> v(prueba);
	
	int pos;

	for (int i = 0; i < prueba.size() - 1; i++) {
		pos = i;
		for (int j = i; j < prueba.size(); j++) {
			if (prueba[pos] > prueba[j]) {
				pos = j;
			}
		}
		swap(prueba, pos, i);
		
	}

	//return v;
}

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &prueba) {
    
    //std::vector<T> v(prueba);

    for (int i = prueba.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (prueba[j] > prueba[j + 1]) {
				swap(prueba, j, j + 1);
			}
		}
	}

	//return v;


}

// Espacio Para Merge

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &prueba) {

    //std::vector<T> v(prueba);
    std::vector<T> tmp(prueba.size());

    mergeSplit(prueba, tmp, 0, prueba.size() - 1);


    //return v;

}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &prueba, int val) {

    std::vector<T> v(prueba);

    for (int i = 0; i <= v.size() - 1; i++) {
        if (val == v[i]) {
            return i;
        }
    }
    return -1;

}

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &prueba, int val) {

    std::vector<T> v(prueba);

    int mid;
    int low = 0;
    int high = v.size() - 1;

    while (low < high) {
        mid = (low + high) / 2;
        if (val == v[mid]) {
            return mid;
        } else if (val < v[mid]) {
            high = mid - 1;
        } else if (val > v[mid]) {
            low = mid + 1;
        }
    }
    if (low == val) {
        return low;
    } else {
        return -1;
    }
}


#endif