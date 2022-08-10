#include <iostream>
#include <string>
using namespace std;

template <class Item>
Item maximum(Item a, Item b) {
	if (a > b)
		return a;
	else
		return b;
}

// We can do this to our nodes in the BST too
template <class Data>
class BSTNode {
	public:
		Data key;
		BSTNode<Data>* left;
		BSTNode<Data>* right;
		BSTNode<Data>* parent;

		BSTNode(const Data &d) {
			key = d;
			left = right = parent = nullptr;
		}
};
/*
 * Now that the BSTNode uses templates, we need to specify the template 
 * paremeter when declaring objects or pointers of type BSTNode.
 */

/*
 * If we are creating an object of type BSTNode within another function
 * or class that uses templates, we may use the template parameter of that function/class
 */
template <class T>
void foo(T x) {
	BSTNode<T> n;
}
// In this case template parameter T is determined when we call the function foo
// int x = 5;
// foo(x);

/*
 * Creating new BSTNodes on the heap, we also need to pass the template parameters
 */
void bar() {
	BSTNode<string>* p;
	p = new BSTNode<string>("bytes");
}

/*
 * Similarly with class definitions
 */
template <class Key>
class BST {
	private:
		BSTNode<Key>* root;
		void print_InOrder(BSTNode<Key>* n);
	public:
		BST();
		// ....
};

int main() {
	cout << maximum<int>(10, 20) << endl;
	//cout << maximum(10, 20) << endl;  // brackets are optional for template functions
	cout << maximum<double>(101.5, 20.9) << endl;
	cout << maximum<string>("avocado", "butter") << endl;
	return 0;
}

































































// stack with templates
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack {
	private:
		vector<T> s;  // STL vector container
	public:
		void push(T x) { s.push_back(x); }
		void pop() { s.pop_back(); }
		T top() const { return s[s.size() - 1]; }
		bool empty() { return s.empty(); }

		// we can implement other methods that return T
		T min() const {
			if (empty()) return 999999999;
			T min = s[0];
			for (int i = 1; i < s.size(); i++) {
				if (s[i] < min)
					min = s[i];
			}
			return min;
		}

		typedef Stack<T>* StackPtr; // we need to define a typer for pointers
		StackPtr return_current_stack();
};


template <class T>
typename Stack<T>::StackPtr Stack<T>::return_current_stack() {
	return this;
}

void test_assert(bool b, string description) {
	if (!b)
		cerr << "Test failed! " << description << endl;
	else
		cout << "Test passed: " << description << endl;
}

void test_ints() {
	Stack<int> s; // starts empty
	s.push(1);
	s.push(2);
	s.push(3);

	test_assert(s.top() == 3, "s.top() == 3");
	s.pop();
	test_assert(s.top() == 2, "s.top() == 2");
	s.pop();
	test_assert(s.top() == 1, "s.top() == 1");
	s.pop();
	test_assert(s.empty(), "s.empty()");
}

void test_strings() {
	Stack<string> s; // starts empty
	s.push("avocado");
	s.push("butter");
	s.push("coconut");

	test_assert(s.top() == "coconut", "s.top() == coconut");
	s.pop();
	test_assert(s.top() == "butter", "s.top() == butter");
	s.pop();
	test_assert(s.top() == "avocado", "s.top() == avocado");
	s.pop();
	test_assert(s.empty(), "s.empty()");
}

int main() {
	test_ints();
	test_strings();

	// to use with new
	//Stack<int>::StackPtr s = new Stack<int>;

	return 0;
}
