/*
 * splay.h
 *
 *      Date: 30/10/2023
 *      Author: sebas colin
 */

#ifndef SPLAY_H_
#define SPLAY_H_

#include <string> 
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class SplayTree;

template <class T> 
class Node {

    private:
        T value;
        Node *left, *right;
        Node *parent;

        Node<T>* succesor();
        Node<T>* rot_right(Node<T>*);
        Node<T>* rot_left(Node<T>*);

    public:
        Node(T val);
        Node(T val, Node<T>*, Node<T>*, Node<T>*);

        Node<T>* add(T);
        Node<T>* find(T);
        Node<T>* remove(T);

        void removeChilds();
        void print_tree(std::stringstream &) const;
        void preorder(std::stringstream &) const;
        void inorder(std::stringstream &) const;

        Node<T>* splay(Node<T>*, Node<T>*);

		// Aux functions 
		Node<T>* findMin();

        friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *pa) {
    value = val;
    left = le;
    right = ri;
    parent = pa;
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T> 
Node<T>* Node<T>::findMin() {
	Node<T>* temp = this;
	while(temp->left) {
		temp = temp->left; 
	} 
	return temp;
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right == 0) {
		if (left != 0) {
			left = 0;
		}
		return le;
	}

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *scopeParent, *child;
	scopeParent = right;
	child = right->left;
	while (child->left != 0) {
		scopeParent = child;
		child = child->left;
	}
	scopeParent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

// HW Member Functions 

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            return left->add(val);
        } else {
            left = new Node<T>(val);
            left->parent = this;
            return left;
        }
    } else if (val > value) {
        if (right != 0) {
            return right->add(val);
        } else {
            right = new Node<T>(val);
            right->parent = this;
            return right;
        }
    }
	
}

template <class T> 
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    } 

    if (val < value) {
        if (left) {
            if (left->value == val) {
                return left;
            }
            return left->find(val);
        }
    } else {
        if (right) {
            if (right->value == val) {
                return right;
            }
            return right->find(val);
        }
    }
}

template <class T>
Node<T>* Node<T>::remove(T val) {
   Node<T> *succ, *old;
    if (val < value) {
        if (left != 0) {                        
            if (left-> value == val) {          
                old = left;                     
                if (old->left != 0 && old->right != 0) {        
                    succ = left->succesor();                   
                    if (succ != 0) {
                        succ->left = old->left;                 
                        succ->right = old->right;
                        succ->parent = old->parent;
                        if (succ->left) 
                            succ->left->parent = succ;
                        if (succ->right)
                            succ->right->parent = succ;
                    }
                    left = succ;      
                } else if (old->right != 0) {              
                    old->right->parent = old->parent;       
                    left = old->right;                     
                } else if (old->left != 0) {               
                    old->left->parent = old->parent;        
                    left = old->left;                       
                } else {                                    
                    left = 0;
                }
            } else {
                return left->remove(val);
            }
        } else {
            return 0;
        }
    } else if (val > value) { 
        if (right != 0) {
            if (right->value == val) {
                old = right;
                if (old->left != 0 && old->right != 0) {
                    succ = right->succesor();      
                    if (succ != 0) {
                        succ->left = old->left;
                        succ->right = old->right;
                        succ->parent = old->parent;
                        if (succ->left)
                            succ->left->parent = succ;
                        if (succ->right)
                            succ->right->parent = succ;
                    }
                    right = succ;               
                } else if (old->right != 0) {
                    old->right->parent = old->parent;
                    right = old->right;
                } else if (old->left != 0) {
                    old->left->parent = old->parent;
                    right = old->left;
                } else {
                    right = 0;
                }
            } else {
                return right->remove(val);
            }
        } else {
            return 0;
        }
    }
}


template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			cout << succ->value;
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}



template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif