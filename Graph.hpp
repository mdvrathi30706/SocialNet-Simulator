#include "User.hpp"
#include <unordered_map>
#include <vector>
#include <utility>
#include <queue>

class Graph {
	std::unordered_map<std::string,User*> Users;
	void inSen(std::string &userName) { //case-insensitve username and post content, works only with English
		for(char &c:userName) {
			if(c>='A' && c<='Z') {
				c=c+32;
			}
		}
	}
public:
	void addUser(std::string userName) { // add user to our graph
		inSen(userName);
		if(Users.find(userName)!=Users.end()) {
			std::cout << userName << " already exists" << std::endl;
			return;
		}
		User* Node = new User(userName);
		Users.insert({userName,Node});
	}
	void addFriend(std::string &user1,std::string &user2) { // add connection between two users
		inSen(user1);
		inSen(user2);
		if(user1==user2) {
			std::cout << "same users" << std::endl;
			return;
		}
		auto it1= Users.find(user1);
		auto it2= Users.find(user2);
		if(it1!=Users.end() && it2!=Users.end()) {
			if(it1->second->friends.find(user2)!=it1->second->friends.end()) {
				std::cout << user1 << " and " << user2 << " are already friends" << std::endl;
				return;
			}
			it1->second->friends.insert(user2);
			it2->second->friends.insert(user1);
		} else {
			if(it1==Users.end()) {
				std::cout << user1 << " not found" << std::endl;
			}
			if(it2==Users.end()) {
				std::cout << user2 << " not found" << std::endl;
			}
		}
	}
	void listFriend(std::string &userName) { // list all friends from the set friends
		inSen(userName);
		auto it=Users.find(userName);
		if(it!=Users.end()) {
			std::vector<std::string> v(it->second->friends.begin(),it->second->friends.end());
			std::sort(v.begin(),v.end());
			if (v.empty()) {
				std::cout << "NO FRIENDS";
			} else {
				for(const std::string &s:v) {
					std::cout << s << " ";
				}
			}
			std::cout << std::endl;
		} else {
			std::cout << userName << " not found" << std::endl;
		}
	}
	void suggestFriends(std::string &userName, int n) {
	    //Maintain a floating hash map of username as key, and value as number of mutual friends
	    //Then create a heap of the hashmap, with max-heap for number of mutuals and min heap for username, lexicographically
		inSen(userName);
		auto it1 = Users.find(userName);
		if (it1 == Users.end()) {
			std::cout << userName << " not found" << std::endl;
			return;
		}

		std::unordered_map<std::string, int> FoF;
		auto &userFriends = it1->second->friends;

		for (const std::string &f1 : userFriends) {
			auto it2 = Users.find(f1);
			if (it2 == Users.end()) continue;
			for (const std::string &f2 : it2->second->friends) {
				if (f2 != userName && userFriends.find(f2) == userFriends.end()) {
					FoF[f2]++;
				}
			}
		}

		std::vector<std::pair<int, std::string>> v;
		for (auto &p : FoF) v.emplace_back(p.second, p.first);

		auto cmp = [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) {
			if (a.first != b.first) return a.first < b.first;
			return a.second > b.second;
		};

		std::make_heap(v.begin(), v.end(), cmp);

		for (int i = 0; i < n && !v.empty(); ++i) {
			pop_heap(v.begin(), v.end(), cmp);
			std::cout << v.back().second << " (" << v.back().first << " mutual friends)\n";
			v.pop_back();
		}
	}

	void degreeOfSeparation (std::string &s1, std::string &s2) {
	    //find degree of separation between 2 users
		// Standard BFS
		inSen(s1);
		inSen(s2);
		if (Users.find(s1)==Users.end()) {
			std::cout << s1 << " not found"<<std::endl;
			if(Users.find(s2)==Users.end()) {
				if(s1!=s2) {
					std::cout << s2 << " not found"<<std::endl;
				}
			}
			return;
		}
		if(Users.find(s2)==Users.end()) {
			std::cout << s2 << " not found" << std::endl;
			return;
		}
		if(s1==s2) {
			std::cout << 0 << std::endl;
			return;
		}
		std::queue<std::pair<int,std::string>> Q;
		std::unordered_set<std::string> S;
		Q.push({0,s1});
		S.insert(s1);
		while(!Q.empty()) {
			std::pair<int,std::string> P=Q.front();
			Q.pop();
			auto it=Users.find(P.second);
			for(const std::string &s:it->second->friends) {
				if(s==s2) {
					std::cout << P.first+1 << std::endl;
					return;
				}
				if(S.find(s)==S.end()) {
					Q.push({P.first+1,s});
					S.insert(s);
				}
			}
		}
		std::cout << -1 << std::endl;
	}
	void addPost(std::string &userName,const std::string &s) {//Add post s, to user userName
		inSen(userName);
		auto it=Users.find(userName);
		if(it==Users.end()) {
			std::cout<< userName << " not found" << std::endl;
			return;
		}
		it->second->addPost(s);
	}
	void outputPosts(std::string &userName,int n) { //output recent n post of user userName
		inSen(userName);
		auto it=Users.find(userName);
		if(it==Users.end()) {
			std::cout << userName << " not found" << std::endl;
			return;
		}
		it->second->outputPosts(n);
	}
	~Graph() { //destructor to delete the custom classes
		for (auto &p : Users) {
			delete p.second;
		}
	}
};
