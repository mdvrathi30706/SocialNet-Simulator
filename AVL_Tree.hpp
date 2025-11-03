#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

struct Node {
	std::string post; //the post 
	Node* left=nullptr; // left child
	Node* right=nullptr; // right child
	int height=0; //height of the node (augmented for AVLtree)
	Node(const std::string &s) { //constructor-> add post to the node.
		post=s;
	}
	//We can also store timeStamp of creation in it if required
};

class AVLtree {
	Node* root;
	int height(Node* N) { // return height of the node, if nullptr, returns -1
		if (N==nullptr) {
			return -1;
		}
		return N->height;
	}
	Node* leftRotate(Node* x) { // left rotation of the node for balancing 
		Node* y=x->right;
		Node* s=y->left;
		y->left=x;
		x->right=s;
		y->height=std::max(height(y->left),height(y->right))+1;
		x->height=std::max(height(x->left),height(x->right))+1;
		return y;
	}
	Node* rightRotate(Node* x) { // right rotaion of the node for balancing
	    //will not be used in insert only condition 
		Node* y=x->left;
		Node* s=y->right;
		y->right=x;
		x->left=s;
		y->height=std::max(height(y->left),height(y->right))+1;
		x->height=std::max(height(x->left),height(x->right))+1;
		return y;
	}
	int getBalance(Node* N) { // return <-1 if node is right heavy, or >1 is node is left heavy
		if (N == nullptr) {
			return 0;
		}
		return height(N->left) - height(N->right);
	}

	Node* insertHelper(Node* N,const std::string &s) {//recursively insert node and balance tree
		if (N==nullptr) {
			return (new Node(s));
		}
		N->right=insertHelper(N->right,s);
		N->height=std::max(height(N->left),height(N->right))+1;
		int balance=getBalance(N);
		if(balance<-1) {
			return leftRotate(N);
		}
		//other balance conditions not required for insertion
		//would be required for deletion if applicable
		return N;
	}
	void deleteTree(Node* N) {//post order deletion of nodes
		if(N==nullptr) {
			return;
		}
		deleteTree(N->left);
		deleteTree(N->right);
		delete N; 
	}
	void outputHelper(Node* N,int &n) { //recursively help output in reverse inorder traversal
		if(N==nullptr) {
			return;
		}
		if(n<=0) {
			return;
		}
		outputHelper(N->right,n);
		if(n<=0){
		    return;
		}
		std::cout << N->post << std::endl;
		n--;
		if(n<=0){
		    return;
		}
		outputHelper(N->left,n);
	}
public:
	void insert(const std::string &s) {//insert a node of post 
		root=insertHelper(root,s);
	}
	AVLtree() { // contructor
		this->root=nullptr;
	}
	~AVLtree() { // destruct using deleteTree
		deleteTree(root);
	}
	void outputN(int n) { // output last N nodes by using outputHelper
	    int count=(n==-1 ? INT_MAX : n);
		outputHelper(root,count);
	}
};