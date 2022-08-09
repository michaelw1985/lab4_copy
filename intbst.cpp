#include "intbst.h"

#include <iostream>
using std::cout;

// Daryon Roshanzaer 5701388
// Michael Wong 6209282

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node<T> *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(T value) {
	if (!root) {
        Node<T> *temp = new Node {value};
        root = temp;
        return true;
    }
    else {
        return insert(value, root);
    }
}


// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(T value, Node<T> *n) {
    if (value > n->info) {
        if (!n->right) {
            Node<T> *temp = new Node {value};
	    temp->parent = n;
            n->right = temp;
            return true;
        } else{
            return insert(value, n->right);
        }
    }
    else if ( value < n->info) {
        if (!n->left) {
            Node<T> *temp = new Node {value};
	    temp->parent = n;
            n->left = temp;
            return true;
        } else{
           return insert(value, n->left);
        }
    }
    else { // is equal
        return false;
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node<T> *n) const {
    if (!n) {
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}

void IntBST::printInOrder(Node<T> *n) const {
    if (!n) {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node<T> *n) const {
    if (!n) {
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
T IntBST::sum() const {
    return sum(root);
}
// recursive helper for sum
T IntBST::sum(Node<T> *n) const {
   if (!n) { return 0; }
   return (n->info + sum(n->left) + sum(n->right)); 
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node<T> *n) const {
    if (!n) { return 0; }
    return (1 + count(n->left) + count(n->right));
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
typename IntBST<T>::NodePtr IntBST<T>::getNodeFor(T value, Node<T>* n) const{
    if (!n) {
        return nullptr;
    }
    if (value > n->info) {
	if (!n->right) {
		return nullptr;
	} else {
        	return  getNodeFor(value, n->right);
	}
    }
    else if ( value < n->info) {
    	if (!n->left) {
		return nullptr;
	} else {
		return getNodeFor(value, n->left);
	}
    }
    else {
        return n; //this returns address right
    }
}

// returns true if value is in the tree; false if not

// FIX 
bool IntBST::contains(T value) const {
    if (getNodeFor(value, root)) return true;
    else return false;
}

// returns the Node containing the predecessor of the given value
typename IntBST<T>::NodePtr IntBST<T>::getPredecessorNode(T value) const{

    if (!root) return 0;
    Node<T> *currNode = getNodeFor(value, root);
    if (!currNode) return 0;
    if (!currNode->left) {
        if (!currNode->parent) return 0;
        else {
            while (currNode->parent) {
                if (currNode->parent->info < value) {
                    return currNode->parent;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return 0;
        }
    } else {
        currNode = currNode->left;
        while (currNode->right) {
            currNode = currNode->right;
        }
    }
    return currNode;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(T value) const{

    if (!root) return 0;
    Node<T> *currNode = getNodeFor(value, root);
    if (!currNode) return 0;
    if (!currNode->left) {
        if (!currNode->parent) return 0;
        else {
            while (currNode->parent) {
                if (currNode->parent->info < value) {
                    return currNode->parent->info;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return 0;
        }
    } else {
        currNode = currNode->left;
        while (currNode->right) {
            currNode = currNode->right;
        }
    }
    return currNode->info;
}

// returns the Node containing the successor of the given value
typename IntBST<T>::NodePtr IntBST<T>::getSuccessorNode(T value) const{
    if (!root) return nullptr;
    Node<T> *currNode = getNodeFor(value, root);
    if (!currNode) return nullptr;
    if (!currNode->right) {
        if (!currNode->parent) return nullptr;
        else {
            while (currNode->parent) {
                if (currNode->parent->info > value) {
                    return currNode->parent;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return nullptr;
        }
    } 
    else {
        currNode = currNode->right;
        while (currNode->left) {
            currNode = currNode->left;
        }
    }
    return currNode;
}


// returns the successor value of the given value or 0 if there is none
T IntBST::getSuccessor(T value) const{

    if (!root) return 0;
    Node<T> *currNode = getNodeFor(value, root);
    if (!currNode) return 0;
    if (!currNode->right) {
        if (!currNode->parent) return 0;
        else {
            while (currNode->parent) {
                if (currNode->parent->info > value) {
                    return currNode->parent->info;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return 0;
        }
    } 
    else {
        currNode = currNode->right;
        while (currNode->left) {
            currNode = currNode->left;
        }
    }
    return currNode->info;
}
/*
	if (!root) return 0;
	Node* currNode = getNodeFor(value, root);
	if (!currNode) return 0;
	if (currNode->right) {
		currNode = currNode->right;
		if (currNode->left) {
			while (currNode->left) {
				currNode = currNode->left;
			}
			return currNode->info;
		}
		else {
			return currNode->info;
		}
	}
	else {
		return 0;
	}
}
*/

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(T value){
    Node<T> *currNode = getNodeFor(value, root);
    if (!currNode) return false;
    if (currNode == root && !root->left && !root->right) {
        delete currNode;
        root = nullptr;
        return true;
    }
    else {
        if (!currNode->left && !currNode->right) { // no children
            if (currNode->parent->right == currNode) {
            	currNode->parent->right = nullptr;
            	delete currNode;
            	return true;
            } 
	    else {
            	currNode->parent->left = nullptr;
            	delete currNode;
            	return true;
            }
        } 
	else if (currNode->left && currNode->right) { // two children
		Node<T>* newNode = getSuccessorNode(value);
		T newData = newNode->info;
		remove(newNode->info); 
		currNode->info = newData;
		return true;
        } 
	else { // only has one child
		if (!currNode->parent) { // checking if the currNode is a root node
			if (currNode->left) {
				currNode->left->parent = nullptr;
				root = currNode->left;
				delete currNode;
				return true;
			}
			else {
				currNode->right->parent = nullptr;
				root = currNode->right;
				delete currNode;
				return true;
			}
		}
		else if (currNode->left) { // only has left child which is left
                	currNode->left->parent = currNode->parent;
                	if (currNode->parent->info > value) {
				currNode->parent->left = currNode->left;
               		} 
			else {
				currNode->parent->right = currNode->left;
                	}
                	delete currNode;
                	return true;
            	}
		else { // only has right child
                	currNode->right->parent = currNode->parent;
                	if (currNode->parent->info > value) {
        	            	currNode->parent->left = currNode->right;
                	} 
			else {
	                    	currNode->parent->right = currNode->right;
               		}
                	delete currNode;
                	return true;
           		}
        	}
    	}
}
