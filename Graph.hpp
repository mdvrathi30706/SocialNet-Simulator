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
		    if(it1->second->friends.find(user2)!=it1->second->friends.end()){
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
	void suggestFriends(std::string &userName,int n) { //suggest friends in descending order of number of mutual friends
	    //Working -> Maintains a floating map for username and mutual and then maintains a floating heap for all mutual users
		inSen(userName);
		auto it1=Users.find(userName);
		if(it1==Users.end()) {
			std::cout << userName << " not found" << std::endl;
		}
		else {
			std::unordered_map<std::string,int> FoF;
			for(const std::string &f1: it1->second->friends) {
				auto it2=Users.find(f1);
				for(const std::string &f2:it2->second->friends) {
					if(f2!=userName && it1->second->friends.find(f2)==it1->second->friends.end()) {
						FoF[f2]++; //if not in the map, then initialized to 0
					}
				}
			}
			auto cmp = [](const std::pair<int,std::string> &a, const std::pair<int,std::string> &b) {
			    //custom comparator as maxHeap according to number of mutuals, but minHeap according to username
				if(a.first != b.first) return a.first < b.first;
				return a.second > b.second;
			};
			std::priority_queue<std::pair<int,std::string>, std::vector<std::pair<int,std::string>>, decltype(cmp)> pQ(cmp);
			for (const auto &f:FoF) {
				pQ.push({f.second,f.first});
			}
			while(!pQ.empty() && n>0) {
				std::cout << pQ.top().second << " (" << pQ.top().first << " mutual friends)" <<std::endl;
				pQ.pop();
				n--;
			}
		}
		return;
	}
	void degreeOfSeparation (std::string &s1, std::string &s2) { //find degree of separation between 2 users
	    // Standard BFS
		inSen(s1);
		inSen(s2);
		if (Users.find(s1)==Users.end()) {
			std::cout << s1 << " not found"<<std::endl;
			if(Users.find(s2)==Users.end()) {
			    if(s1!=s2){
				    std::cout << s2 << " not found"<<std::endl;
			    }
			}
			return;
		}
		if(Users.find(s2)==Users.end()) {
			std::cout << s2 << " not found" << std::endl;
			return;
		}
		if(s1==s2){
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
