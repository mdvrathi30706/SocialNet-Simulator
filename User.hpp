#include "AVL_Tree.hpp"
#include <unordered_set>

class User {
public:
	std::string userName; //not required as mapped from hash map
	std::unordered_set<std::string> friends; // set of freinds
	AVLtree Posts; // Posts implemented using AVLtree
	User(const std::string &userName) { //constructor
		this->userName=userName;
	}
	void addPost(const std::string &s) { // addPost , just insert post in Posts
		Posts.insert(s);
	}
	void outputPosts(int &n) { //fucntion implemented in AVLtree
		Posts.outputN(n);
	}
};