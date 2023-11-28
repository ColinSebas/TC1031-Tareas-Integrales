/*
 * bst.h
 *
 *  Created on: 02/10/23
 *      Author: Sebas Colin
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class BST;   

template <class T>
class TreeNode {

    private:
        T value;
        TreeNode *left, *right;

	    TreeNode<T>* succesor();

    public:
        TreeNode(T);
        TreeNode(T, TreeNode<T>*, TreeNode<T>*);
        void add(T);
        bool find(T);
		T getValue() const {return value;};

		// HW
		int height(TreeNode<T>*);

        //void remove(T);
        //void removeChilds();
        void postorder(std::stringstream&) const;
        //void levelByLevel(std::stringstream&) const;
        void inorder(std::stringstream&) const;
        void preorder(std::stringstream&) const;
		//void auxLevel(TreeNode<T>*, int, std::stringstream&);

        friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(NULL), right(NULL) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) {
	value = val;
	left = le;
	right = ri;
}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < this->value) {
		if (left != NULL) {
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}

	} else {
		if (right != NULL) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else {
		return (right != 0 && right->find(val));
	}
	return false;
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	//std::stringstream ss;
	if (left != 0) {
		left->inorder(aux);
	}
	
	if (aux.tellp() != 0) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
	
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
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
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
		aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
		aux << " ";
	}
	aux << value;
}

/*
template <class T> 
void TreeNode<T>::levelByLevel(std::stringstream &aux) const {

}

template <class T>
void TreeNode<T>::auxLevel(TreeNode<T> *yeet, int lvl, std::stringstream &aux) {
	if (yeet == NULL) {
		return;
	}
	if (lvl == 1) {
		aux << yeet->value; 
		cout << yeet->value;
	} else if (lvl > 1) {
		auxLevel(yeet->left, lvl - 1, aux);
		auxLevel(yeet->right, lvl - 1, aux);
	}
}
*/

template <class T> 
int TreeNode<T>::height(TreeNode<T> *node) {
	int le, ri = 0;

    if (node == NULL) {
        return 0;
    } 

    le = height(node->left);
    ri = height(node->right);

    if (le > ri) {
        return (le + 1);
    } else {
        return (ri + 1);
    }
}


template <class T> 
class BST {

    private:
        TreeNode<T> *root;

    public:
        BST();
        ~BST();
        bool empty() const;
        void add(T);
        bool find(T) const;

        // HW

        std::string visit();
        int height() const;
        std::string ancestors(T) const;
        int whatlevelamI(T) const;

        //void remove(T);
        //void removeAll();
        //std::string inorder() const;
        //std::string preorder() const;
		void levelByLevel(std::stringstream&);
		void auxLevel(TreeNode<T>*, int, std::stringstream&);
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	//removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != NULL) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new TreeNode<T>(val);
	}
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T> 
void BST<T>::levelByLevel(std::stringstream &aux) {
	int h = root->height(root);
	for (int i = 1; i <= h; i++) {
		auxLevel(root, i, aux);
	}
}

template <class T>
void BST<T>::auxLevel(TreeNode<T> *yeet, int lvl, std::stringstream &aux) {
	if (yeet == NULL) {
		return;
	}
	if (lvl == 1) {
		aux << yeet->value; 
		aux << " ";
		//cout << yeet->value;
	} else if (lvl > 1) {
		auxLevel(yeet->left, lvl - 1, aux);
		auxLevel(yeet->right, lvl - 1, aux);
	}
}

template <class T> 
std::string BST<T>::visit() {
	
	std::stringstream ss;
	std::stringstream temp, tempDos;
	std::string ht;
	ss << "[";
	root->preorder(ss);
	ss << "]" << "\n" << "[";
	root->inorder(temp);
	ss << temp.str();
	ss << "]" << "\n" << "[";
	root->postorder(ss);
	ss << "]" << "\n" << "[";
	levelByLevel(tempDos);
	ht = tempDos.str();
	ht.pop_back();
	ss << ht;
	ss << "]";
	
	return ss.str();
}

template <class T>
int BST<T>::height() const {
		int i = root->height(root);
		return i;
}

template <class T> 
std::string BST<T>::ancestors(T val) const {
	
	std::stringstream ss;
	std::string fail = "fail";
	TreeNode<T> *p = root;
	ss << "[";
	//cout << p->value;
	if (root->find(val) == true) {

		while (p->value != val) {
	
			if (p->value < val) {
				//cout << p->value;
				ss << p->value << " ";
				p = p->right;
			} else if (p->value > val) {
				//cout << p->value;
				ss << p->value << " ";
				p = p->left;
			}

		}
		std::string final = ss.str();
		final.pop_back();
		final.append("]");
		return final;

	} else {

		std::string n = "[]";
		return n;

	}

	return fail;

}

template <class T> 
int BST<T>::whatlevelamI(T val) const {
	int i = 1;
	TreeNode<T> *p = root;

	if (root == NULL) {
        return 0;
    } 

	if (root->find(val) == true) {

		while (p->value != val) {
	
			if (p->value < val) {
				i++;
				p = p->right;
			} else if (p->value > val) {
				i++;
				p = p->left;
			}
		}

	}
	return i;

}

#endif	